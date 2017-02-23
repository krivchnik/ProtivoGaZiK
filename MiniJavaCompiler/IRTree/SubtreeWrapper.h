#pragma once

#include <cassert>
#include <memory>
#include <IRTree/Label.h>
#include <IRTree/Nodes/Expression.h>
#include <IRTree/Nodes/Statement.h>

namespace IRTree {

// Base Subtree Wrappers

class ISubtreeWrapper {
public:
    virtual ~ISubtreeWrapper() = default;
    virtual std::shared_ptr<const CExpression> ToExpression() = 0;
    virtual std::shared_ptr<const CStatement> ToStatement() = 0;
    virtual std::shared_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) = 0;
};

class CExpressionWrapper : public ISubtreeWrapper {
public:
    CExpressionWrapper( const CExpression* _expression )
        : expression( _expression ) {}
    CExpressionWrapper( std::shared_ptr<const CExpression> _expression )
        : expression( _expression ) {}

    virtual std::shared_ptr<const CExpression> ToExpression() override;
    virtual std::shared_ptr<const CStatement> ToStatement() override;
    virtual std::shared_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
private:
    std::shared_ptr<const CExpression> expression;
};

class CStatementWrapper : public ISubtreeWrapper {
public:
    explicit CStatementWrapper( const CStatement* _statement )
        : statement( _statement ) {}
    explicit CStatementWrapper( std::shared_ptr<const CStatement> _statement ) : statement( _statement ) {}
    virtual ~CStatementWrapper() = default;

    virtual std::shared_ptr<const CExpression> ToExpression() override;
    virtual std::shared_ptr<const CStatement> ToStatement() override;
    virtual std::shared_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
private:
    std::shared_ptr<const CStatement> statement;
};

class CConditionalWrapper : public ISubtreeWrapper {
public:
    CConditionalWrapper() = default;
    virtual ~CConditionalWrapper() = default;

    virtual std::shared_ptr<const CExpression> ToExpression() override;
    virtual std::shared_ptr<const CStatement> ToStatement() override;
    virtual std::shared_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override = 0;
};

// Specific Subtree Wrappers

class CRelativeConditionalWrapper : public CConditionalWrapper {
public:
    CRelativeConditionalWrapper(
        TLogicOperatorType _operatorType,
        const CExpression* _operandLeft,
        const CExpression* _operandRight
    ) : operatorType( _operatorType ),
        operandLeft( _operandLeft ),
        operandRight( _operandRight ) {}

    CRelativeConditionalWrapper(
        TLogicOperatorType _operatorType,
        std::shared_ptr<const CExpression> _operandLeft,
        std::shared_ptr<const CExpression> _operandRight
    ) : operatorType( _operatorType ),
        operandLeft( _operandLeft ),
        operandRight( _operandRight ) {}

    virtual std::shared_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
private:
    TLogicOperatorType operatorType;
    std::shared_ptr<const CExpression> operandLeft;
    std::shared_ptr<const CExpression> operandRight;
};

class CAndConditionalWrapper : public CConditionalWrapper {
public:
    CAndConditionalWrapper( std::shared_ptr<ISubtreeWrapper> _operandLeft, std::shared_ptr<ISubtreeWrapper> _operandRight )
        : operandLeft( _operandLeft ), operandRight( _operandRight ) {}

    virtual std::shared_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
private:
    std::shared_ptr<ISubtreeWrapper> operandLeft;
    std::shared_ptr<ISubtreeWrapper> operandRight;
};

class COrConditionalWrapper : public CConditionalWrapper {
public:
    COrConditionalWrapper( std::shared_ptr<ISubtreeWrapper> _operandLeft, std::shared_ptr<ISubtreeWrapper> _operandRight )
        : operandLeft( _operandLeft ), operandRight( _operandRight ) {}

    virtual std::shared_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
private:
    std::shared_ptr<ISubtreeWrapper> operandLeft;
    std::shared_ptr<ISubtreeWrapper> operandRight;
};

class CNegateConditionalWrapper : public CConditionalWrapper {
public:
    CNegateConditionalWrapper( std::shared_ptr<ISubtreeWrapper> _wrapper )
        : wrapper( _wrapper ) {}

    virtual std::shared_ptr<const CStatement> ToConditional( CLabel labelTrue, CLabel labelFalse ) override;
private:
    std::shared_ptr<ISubtreeWrapper> wrapper;
};

}
