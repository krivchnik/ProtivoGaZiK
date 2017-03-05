#include <IRTree/Nodes/Expression.h>

#include <IRTree/Nodes/Statement.h>
#include <assert.h>

using namespace IRTree;

CConstExpression::CConstExpression( int _value ) : value( _value ) {}

std::shared_ptr<const IExpression> CConstExpression::Canonize() {
    assert(false);
    return CExpression::Canonize();
}

std::shared_ptr<const IExpression> CConstExpression::Clone() const {
    assert(false);
    return CExpression::Clone();
}

CNameExpression::CNameExpression( CLabel _label ) : label( _label ) {}

std::shared_ptr<const IExpression> CNameExpression::Canonize() {
    assert(false);
    return CExpression::Canonize();
}

std::shared_ptr<const IExpression> CNameExpression::Clone() const {
    assert(false);
    return CExpression::Clone();
}

CTempExpression::CTempExpression( const CTemp& _temporary ) : temporary( _temporary ) {}

std::shared_ptr<const IExpression> CTempExpression::Canonize() {
    assert(false);
    return CExpression::Canonize();
}

std::shared_ptr<const IExpression> CTempExpression::Clone() const {
    assert(false);
    return CExpression::Clone();
}

CBinaryExpression::CBinaryExpression( TOperatorType _operation, const CExpression* left, const CExpression* right )
    : operation( _operation ), leftOperand( left ), rightOperand( right ) {}
CBinaryExpression::CBinaryExpression( TOperatorType _operation, std::shared_ptr<const CExpression> left, std::shared_ptr<const CExpression> right )
    : operation( _operation ), leftOperand( left), rightOperand( right ) {}

std::shared_ptr<const IExpression> CBinaryExpression::Canonize() {
    assert(false);
    return CExpression::Canonize();
}

std::shared_ptr<const IExpression> CBinaryExpression::Clone() const {
    assert(false);
    return CExpression::Clone();
}

CMemExpression::CMemExpression( const CExpression* _address ) : address( _address ) {}
CMemExpression::CMemExpression( std::shared_ptr<const CExpression> _address ) : address( _address ) {}

std::shared_ptr<const IExpression> CMemExpression::Canonize() {
    assert(false);
    return CExpression::Canonize();
}

std::shared_ptr<const IExpression> CMemExpression::Clone() const {
    assert(false);
    return CExpression::Clone();
}

CCallExpression::CCallExpression( const CExpression* func, const CExpressionList* args )
    : function( func ), arguments( args ) {}
CCallExpression::CCallExpression( std::shared_ptr<const CExpression> func, std::shared_ptr<const CExpressionList> args )
    : function( func ), arguments( args ) {}

std::shared_ptr<const IExpression> CCallExpression::Canonize() {
    assert(false);
    return CExpression::Canonize();
}

std::shared_ptr<const IExpression> CCallExpression::Clone() const {
    assert(false);
    return CExpression::Clone();
}

CEseqExpression::CEseqExpression( const CStatement* _statement, const CExpression* _expression )
    : statement( _statement ), expression( _expression ) {}
CEseqExpression::CEseqExpression( std::shared_ptr<const CStatement> _statement, std::shared_ptr<const CExpression> _expression )
    : statement( _statement ), expression( _expression ) {}

std::shared_ptr<const IExpression> CEseqExpression::Canonize() {
    assert(false);
    return CExpression::Canonize();
}

std::shared_ptr<const IExpression> CEseqExpression::Clone() const {
    assert(false);
    return CExpression::Clone();
}

std::shared_ptr<const IExpression> CExpression::Canonize() {
    assert(false);
    return std::shared_ptr<const IExpression>();
}

std::shared_ptr<const IExpression> CExpression::Clone() const {
    assert(false);
    return std::shared_ptr<const IExpression>();
}
