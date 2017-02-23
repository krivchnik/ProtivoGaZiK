#include <IRTree/Visitors/DoubleCallEliminationVisitor.h>

using namespace IRTree;

std::shared_ptr<const CStatement> CDoubleCallEliminationVisitor::ResultTree() {
    return lastStatement;
}

void CDoubleCallEliminationVisitor::updateLastExpression( const CExpression* newLastExpression ) {
    lastExpression = std::shared_ptr<const CExpression>( newLastExpression );
}

void CDoubleCallEliminationVisitor::updateLastExpression( std::shared_ptr<const CExpression> newLastExpression ) {
    lastExpression = newLastExpression;
}

void CDoubleCallEliminationVisitor::updateLastExpressionList( const CExpressionList* newLastExpressionList ) {
    lastExpressionList = std::shared_ptr<const CExpressionList>( newLastExpressionList );
}

void CDoubleCallEliminationVisitor::updateLastExpressionList( std::shared_ptr<const CExpressionList> newLastExpressionList ) {
    lastExpressionList = newLastExpressionList;
}

void CDoubleCallEliminationVisitor::updateLastStatement( const CStatement* newLastStatement ) {
    lastStatement = std::shared_ptr<const CStatement>( newLastStatement );
}

void CDoubleCallEliminationVisitor::updateLastStatement( std::shared_ptr<const CStatement> newLastStatement ) {
    lastStatement = newLastStatement;
}

void CDoubleCallEliminationVisitor::updateLastStatementList( const CStatementList* newLastStatementList ) {
    lastStatementList = std::shared_ptr<const CStatementList>( newLastStatementList );
}

void CDoubleCallEliminationVisitor::updateLastStatementList( std::shared_ptr<const CStatementList> newLastStatementList ) {
    lastStatementList = newLastStatementList;
}


/*__________ Expressions __________*/

void CDoubleCallEliminationVisitor::Visit( const CConstExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_CONST );
    onNodeEnter( nodeName );

    updateLastExpression(
        new CConstExpression( expression->Value() )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CNameExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_NAME );
    onNodeEnter( nodeName );

    updateLastExpression(
        new CNameExpression( expression->Label() )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CTempExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_TEMP );
    onNodeEnter( nodeName );

    updateLastExpression(
        new CTempExpression( expression->Temporary() )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CBinaryExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_BINARY );
    onNodeEnter( nodeName );

    expression->LeftOperand()->Accept( this );
    std::shared_ptr<const CExpression> expressionLeft(lastExpression);

    expression->RightOperand()->Accept( this );
    std::shared_ptr<const CExpression> expressionRight(lastExpression);

    updateLastExpression(
        new CBinaryExpression(
            expression->Operation(),
            expressionLeft,
            expressionRight
        )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CMemExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_MEM );
    onNodeEnter( nodeName );

    expression->Address()->Accept( this );
    std::shared_ptr<const CExpression> addressExpression( lastExpression );

    updateLastExpression(
        new CMemExpression( addressExpression )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CCallExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_CALL );
    onNodeEnter( nodeName );

    expression->Function()->Accept( this );
    std::shared_ptr<const CExpression> functionExpression( lastExpression );
    expression->Arguments()->Accept( this );
    std::shared_ptr<const CExpressionList> argumentsList( lastExpressionList );

    updateLastExpression(
        new CCallExpression(
            functionExpression,
            argumentsList
        )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CEseqExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_ESEQ );
    onNodeEnter( nodeName );

    expression->Statement()->Accept( this );
    expression->Expression()->Accept( this );

    updateLastExpression(
        new CEseqExpression(
            lastStatement,
            lastExpression
        )
    );

    onNodeExit( nodeName );
}

/*__________ Statements __________*/

void CDoubleCallEliminationVisitor::Visit( const CExpStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_EXP );
    onNodeEnter( nodeName );

    statement->Expression()->Accept( this );
    std::shared_ptr<const CExpression> expression( lastExpression );

    updateLastStatement(
        new CExpStatement( expression )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CJumpConditionalStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_CJUMP );
    onNodeEnter( nodeName );

    statement->LeftOperand()->Accept( this );
    std::shared_ptr<const CExpression> expressionLeft( lastExpression );

    statement->RightOperand()->Accept( this );
    std::shared_ptr<const CExpression> expressionRight( lastExpression );

    updateLastStatement(
        new CJumpConditionalStatement(
            statement->Operation(),
            expressionLeft,
            expressionRight,
            statement->TrueLabel(),
            statement->FalseLabel()
        )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CJumpStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_JUMP );
    onNodeEnter( nodeName );

    updateLastStatement(
        new CJumpStatement( statement->Target() )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CLabelStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_LABEL );
    onNodeEnter( nodeName );

    updateLastStatement(
        new CLabelStatement( statement->Label() )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CMoveStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_MOVE );
    onNodeEnter( nodeName );

    statement->Destination()->Accept( this );
    std::shared_ptr<const CExpression> destination( lastExpression );

    statement->Source()->Accept( this );
    std::shared_ptr<const CExpression> source( lastExpression );

    updateLastStatement(
        new CMoveStatement( destination, source )
    );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CSeqStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_SEQ );
    onNodeEnter( nodeName );

    statement->LeftStatement()->Accept( this );
    std::shared_ptr<const CStatement> statementLeft( lastStatement );

    statement->RightStatement()->Accept( this );
    std::shared_ptr<const CStatement> statementRight( lastStatement );

    updateLastStatement(
        new CSeqStatement( statementLeft, statementRight )
    );

    onNodeExit( nodeName );
}

/*__________  Lists __________*/

void CDoubleCallEliminationVisitor::Visit( const CExpressionList* list ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_LIST );
    onNodeEnter( nodeName );

    CExpressionList* newList = new CExpressionList();

    const std::vector<std::shared_ptr<const CExpression>>& expressions = list->Expressions();
    for ( auto it = expressions.begin(); it != expressions.end(); ++it ) {
        ( *it )->Accept( this );
        newList->Add( lastExpression );
    }

    updateLastExpressionList( newList );

    onNodeExit( nodeName );
}

void CDoubleCallEliminationVisitor::Visit( const CStatementList* list ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_LIST );
    onNodeEnter( nodeName );

    CStatementList* newList = new CStatementList();

    const std::vector<std::shared_ptr<const CStatement>>& statements = list->Statements();
    for ( auto it = statements.begin(); it != statements.end(); ++it ) {
        ( *it )->Accept( this );
        newList->Add( lastStatement );
    }

    updateLastStatementList( newList );

    onNodeExit( nodeName );
}
