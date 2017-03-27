
#pragma once

#include <cassert>
#include <deque>
#include <limits>
#include <vector>

#include <IRTree/Nodes/NodeNames.h>
#include <IRTree/Visitors/Visitor.h>
#include <IRTree/Nodes/Expression.h>
#include <IRTree/Nodes/ExpressionList.h>
#include <IRTree/Nodes/Statement.h>
#include <IRTree/Nodes/StatementList.h>
#include <Nodes/CListStatement.h>
#include <map>


namespace IRTree {
// генерация ассемблерного кода
    class HolyPatricVisitor : public CVisitor {
    public:
        HolyPatricVisitor( bool _verbose = false );

        std::string GetResultProgram();

        // Visitors for different node types.
        void Visit( const CConstExpression* expression ) override;
        void Visit( const CNameExpression* expression ) override;
        void Visit( const CTempExpression* expression ) override;
        void Visit( const CBinaryExpression* expression ) override;
        void Visit( const CMemExpression* expression ) override;
        void Visit( const CCallExpression* expression ) override;
        void Visit( const CEseqExpression* expression ) override;

        void Visit( const CExpStatement* expression ) override;
        void Visit( const CJumpConditionalStatement* expression ) override;
        void Visit( const CJumpStatement* expression ) override;
        void Visit( const CLabelStatement* expression ) override;
        void Visit( const CMoveStatement* expression ) override;
        void Visit( const CSeqStatement* expression ) override;

        void Visit( const CExpressionList* list ) override;
        void Visit( const CStatementList* list ) override;

    private:
        std::vector<std::string> resultAssemblerPrograms;
        // номер регистра в который мы запишем результат работы данной вершины
        std::map<const IVisitorTarget*, int> registerId;
        // количество используемых регистров
        int nRegisters;
        std::string constructRegister(int index) const;
        std::string to_jump_string(TLogicOperatorType operation) const;
    };
}
