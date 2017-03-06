#include <IRTree/Visitors/SeqLinearizerVisitor.h>

using namespace IRTree;

std::shared_ptr<const CStatement> CSeqLinearizerVisitor::ResultTree() {
    return ( lastStatement );
}

void CSeqLinearizerVisitor::updateLastExpression( const CExpression* newLastExpression ) {
    lastExpression = std::shared_ptr<const CExpression>( newLastExpression );
}

void CSeqLinearizerVisitor::updateLastExpression( std::shared_ptr<const CExpression> newLastExpression ) {
    lastExpression = ( newLastExpression );
}

void CSeqLinearizerVisitor::updateLastStatement( const CStatement* newLastStatement ) {
    lastStatement = std::shared_ptr<const CStatement>( newLastStatement );
}

void CSeqLinearizerVisitor::updateLastStatement( std::shared_ptr<const CStatement> newLastStatement ) {
    lastStatement = ( newLastStatement );
}

void CSeqLinearizerVisitor::updateLastExpressionList( const CExpressionList* newLastExpressionList ) {
    lastExpressionList = std::shared_ptr<const CExpressionList>( newLastExpressionList );
}

void CSeqLinearizerVisitor::updateLastExpressionList( std::shared_ptr<const CExpressionList> newLastExpressionList ) {
    lastExpressionList = ( newLastExpressionList );
}

void CSeqLinearizerVisitor::saveResult( std::shared_ptr<const CStatement> result ) {
    if ( distanceToSeqStack.back() == 1 ) {
        statementStack.back()->push_back( ( result ) );
    } else {
        updateLastStatement( ( result ) );
    }
}

/*__________ Expressions __________*/

void CSeqLinearizerVisitor::Visit( const CConstExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_CONST );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    updateLastExpression( ( expression->Clone() ) );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CNameExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_NAME );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    updateLastExpression( ( expression->Clone() ) );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CTempExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_TEMP );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    updateLastExpression( ( expression->Clone() ) );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CBinaryExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_BINARY );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    expression->LeftOperand()->Accept( this );
    std::shared_ptr<const CExpression> leftOperand = ( lastExpression );
    expression->RightOperand()->Accept( this );
    std::shared_ptr<const CExpression> rightOperand = ( lastExpression );

    updateLastExpression(
        new CBinaryExpression(
            expression->Operation(),
            ( leftOperand ),
            ( rightOperand )
        )
    );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CMemExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_MEM );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    expression->Address()->Accept( this );
    std::shared_ptr<const CExpression> addressExpression = ( lastExpression );

    updateLastExpression(
        new CMemExpression(
            ( addressExpression )
        )
    );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CCallExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_CALL );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    expression->Function()->Accept( this );
    std::shared_ptr<const CExpression> functionExpression = ( lastExpression );
    expression->Arguments()->Accept( this );
    std::shared_ptr<const CExpressionList> argumentList = ( lastExpressionList );

    updateLastExpression(
        new CCallExpression(
            ( functionExpression ),
            ( argumentList )
        )
    );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CEseqExpression* expression ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_ESEQ );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    expression->Statement()->Accept( this );
    std::shared_ptr<const CStatement> eseqStatement = ( lastStatement );
    expression->Expression()->Accept( this );
    std::shared_ptr<const CExpression> eseqExpression = ( lastExpression );

    updateLastExpression(
        new CEseqExpression(
            ( eseqStatement ),
            ( eseqExpression )
        )
    );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

/*__________ Statements __________*/

void CSeqLinearizerVisitor::Visit( const CExpStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_EXP );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    statement->Expression()->Accept( this );
    std::shared_ptr<const CExpression> expression = ( lastExpression );

    std::shared_ptr<CStatement> result(
        new CExpStatement(
            ( expression )
        )
    );
    saveResult( ( result ) );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CJumpConditionalStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_CJUMP );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    statement->LeftOperand()->Accept( this );
    std::shared_ptr<const CExpression> leftOperand = ( lastExpression );
    statement->RightOperand()->Accept( this );
    std::shared_ptr<const CExpression> rightOperand = ( lastExpression );

    std::shared_ptr<CStatement> result(
        new CJumpConditionalStatement(
            statement->Operation(),
            ( leftOperand ),
            ( rightOperand ),
            statement->TrueLabel(),
            statement->FalseLabel()
        )
    );
    saveResult( ( result ) );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CJumpStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_JUMP );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    std::shared_ptr<CStatement> result(
        new CJumpStatement( statement->Target() )
    );
    saveResult( ( result ) );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CLabelStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_LABEL );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    std::shared_ptr<CStatement> result(
        new CLabelStatement( statement->Label() )
    );
    saveResult( ( result ) );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CMoveStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_MOVE );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    statement->Destination()->Accept( this );
    std::shared_ptr<const CExpression> destination = ( lastExpression );
    statement->Source()->Accept( this );
    std::shared_ptr<const CExpression> source = ( lastExpression );

    std::shared_ptr<CStatement> result(
        new CMoveStatement(
            ( destination ),
            ( source )
        )
    );
    saveResult( ( result ) );

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CSeqStatement* statement ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_SEQ );
    onNodeEnter( nodeName );

    ++distanceToSeqStack.back();

    if ( distanceToSeqStack.back() > 1 ) {
        statementStack.emplace_back( new std::vector<std::shared_ptr<const CStatement>>() );
    }

    distanceToSeqStack.push_back( 0 );
    std::cout << nodeName << ". Enter: " << statementStack.back()->size() << std::endl;
    statement->LeftStatement()->Accept( this );
    statement->RightStatement()->Accept( this );
    std::cout << nodeName << ". Exit: " << statementStack.back()->size() << std::endl;

    distanceToSeqStack.pop_back();
    if ( distanceToSeqStack.back() > 1 ) {
        CStatementList* statementList = new CStatementList();
        for ( auto it = statementStack.back()->begin(); it != statementStack.back()->end(); ++it ) {
            statementList->Add(*it);
        }
        updateLastStatement( statementList );
        statementStack.pop_back();
    }

    --distanceToSeqStack.back();

    onNodeExit( nodeName );
}

/*__________  Lists __________*/

void CSeqLinearizerVisitor::Visit( const CExpressionList* list ) {
    std::string nodeName = generateNodeName( CNodeNames::EXP_LIST );
    onNodeEnter( nodeName );

    CExpressionList* newList = new CExpressionList();

    const std::vector<std::shared_ptr<const CExpression>>& expressions = list->Expressions();
    for ( auto it = expressions.begin(); it != expressions.end(); ++it ) {
        ( *it )->Accept( this );
        newList->Add( ( lastExpression ) );
    }

    updateLastExpressionList( newList );

    onNodeExit( nodeName );
}

void CSeqLinearizerVisitor::Visit( const CStatementList* list ) {
    std::string nodeName = generateNodeName( CNodeNames::STAT_LIST );
    onNodeEnter( nodeName );

    // such calls should never happen
    assert( false );

    onNodeExit( nodeName );
}
