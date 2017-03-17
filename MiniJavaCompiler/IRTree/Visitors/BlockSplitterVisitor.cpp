//
// Created by nismohl on 17.03.17.
//

#include <IRTree/Visitors/BlockSplitterVisitor.h>

namespace IRTree {

std::vector<std::shared_ptr<CStatementList>> CBlockSplitterVisitor::GetAllBlocks() {
    return allBlocks;
}

void CBlockSplitterVisitor::Visit(const CConstExpression *expression) {
    assert( false );
}

void CBlockSplitterVisitor::Visit(const CNameExpression *expression) {
    assert( false );
}

void CBlockSplitterVisitor::Visit(const CTempExpression *expression) {
    assert( false );
}

void CBlockSplitterVisitor::Visit(const CBinaryExpression *expression) {
    assert( false );
}

void CBlockSplitterVisitor::Visit(const CMemExpression *expression) {
    assert( false );
}

void CBlockSplitterVisitor::Visit(const CCallExpression *expression) {
    assert( false );
}

void CBlockSplitterVisitor::Visit(const CEseqExpression *expression) {
    assert( false );
}

void CBlockSplitterVisitor::Visit(const CExpStatement *statement) {
    if( !metLabel ) {
        addNewLabel();
    }
    oneBlock->Add( std::shared_ptr<const CStatement>( statement ) );
}

void CBlockSplitterVisitor::Visit(const CJumpConditionalStatement *statement) {
    if( !metLabel ) {
        addNewLabel();
    }
    oneBlock->Add( std::shared_ptr<const CStatement>( statement ) );
    allBlocks.push_back( oneBlock );
    oneBlock = nullptr;
    metLabel = false;
}

void CBlockSplitterVisitor::Visit(const CJumpStatement *statement) {
    if( !metLabel ) {
        addNewLabel();
    }
    oneBlock->Add( std::shared_ptr<const CStatement>( statement ) );
    allBlocks.push_back( oneBlock );
    oneBlock = nullptr;
    metLabel = false;
}

void CBlockSplitterVisitor::Visit(const CLabelStatement *statement) {
    metLabel = true;
    if( oneBlock != nullptr ) {
        oneBlock->Add(
                new CJumpStatement(
                        statement->Label()
                )
        );
        allBlocks.push_back( oneBlock );
    }
    oneBlock = std::shared_ptr<CStatementList>( new CStatementList( statement ) );
}

void CBlockSplitterVisitor::Visit(const CMoveStatement *statement) {
    if( !metLabel ) {
        addNewLabel();
    }
    oneBlock->Add( std::shared_ptr<const CStatement>( statement ) );
}

void CBlockSplitterVisitor::Visit(const CSeqStatement *statement) {
    assert( false );
}

void CBlockSplitterVisitor::Visit(const CExpressionList *list) {
    assert( false );
}

void CBlockSplitterVisitor::Visit(const CStatementList *list) {
    std::vector<std::shared_ptr<const CStatement>> statements = list->Statements();
    for( auto it = statements.begin(); it != statements.end(); ++it ) {
        ( *it )->Accept( this );
    }
    if( oneBlock != nullptr ) {
        oneBlock->Add(
                new CJumpStatement(
                        // Label with the biggest number
                        CLabel( LabelTag::FINISH )
                )
        );
        allBlocks.push_back( oneBlock );
    }
}

void CBlockSplitterVisitor::addNewLabel() {
    oneBlock = std::shared_ptr<CStatementList>(
            new CStatementList(
                    new CLabelStatement( CLabel() )
            )
    );
    metLabel = true;
}

}
