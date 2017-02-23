#include <IRTree/SubtreeWrapper.h>
#include <IRTree/Temporary.h>

using namespace IRTree;

std::shared_ptr<const CExpression> CExpressionWrapper::ToExpression() {
    return expression;
}

std::shared_ptr<const CStatement> CExpressionWrapper::ToStatement() {
    return std::shared_ptr<const CStatement>( new CExpStatement( expression ) );
}

std::shared_ptr<const CStatement> CExpressionWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
    return std::shared_ptr<const CStatement>(
        new CJumpConditionalStatement(
            TLogicOperatorType::LOT_NE,
            expression,
            std::shared_ptr<const CExpression>( new CConstExpression( 0 ) ),
            labelTrue,
            labelFalse
        )
    );
}


std::shared_ptr<const CExpression> CStatementWrapper::ToExpression() {
    // such calls should never happen
    assert( false );
    // return std::move( std::shared_ptr<const CExpression>(
    //     new CEseqExpression( statement, new CConstExpression( 0 ) )
    // ) );
}

std::shared_ptr<const CStatement> CStatementWrapper::ToStatement() {
    return statement;
}

std::shared_ptr<const CStatement> CStatementWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
    // such calls should never happen
    assert( false );
}


std::shared_ptr<const CExpression> CConditionalWrapper::ToExpression() {
    CTempExpression* tempExpression = new CTempExpression( CTemp() );
    CLabel labelFalse;
    CLabel labelTrue;
    return std::shared_ptr<const CExpression> (
        new CEseqExpression(
            new CSeqStatement(
                new CMoveStatement( tempExpression, new CConstExpression( 1 ) ),
                new CSeqStatement(
                    ToConditional( labelTrue, labelFalse ),
                    std::shared_ptr<const CSeqStatement>(
                        new CSeqStatement(
                            new CLabelStatement( labelFalse ),
                            new CSeqStatement(
                                new CMoveStatement( tempExpression, new CConstExpression( 0 ) ),
                                new CLabelStatement( labelTrue )
                            )
                        )
                    )
                )
            ),
            tempExpression
        )
    );
}

std::shared_ptr<const CStatement> CConditionalWrapper::ToStatement() {
    /* TODO; */
}

std::shared_ptr<const CStatement> CRelativeConditionalWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
    return std::shared_ptr<const CStatement>(
        new CJumpConditionalStatement(
            operatorType,
            operandLeft,
            operandRight,
            labelTrue,
            labelFalse
        )
    );
}

std::shared_ptr<const CStatement> CAndConditionalWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
    CLabel labelMiddle;
    return std::shared_ptr<const CStatement>(
        new CSeqStatement(
            operandLeft->ToConditional( labelMiddle, labelFalse ),
            std::move( std::shared_ptr<const CSeqStatement>(
                new CSeqStatement(
                        std::move( std::shared_ptr<const CLabelStatement>( new CLabelStatement( labelMiddle ) ) ),
                        std::move( operandRight->ToConditional( labelTrue, labelFalse ) )
                )
            ) )
        )
    );
}

std::shared_ptr<const CStatement> COrConditionalWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
    CLabel labelMiddle;
    return std::move( std::shared_ptr<const CStatement>(
        new CSeqStatement(
                std::move(operandLeft->ToConditional(labelTrue, labelMiddle ) ),
                std::move(std::shared_ptr<const CSeqStatement>(
                        new CSeqStatement(
                                std::move(std::shared_ptr<const CLabelStatement>(new CLabelStatement(labelMiddle ) ) ),
                                std::move(operandRight->ToConditional(labelTrue, labelFalse ) )
                        )
                ) )
        )
    ) );
}

std::shared_ptr<const CStatement> CNegateConditionalWrapper::ToConditional( CLabel labelTrue, CLabel labelFalse ) {
    return wrapper->ToConditional( labelFalse, labelTrue ); // reversed order of arguments
}
