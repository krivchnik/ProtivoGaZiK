//
// Created by nismohl on 17.03.17.
//

#include <CodeGeneration/HolyPatricVisitor.h>

namespace IRTree {

    void HolyPatricVisitor::Visit(const CConstExpression *expression) {
        assert(expression != 0);
        registerId[expression] = ++nRegisters;
        resultAssemblerPrograms.push_back("MOV " + constructRegister(registerId[expression]) + " " +
                                                  std::to_string(expression->Value()) + "\n");
        isMemSubexpression = false;
    }

    void HolyPatricVisitor::Visit(const CNameExpression *expression) {
        assert(expression != 0);
        resultAssemblerPrograms.push_back(expression->Label().ToString() + "\n");
        isMemSubexpression = false;
    }

    void HolyPatricVisitor::Visit(const CTempExpression *expression) {
        assert(expression != 0);
        if( registerIdForTemps.find(expression->Temporary().ToString()) == registerIdForTemps.end() ) {
            registerId[expression] = ++nRegisters;
            if( expression->Temporary().ToString()[0] == '$') {
                resultAssemblerPrograms.push_back("MOV");
                resultAssemblerPrograms.push_back(constructRegister(registerId[expression]));
                resultAssemblerPrograms.push_back(expression->Temporary().ToString() + "\n");
            } else {
                registerIdForTemps[expression->Temporary().ToString()] = nRegisters;
            }
        } else {
            registerId[expression] = registerIdForTemps[expression->Temporary().ToString()];
        }
        isMemSubexpression = false;
    }

    void HolyPatricVisitor::Visit(const CBinaryExpression *expression) {
        assert(expression != 0);
        expression->LeftOperand()->Accept(this);
        expression->RightOperand()->Accept(this);
        resultAssemblerPrograms.push_back(to_string(expression->Operation()));
        resultAssemblerPrograms.push_back(constructRegister(registerId[expression->LeftOperand()]));
        resultAssemblerPrograms.push_back(constructRegister(registerId[expression->RightOperand()]) + "\n");
        registerId[expression] = registerId[expression->LeftOperand()];
        isMemSubexpression = false;
    }

    void HolyPatricVisitor::Visit(const CMemExpression *expression) {
        assert(expression != 0);
        expression->Address()->Accept(this);
        //resultAssemblerPrograms.push_back("MOV");
        registerId[expression] = registerId[expression->Address()];
        isMemSubexpression = true;
        //resultAssemblerPrograms.push_back(constructRegister(registerId[expression]));
        //resultAssemblerPrograms.push_back("[" + constructRegister(registerId[expression->Address()]) + "]\n");
    }

    void HolyPatricVisitor::Visit(const CCallExpression *expression) {
        assert(expression != 0);
        expression->Arguments()->Accept(this);
        for( int i = expression->Arguments()->Expressions().size() - 1; i >= 0 ; --i){
            resultAssemblerPrograms.push_back("PUSH " + constructRegister(
                    registerId[(expression->Arguments()->Expressions()[i]).get()]) + "\n");
        }
        resultAssemblerPrograms.push_back("CALL");
        expression->Function()->Accept(this);
        for( int i = expression->Arguments()->Expressions().size() - 1; i >= 0 ; --i){
            resultAssemblerPrograms.push_back("POP " + constructRegister(
                    registerId[(expression->Arguments()->Expressions()[i]).get()]) + "\n");
        }
        isMemSubexpression = false;
    }

    void HolyPatricVisitor::Visit(const CEseqExpression *expression) {
        assert( false );
    }

    void HolyPatricVisitor::Visit(const CExpStatement *statement) {
        assert( statement != 0 );
        statement->Expression()->Accept(this);
    }

    void HolyPatricVisitor::Visit(const CJumpConditionalStatement *statement) {
        assert( statement != 0 );
        statement->LeftOperand()->Accept(this);
        statement->RightOperand()->Accept(this);
        resultAssemblerPrograms.push_back(to_string(statement->Operation()) + " ");
        resultAssemblerPrograms.push_back(constructRegister(registerId[statement->LeftOperand()]) + " ");
        resultAssemblerPrograms.push_back(constructRegister(registerId[statement->RightOperand()]) + "\n");
        resultAssemblerPrograms.push_back(to_jump_string(statement->Operation()) + " " + statement->TrueLabel().ToString() + "\n");
    }

    void HolyPatricVisitor::Visit(const CJumpStatement *statement) {
        assert(statement != 0);
        resultAssemblerPrograms.push_back("JUMP " + statement->Target().ToString() + "\n");
    }

    void HolyPatricVisitor::Visit(const CLabelStatement *statement) {
        assert( statement != 0 );
        resultAssemblerPrograms.push_back("LABEL " + statement->Label().ToString() + "\n");
    }

    void HolyPatricVisitor::Visit(const CMoveStatement *statement) {
        assert( statement != 0 );
        statement->Destination()->Accept(this);
        bool isLeftMemExpression = isMemSubexpression;
        statement->Source()->Accept(this);
        bool isRightMemExpression = isMemSubexpression;

        resultAssemblerPrograms.push_back("MOV");

        std::string leftArgument = isLeftMemExpression ? "[" : "";
        leftArgument.append(constructRegister(registerId[statement->Destination()]));
        if( isLeftMemExpression ) {
            leftArgument.append("]");
        }

        std::string rightArgument = isRightMemExpression ? "[" : "";
        rightArgument.append(constructRegister(registerId[statement->Source()]));
        if( isRightMemExpression ) {
            rightArgument.append("]");
        }
        resultAssemblerPrograms.push_back(leftArgument);
        resultAssemblerPrograms.push_back(rightArgument + "\n");
    }

    void HolyPatricVisitor::Visit(const CSeqStatement *statement) {
        // ???
        assert( false );
    }

    void HolyPatricVisitor::Visit(const CExpressionList *list) {
        assert(list != 0);
        for( int i = 0; i < list->Expressions().size(); ++i){
            list->Expressions()[i]->Accept(this);
        }
    }

    void HolyPatricVisitor::Visit(const CStatementList *list) {
        assert( list != 0 );
        std::vector<std::shared_ptr<const CStatement>> statements = list->Statements();
//        std::cout << statements.size() << "\n";
//        std::shared_ptr<const CStatement> firstStatement(statements[0]);
//        const CLabelStatement* rawStatement = dynamic_cast<const CLabelStatement*>(firstStatement.get());
//        std::cout << rawStatement->Label().ToString() << "\n";
        for( auto it = statements.begin(); it != statements.end(); ++it ) {
            ( *it )->Accept( this );
        }
    }

    std::string HolyPatricVisitor::GetResultProgram() {
        std::string resultProgram = "";
        for( int i = 0; i < resultAssemblerPrograms.size(); ++i ){
            resultProgram += " " + resultAssemblerPrograms[i];
        }
        return resultProgram;
    }

    std::string HolyPatricVisitor::constructRegister(int index) const {
        return "R" + std::to_string(index);
    }

    HolyPatricVisitor::HolyPatricVisitor(bool _verbose)
            : CVisitor( _verbose ), nRegisters( 0 ), isMemSubexpression( false ) {}

    std::string HolyPatricVisitor::to_jump_string(TLogicOperatorType type) const {
        switch( type )
        {
            case TLogicOperatorType::LOT_EQ:
                return std::string("JE");
            case TLogicOperatorType::LOT_NE:
                return std::string("JNE");
            case TLogicOperatorType::LOT_LT:
                return std::string("JL");
            case TLogicOperatorType::LOT_GT:
                return std::string("JG");
            case TLogicOperatorType::LOT_LE:
                return std::string("JLE");
            case TLogicOperatorType::LOT_GE:
                return std::string("JGE");
            default:
                assert( false );
        }
    }

}
