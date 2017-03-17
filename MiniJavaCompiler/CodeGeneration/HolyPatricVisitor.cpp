//
// Created by nismohl on 17.03.17.
//

#include <CodeGeneration/HolyPatricVisitor.h>

namespace IRTree {

    void HolyPatricVisitor::Visit(const CConstExpression *expression) {
        assert(expression != 0);
        registerId[expression] = registerId.size();
        resultAssemblerPrograms.push_back("LI " + std::to_string(expression->Value()) + "\n");
        assert( false );
    }

    void HolyPatricVisitor::Visit(const CNameExpression *expression) {
        assert(expression != 0);
        resultAssemblerPrograms.push_back(expression->Label().ToString() + "\n");
    }

    void HolyPatricVisitor::Visit(const CTempExpression *expression) {
        assert(expression != 0);
        registerId[expression] = registerId.size();
    }

    void HolyPatricVisitor::Visit(const CBinaryExpression *expression) {
        assert(expression != 0);
        expression->LeftOperand()->Accept(this);
        expression->RightOperand()->Accept(this);
        resultAssemblerPrograms.push_back(to_string(expression->Operation()) + " ");
        resultAssemblerPrograms.push_back(constructRegister(registerId[expression->LeftOperand()]) + " ");
        resultAssemblerPrograms.push_back(constructRegister(registerId[expression->RightOperand()]) + "\n");
    }

    void HolyPatricVisitor::Visit(const CMemExpression *expression) {
        assert(expression != 0);
        expression->Address()->Accept(this);
        resultAssemblerPrograms.push_back("MEM ");
        resultAssemblerPrograms.push_back(constructRegister(registerId[expression->Address()]) + "\n");
    }

    void HolyPatricVisitor::Visit(const CCallExpression *expression) {
        assert(expression != 0);
        expression->Arguments()->Accept(this);
        for( int i = expression->Arguments()->Expressions().size() - 1; i >= 0 ; --i){
            resultAssemblerPrograms.push_back("PULL " + constructRegister(
                    registerId[(expression->Arguments()->Expressions()[i]).get()]) + "\n");
        }
        resultAssemblerPrograms.push_back("CALL ");
        expression->Function()->Accept(this);
    }

    void HolyPatricVisitor::Visit(const CEseqExpression *expression) {
        assert( false );
    }

    void HolyPatricVisitor::Visit(const CExpStatement *statement) {
        assert( statement != 0 );
        statement->Expression()->Accept(this);
        assert(false);
    }

    void HolyPatricVisitor::Visit(const CJumpConditionalStatement *statement) {
        assert( statement != 0 );
        statement->LeftOperand()->Accept(this);
        statement->RightOperand()->Accept(this);
        resultAssemblerPrograms.push_back(to_string(statement->Operation()) + " ");
        resultAssemblerPrograms.push_back(constructRegister(registerId[statement->LeftOperand()]) + " ");
        resultAssemblerPrograms.push_back(constructRegister(registerId[statement->RightOperand()]) + "\n");
        resultAssemblerPrograms.push_back("CJUMP " + statement->TrueLabel().ToString() + "\n");
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
        statement->Source()->Accept(this);
        resultAssemblerPrograms.push_back("MOVE ");
        resultAssemblerPrograms.push_back(constructRegister(registerId[statement->Destination()]));
        resultAssemblerPrograms.push_back(constructRegister(registerId[statement->Source()]) + "\n");
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
        assert(false);
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

}
