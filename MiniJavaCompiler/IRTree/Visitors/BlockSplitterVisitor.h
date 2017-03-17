//
// Created by nismohl on 17.03.17.
//

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

namespace IRTree {

    class CBlockSplitterVisitor : public CVisitor {
    public:
        CBlockSplitterVisitor( bool _verbose = false )
                : CVisitor( _verbose ), oneBlock( nullptr ), metLabel( false )  {}

        std::vector<std::shared_ptr<CStatementList>> GetAllBlocks();

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
        bool metLabel;
        std::shared_ptr<CStatementList> oneBlock;
        std::vector<std::shared_ptr<CStatementList>> allBlocks;
        void addNewLabel();
    };
}
