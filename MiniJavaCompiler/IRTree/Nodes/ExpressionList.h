#pragma once

#include <memory>
#include <vector>

#include <IRTree/Visitors/Visitor.h>
#include <IRTree/Nodes/VisitorTarget.h>

namespace IRTree {

class CExpression;

class CExpressionList : public IVisitorTarget {
public:
    CExpressionList() = default;

    CExpressionList( const CExpression* expression ) { Add( expression ); }
    CExpressionList( std::shared_ptr<const CExpression> expression ) { Add( expression ); }

    void Add( const CExpression* expression )
        { expressions.emplace_back( expression ); }

    void Add( std::shared_ptr<const CExpression> expression )
        { expressions.push_back( expression ); }

    const std::vector< std::shared_ptr<const CExpression> >& Expressions() const { return expressions; }

    void Accept( IVisitor* visitor ) const override { visitor->Visit( this ); }
    std::shared_ptr<const CExpressionList> Clone() const;
    std::shared_ptr<const CExpressionList> Canonize();
private:
    std::vector< std::shared_ptr<const CExpression> > expressions;
};

}
