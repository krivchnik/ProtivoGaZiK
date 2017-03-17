//
// Created by nismohl on 17.03.17.
//

#include <IRTree/BlockLinearizer.h>
#include <list>
#include <map>

namespace IRTree {

std::vector<Block> CBlockLinearizer::Linearize(std::vector<std::shared_ptr<CStatementList>>& argBlocks) {

    std::map<CLabel, Block> blocks;
    for( auto it = argBlocks.begin(); it != argBlocks.end(); ++it ) {
        auto statements = ( *it )->Statements();
        std::shared_ptr<const CStatement> firstStatement = statements[0];

        //first statement is always label
        CLabel label = static_cast<const CLabelStatement*>( firstStatement.get() )->Label();
        blocks.emplace( label, statements );
    }

    std::vector<Block> linearizedBlocks;
    while( !blocks.empty() ) {
        std::cout << blocks.size() << "\n";
        auto currentBlock = blocks.begin();
        while( currentBlock != blocks.end() ) {

            std::shared_ptr<const CStatement> lastStatement = currentBlock->second.back();

            //last statement is either jump or conditional jump
            if( auto jumpStatement = dynamic_cast<const CJumpStatement*>( lastStatement.get() ) ) {
                CLabel jumpLabel = jumpStatement->Target();
                linearizedBlocks.push_back(currentBlock->second);
                blocks.erase(currentBlock);
                currentBlock = blocks.find(jumpLabel);

            } else if( auto jumpStatement = dynamic_cast<const CJumpConditionalStatement*>( lastStatement.get() ) ) {

                CLabel trueLabel = jumpStatement->TrueLabel();
                CLabel falseLabel = jumpStatement->FalseLabel();
                auto nextBlock = blocks.find(falseLabel);
                if (nextBlock == blocks.end()) {
                    nextBlock = blocks.find(trueLabel);
                    if (nextBlock != blocks.end()) {

                        //invert operation and swap labels
                        currentBlock->second[currentBlock->second.size() - 1] =
                                std::shared_ptr<const CJumpConditionalStatement>(
                                        new CJumpConditionalStatement(
                                                GetInverseType(jumpStatement->Operation()),
                                                jumpStatement->LeftOperand(),
                                                jumpStatement->RightOperand(),
                                                jumpStatement->FalseLabel(),
                                                jumpStatement->TrueLabel()
                                        )
                                );
                        linearizedBlocks.push_back(currentBlock->second);
                        blocks.erase(currentBlock);
                        currentBlock = blocks.find(trueLabel);

                    } else {

                        //add new Block
                        CLabel newLabel;
                        std::shared_ptr<const CLabelStatement> labelStatement(
                                new CLabelStatement(
                                        newLabel
                                )
                        );
                        std::shared_ptr<const CJumpStatement> newJumpStatement(
                                new CJumpStatement(
                                        falseLabel
                                )
                        );
                        std::vector<std::shared_ptr<const CStatement> > newBlock;
                        newBlock.push_back(labelStatement);
                        newBlock.push_back(newJumpStatement);
                        blocks.emplace(newLabel, newBlock);

                        currentBlock->second[currentBlock->second.size() - 1] =
                                std::shared_ptr<const CJumpConditionalStatement>(
                                        new CJumpConditionalStatement(
                                                jumpStatement->Operation(),
                                                jumpStatement->LeftOperand(),
                                                jumpStatement->RightOperand(),
                                                jumpStatement->TrueLabel(),
                                                newLabel
                                        )
                                );

                        linearizedBlocks.push_back(currentBlock->second);
                        blocks.erase(currentBlock);
                        currentBlock = blocks.find(newLabel);
                    }
                }

                linearizedBlocks.push_back(currentBlock->second);
                blocks.erase(currentBlock);
                currentBlock = blocks.find(falseLabel);
            } else {
                assert(false);
            }
        }
    }
    return linearizedBlocks;
}
}
