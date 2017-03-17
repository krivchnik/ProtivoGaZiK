#pragma once

#include <memory>

#include <IRTree/Temporary.h>
#include <IRTree/Label.h>

#include <IRTree/Visitors/Visitor.h>

#include <IRTree/Nodes/ExpressionList.h>
#include <IRTree/Nodes/Statement.h>
#include <IRTree/Nodes/VisitorTarget.h>
#include <assert.h>

namespace IRTree {

class IExpression : public IVisitorTarget {
public:
    virtual ~IExpression() {}
    virtual std::shared_ptr<const CExpression> Clone() const = 0;
    virtual std::shared_ptr<const CExpression> Canonize() const = 0;
};

class CExpression : public IExpression {
public:
    virtual ~CExpression() {}
    virtual std::shared_ptr<const CExpression> Canonize() const override;
    virtual std::shared_ptr<const CExpression> Clone() const override;
};

    std::string to_string(TLogicOperatorType operation) {
        switch (operation){
            case TLogicOperatorType::LOT_EQ:
                return "EQ";
            case TLogicOperatorType::LOT_NE:
                return "NE";
            case TLogicOperatorType::LOT_LT:
                return "LT";
            case TLogicOperatorType::LOT_GT:
                return "GT";
            case TLogicOperatorType::LOT_LE:
                return "LE";
            case TLogicOperatorType::LOT_GE:
                return "GE";
            case TLogicOperatorType::LOT_ULT:
                return "ULT";
            case TLogicOperatorType::LOT_ULE:
                return "ULE";
            case TLogicOperatorType::LOT_UGT:
                return "UGT";
            case TLogicOperatorType::LOT_UGE:
                return "UGE";
            default:
                assert(false);
        }
    }
    enum class TOperatorType : char {
        OT_Plus,
        OT_Minus,
        OT_Times,
        OT_Div,
        OT_Mod,
        OT_And,
        OT_Or
    };

    inline std::string to_string(TOperatorType operation) {
        switch (operation){
            case TOperatorType::OT_Plus:
                return "ADD";
            case TOperatorType::OT_Minus:
                return "SUB";
            case TOperatorType::OT_Times:
                return "MULT";
            case TOperatorType::OT_Div:
                return "DIV";
            case TOperatorType::OT_Mod:
                return "MOD";
            case TOperatorType::OT_And:
                assert(false);
                return "AND";
            case TOperatorType::OT_Or:
                assert(false);
                return "OR";
            default:
                assert(false);
        }
    }

//-----------------------------------------------------------------------------------------------//

class CConstExpression : public CExpression {
public:
    CConstExpression( int _value );

    int Value() const { return value; }

    void Accept( IVisitor* visitor ) const override { visitor->Visit( this ); }
    virtual std::shared_ptr<const CExpression> Canonize() const override;
    virtual std::shared_ptr<const CExpression> Clone() const override;

private:
    int value;
};

//-----------------------------------------------------------------------------------------------//

class CNameExpression : public CExpression {
public:
    CNameExpression( CLabel _label );

    const CLabel Label() const { return label; }

    void Accept( IVisitor* visitor ) const override { visitor->Visit( this ); }
    virtual std::shared_ptr<const CExpression> Canonize() const override;
    virtual std::shared_ptr<const CExpression> Clone() const override;

private:
    CLabel label;
};

//-----------------------------------------------------------------------------------------------//

class CTempExpression : public CExpression {
public:
    CTempExpression( const CTemp& _temporary );

    CTemp Temporary() const { return temporary; }

    void Accept( IVisitor* visitor ) const override { visitor->Visit( this ); }
    virtual std::shared_ptr<const CExpression> Canonize() const override;
    virtual std::shared_ptr<const CExpression> Clone() const override;

private:
    CTemp temporary;
};

//-----------------------------------------------------------------------------------------------//

class CBinaryExpression : public CExpression {
public:
    CBinaryExpression( TOperatorType _operation, const CExpression* left, const CExpression* right );
    CBinaryExpression( TOperatorType _operation, std::shared_ptr<const CExpression> left, std::shared_ptr<const CExpression> right );

    TOperatorType Operation() const { return operation; }
    const CExpression* LeftOperand() const { return leftOperand.get(); }
    const CExpression* RightOperand() const { return rightOperand.get(); }

    void Accept( IVisitor* visitor ) const override { visitor->Visit( this ); }
    virtual std::shared_ptr<const CExpression> Canonize()const  override;
    virtual std::shared_ptr<const CExpression> Clone() const override;

private:
    std::shared_ptr<const CExpression> leftOperand;
    std::shared_ptr<const CExpression> rightOperand;
    TOperatorType operation;
};

//-----------------------------------------------------------------------------------------------//

class CMemExpression : public CExpression {
public:
    CMemExpression( const CExpression* address );
    CMemExpression( std::shared_ptr<const CExpression> address );

    const CExpression* Address() const { return address.get(); }

    void Accept( IVisitor* visitor ) const override { visitor->Visit( this ); }
    virtual std::shared_ptr<const CExpression> Canonize() const override;
    virtual std::shared_ptr<const CExpression> Clone() const override;

private:
    std::shared_ptr<const CExpression> address;
};

//-----------------------------------------------------------------------------------------------//

class CCallExpression : public CExpression {
public:
    CCallExpression( const CExpression* func, const CExpressionList* args );
    CCallExpression( std::shared_ptr<const CExpression> func, std::shared_ptr<const CExpressionList> args );

    const CExpression* Function() const { return function.get(); }
    const CExpressionList* Arguments() const { return arguments.get(); }

    void Accept( IVisitor* visitor ) const override { visitor->Visit( this ); }
    virtual std::shared_ptr<const CExpression> Canonize() const override;
    virtual std::shared_ptr<const CExpression> Clone() const override;

private:
    std::shared_ptr<const CExpression> function;
    std::shared_ptr<const CExpressionList> arguments;
};

//-----------------------------------------------------------------------------------------------//
class CEseqExpression : public CExpression {
public:
    CEseqExpression( const CStatement* _statement, const CExpression* _expression );
    CEseqExpression( std::shared_ptr<const CStatement> _statement, std::shared_ptr<const CExpression> _expression );

    const CStatement* Statement() const { return statement.get(); }
    const CExpression* Expression() const { return expression.get(); }

    void Accept( IVisitor* visitor ) const override { visitor->Visit( this ); }
    virtual std::shared_ptr<const CExpression> Canonize() const override;
    virtual std::shared_ptr<const CExpression> Clone() const override;

private:
    std::shared_ptr<const CStatement> statement;
    std::shared_ptr<const CExpression> expression;
};

} // namespace IRTree
