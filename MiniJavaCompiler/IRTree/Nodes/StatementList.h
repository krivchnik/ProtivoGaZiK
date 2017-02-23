#pragma once

#include <memory>
#include <vector>

#include <IRTree/Visitors/Visitor.h>
#include <IRTree/Nodes/VisitorTarget.h>

namespace IRTree {

class CStatement;

class CStatementList : public IVisitorTarget {
public:
    CStatementList() = default;

    CStatementList( const CStatement* statement ) { Add( statement ); }
    CStatementList( std::shared_ptr<const CStatement> statement ) { Add( statement ); }

    void Add( const CStatement* statement )
        { statements.emplace_back( statement ); }
    void Add( std::shared_ptr<const CStatement> statement )
        { statements.push_back( statement ); }

    const std::vector< std::shared_ptr<const CStatement> >& Statements() const { return statements; }

    void Accept( IVisitor* visitor ) const override { visitor->Visit( this ); }

private:
    std::vector< std::shared_ptr<const CStatement> > statements;
};

}
