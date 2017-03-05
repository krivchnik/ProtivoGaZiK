#include <IRTree/Nodes/Expression.h>

#include <IRTree/Nodes/Statement.h>
#include <assert.h>
#include <IRTree/Canonization.h>

using namespace IRTree;

CConstExpression::CConstExpression(int _value) : value(_value) {}

std::shared_ptr<const CExpression> CConstExpression::Canonize() {
    return Clone();
}

std::shared_ptr<const CExpression> CConstExpression::Clone() const {
    return std::shared_ptr<const CExpression>(new CConstExpression(value));
}

CNameExpression::CNameExpression(CLabel _label) : label(_label) {}

std::shared_ptr<const CExpression> CNameExpression::Canonize() {
    return Clone();
}

std::shared_ptr<const CExpression> CNameExpression::Clone() const {
    return std::shared_ptr<const CExpression>(new CNameExpression(label));
}

CTempExpression::CTempExpression(const CTemp &_temporary) : temporary(_temporary) {}

std::shared_ptr<const CExpression> CTempExpression::Canonize() {
    return Clone();
}

std::shared_ptr<const CExpression> CTempExpression::Clone() const {
    return std::shared_ptr<const CExpression>(new CTempExpression(temporary));
}

CBinaryExpression::CBinaryExpression(TOperatorType _operation, const CExpression *left, const CExpression *right)
        : operation(_operation), leftOperand(left), rightOperand(right) {}

CBinaryExpression::CBinaryExpression(TOperatorType _operation, std::shared_ptr<const CExpression> left,
                                     std::shared_ptr<const CExpression> right)
        : operation(_operation), leftOperand(left), rightOperand(right) {}

std::shared_ptr<const CExpression> CBinaryExpression::Canonize() {
    std::shared_ptr<const CExpression> expressionLeftCanon = leftOperand->Canonize();
    std::shared_ptr<const CExpression> expressionRightCanon = rightOperand->Canonize();
    std::shared_ptr<const CExpression> result;
    const CEseqExpression *eseqExpressionLeftCanon = CastToEseqExpression(expressionLeftCanon.get());
    const CEseqExpression *eseqExpressionRightCanon = CastToEseqExpression(expressionRightCanon.get());

    if (eseqExpressionLeftCanon) {
        result = std::shared_ptr<const CExpression>(
                new CEseqExpression(
                        eseqExpressionLeftCanon->Statement()->Clone(),
                        std::shared_ptr<const CExpression>(
                                new CBinaryExpression(
                                        operation,
                                        eseqExpressionLeftCanon->Expression()->Clone(),
                                        expressionRightCanon
                                )
                        )
                )
        );
    } else if (eseqExpressionRightCanon) {
        if (AreCommuting(eseqExpressionRightCanon->Statement(), expressionLeftCanon.get())) {
            result = std::shared_ptr<const CExpression>(
                    new CEseqExpression(
                            eseqExpressionRightCanon->Statement()->Clone(),
                            std::shared_ptr<const CExpression>(
                                    new CBinaryExpression(
                                            operation,
                                            expressionLeftCanon,
                                            eseqExpressionRightCanon->Expression()->Clone()
                                    )
                            ))
            );
        } else {
            CTemp temp;
            result = std::shared_ptr<const CExpression>(
                    new CEseqExpression(
                            new CMoveStatement(
                                    std::shared_ptr<const CExpression>(
                                            new CTempExpression(temp)
                                    ),
                                    expressionLeftCanon
                            ),
                            new CEseqExpression(
                                    eseqExpressionRightCanon->Statement()->Clone(),
                                    std::shared_ptr<const CExpression>(
                                            new CBinaryExpression(
                                                    operation,
                                                    std::shared_ptr<const CExpression>(
                                                            new CTempExpression(temp)
                                                    ),
                                                    eseqExpressionRightCanon->Expression()->Clone()
                                            )
                                    ))
                    )
            );
        }
    } else {
        result = std::shared_ptr<const CExpression>(
                new CBinaryExpression(
                        operation,
                        expressionLeftCanon,
                        expressionRightCanon
                )
        );
    }

    return result;
}

std::shared_ptr<const CExpression> CBinaryExpression::Clone() const {
    return std::shared_ptr<const CExpression>(new CBinaryExpression(
            operation, leftOperand->Clone(), rightOperand->Clone())
    );
}

CMemExpression::CMemExpression(const CExpression *_address) : address(_address) {}

CMemExpression::CMemExpression(std::shared_ptr<const CExpression>
                               _address) : address(_address) {}

std::shared_ptr<const CExpression> CMemExpression::Canonize() {
    assert(false);
    std::shared_ptr<const CExpression> expressionCanon = address->Canonize();
    std::shared_ptr<const CExpression> result;
    const CEseqExpression *eseqExpressionCanon = CastToEseqExpression(expressionCanon.get());
    if (eseqExpressionCanon) {
        result = std::shared_ptr<const CExpression>(
                new CEseqExpression(
                        eseqExpressionCanon->Statement()->Clone(),
                        std::shared_ptr<const CExpression>(
                                new CMemExpression(
                                        eseqExpressionCanon->Expression()->Clone()
                                )
                        )
                )
        );
    } else {
        result = std::shared_ptr<const CExpression>(
                new CMemExpression(expressionCanon)
        );
    }

    return result;
}


std::shared_ptr<const CExpression> CMemExpression::Clone() const {
    return std::shared_ptr<const CExpression>(new CMemExpression(address->Clone()));
}

CCallExpression::CCallExpression(const CExpression *func, const CExpressionList *args)
        : function(func), arguments(args) {}

CCallExpression::CCallExpression(std::shared_ptr<const CExpression>
                                 func, std::shared_ptr<const CExpressionList>
                                 args)
        : function(func), arguments(args) {}

std::shared_ptr<const CExpression> CCallExpression::Canonize() {
    std::shared_ptr<const CExpression> functionCanon = function->Canonize();
    std::shared_ptr<const CExpressionList> argumentsCanon = arguments->Canonize();
    return std::shared_ptr<const CExpression>(
            new CCallExpression(
                    functionCanon,
                    argumentsCanon)
    );
}

std::shared_ptr<const CExpression> CCallExpression::Clone() const {
    return std::shared_ptr<const CExpression>(new CCallExpression(
            function->Clone(), arguments->Clone()
    ));
}

CEseqExpression::CEseqExpression(const CStatement *_statement, const CExpression *_expression)
        : statement(_statement), expression(_expression) {}

CEseqExpression::CEseqExpression(std::shared_ptr<const CStatement>
                                 _statement,
                                 std::shared_ptr<const CExpression>
                                 _expression)
        : statement(_statement), expression(_expression) {}

std::shared_ptr<const CExpression> CEseqExpression::Canonize() {
    std::shared_ptr<const CStatement> statementCanon = statement->Canonize();
    std::shared_ptr<const CExpression> expressionCanon = expression->Canonize();

    std::shared_ptr<const CExpression> result;
    const CEseqExpression *eseqExpressionCanon = CastToEseqExpression( expressionCanon.get());
    if (eseqExpressionCanon) {
        result = std::shared_ptr<const CExpression>(
                new CEseqExpression(
                        std::shared_ptr<const CStatement>(
                                new CSeqStatement(
                                        statementCanon,
                                        eseqExpressionCanon->Statement()->Clone()
                                )
                        ),
                        eseqExpressionCanon->Expression()->Clone()
                )
        );
    } else {
        result = std::shared_ptr<const CExpression>(
                new CEseqExpression(
                        statementCanon,
                        expressionCanon
                )
        );
    }
    return result;
}

std::shared_ptr<const CExpression> CEseqExpression::Clone() const {
    return std::shared_ptr<const CExpression>(new CEseqExpression(
            statement->Clone(), expression->Clone()
    ));
}

std::shared_ptr<const CExpression> CExpression::Canonize() {
    assert(false);
    return std::shared_ptr<const CExpression>();
}

std::shared_ptr<const CExpression> CExpression::Clone() const {
    assert(false);
    return std::shared_ptr<const CExpression>();
}
