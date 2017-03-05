#include <IRTree/Nodes/ExpressionList.h>

#include <cassert>

#include <IRTree/Nodes/Expression.h>

using namespace IRTree;

std::shared_ptr<const CExpressionList> CExpressionList::Clone() const {
    CExpressionList* newList = new CExpressionList();
    for ( auto it = expressions.begin(); it != expressions.end(); ++it ) {
        newList->Add( ( *it )->Clone() );
    }
    return std::shared_ptr<const CExpressionList>( newList );
}

std::shared_ptr<const CExpressionList> CExpressionList::Canonize() const {
    CExpressionList* newList = new CExpressionList();
    for ( auto it = expressions.begin(); it != expressions.end(); ++it ) {
        newList->Add( ( *it )->Canonize() );
    }
    return std::shared_ptr<const CExpressionList>( newList );
}
