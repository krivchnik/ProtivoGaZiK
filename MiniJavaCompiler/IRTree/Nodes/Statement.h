#pragma once

#include <memory>
#include <IRTree/Label.h>
#include <IRTree/Nodes/VisitorTarget.h>

namespace IRTree {

    class CStatement : public IVisitorTarget {
    public:
        virtual std::shared_ptr<const CStatement> Canonize() const = 0;

        virtual std::shared_ptr<const CStatement> Clone() const = 0;
    };


    enum class TLogicOperatorType : char {
        LOT_EQ,
        LOT_NE,
        LOT_LT,
        LOT_GT,
        LOT_LE,
        LOT_GE,
        LOT_ULT,
        LOT_ULE,
        LOT_UGT,
        LOT_UGE
    };

    inline std::string to_string(TLogicOperatorType operation);
//-----------------------------------------------------------------------------------------------//
    class CExpression;

    class CMoveStatement : public CStatement {
    public:
        CMoveStatement(const CExpression *_destination,
                       const CExpression *_source);

        CMoveStatement(std::shared_ptr<const CExpression> _destination,
                       std::shared_ptr<const CExpression> _source);

        ~CMoveStatement();

        const CExpression *Destination() const {
            return destination.get();
        }

        const CExpression *Source() const {
            return source.get();
        }

        void Accept(IVisitor *visitor) const override {
            visitor->Visit(this);
        }

        virtual std::shared_ptr<const CStatement> Canonize() const override;

        virtual std::shared_ptr<const CStatement> Clone() const override;

    private:
        std::shared_ptr<const CExpression> destination;
        std::shared_ptr<const CExpression> source;
    };

//-----------------------------------------------------------------------------------------------//

    class CExpStatement : public CStatement {
    public:
        CExpStatement(const CExpression *_expression);

        CExpStatement(std::shared_ptr<const CExpression> _expression);

        ~CExpStatement();

        const CExpression *Expression() const { return expression.get(); }

        void Accept(IVisitor *visitor) const override { visitor->Visit(this); }

        virtual std::shared_ptr<const CStatement> Canonize() const override;

        virtual std::shared_ptr<const CStatement> Clone() const override;

    private:
        std::shared_ptr<const CExpression> expression;
    };

//-----------------------------------------------------------------------------------------------//

    class CJumpStatement : public CStatement {
    public:
        CJumpStatement(CLabel _target);

        ~CJumpStatement();

        CLabel Target() const { return target; }

        void Accept(IVisitor *visitor) const override { visitor->Visit(this); }

        virtual std::shared_ptr<const CStatement> Canonize() const override;

        virtual std::shared_ptr<const CStatement> Clone() const override;

    private:
        CLabel target;
    };

//-----------------------------------------------------------------------------------------------//

    class CJumpConditionalStatement : public CStatement {
    public:
        CJumpConditionalStatement(TLogicOperatorType _operation,
                                  const CExpression *left,
                                  const CExpression *right,
                                  CLabel _labelTrue,
                                  CLabel _labelFalse);

        CJumpConditionalStatement(TLogicOperatorType _operation,
                                  std::shared_ptr<const CExpression> left,
                                  std::shared_ptr<const CExpression> right,
                                  CLabel _labelTrue,
                                  CLabel _labelFalse);

        ~CJumpConditionalStatement();

        const CExpression *LeftOperand() const { return leftOperand.get(); }

        const CExpression *RightOperand() const { return rightOperand.get(); }

        CLabel TrueLabel() const { return labelTrue; }

        CLabel FalseLabel() const { return labelFalse; }

        TLogicOperatorType Operation() const { return operation; }

        void Accept(IVisitor *visitor) const override { visitor->Visit(this); }

        virtual std::shared_ptr<const CStatement> Canonize() const override;

        virtual std::shared_ptr<const CStatement> Clone() const override;

    private:
        std::shared_ptr<const CExpression> leftOperand;
        std::shared_ptr<const CExpression> rightOperand;
        CLabel labelTrue;
        CLabel labelFalse;
        TLogicOperatorType operation;
    };

//-----------------------------------------------------------------------------------------------//

    class CSeqStatement : public CStatement {
    public:
        CSeqStatement(const CStatement *_left, const CStatement *_right);

        CSeqStatement(std::shared_ptr<const CStatement> _left, std::shared_ptr<const CStatement> _right);

        const CStatement *LeftStatement() const { return leftStatement.get(); }

        const CStatement *RightStatement() const { return rightStatement.get(); }

        void Accept(IVisitor *visitor) const override { visitor->Visit(this); }

        virtual std::shared_ptr<const CStatement> Canonize() const override;

        virtual std::shared_ptr<const CStatement> Clone() const override;

    private:
        std::shared_ptr<const CStatement> leftStatement;
        std::shared_ptr<const CStatement> rightStatement;
    };

//-----------------------------------------------------------------------------------------------//

    class CLabelStatement : public CStatement {
    public:
        CLabelStatement(CLabel _label);

        ~CLabelStatement();

        CLabel Label() const { return label; }

        void Accept(IVisitor *visitor) const override { visitor->Visit(this); }

        virtual std::shared_ptr<const CStatement> Canonize() const override;

        virtual std::shared_ptr<const CStatement> Clone() const override;

    private:
        CLabel label;
    };

    class CStatementList : public CStatement {
    public:
        CStatementList() = default;

        CStatementList(const CStatement *statement) { Add(statement); }

        CStatementList(std::shared_ptr<const CStatement> statement) { Add(statement); }

        void Add(const CStatement *statement) { statements.emplace_back(statement); }

        void Add(std::shared_ptr<const CStatement> statement) { statements.push_back(statement); }

        const std::vector<std::shared_ptr<const CStatement> > &Statements() const { return statements; }

        void Accept(IVisitor *visitor) const override { visitor->Visit(this); }

        std::shared_ptr<const CStatement> Clone() const;

        std::shared_ptr<const CStatement> Canonize() const;

    private:
        std::vector<std::shared_ptr<const CStatement>> statements;
    };

} // namespace IRTree
