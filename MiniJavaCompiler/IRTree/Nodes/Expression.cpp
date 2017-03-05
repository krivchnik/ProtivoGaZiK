#include <IRTree/Nodes/Expression.h>

#include <IRTree/Nodes/Statement.h>
#include <assert.h>

using namespace IRTree;

CConstExpression::CConstExpression( int _value ) : value( _value ) {}

std::shared_ptr<const IExpression> CConstExpression::Canonize(int eseqCount) {
    assert(false);
    return CExpression::Canonize(eseqCount);
}

CNameExpression::CNameExpression( CLabel _label ) : label( _label ) {}

std::shared_ptr<const IExpression> CNameExpression::Canonize(int eseqCount) {
    assert(false);
    return CExpression::Canonize(eseqCount);
}

CTempExpression::CTempExpression( const CTemp& _temporary ) : temporary( _temporary ) {}

std::shared_ptr<const IExpression> CTempExpression::Canonize(int eseqCount) {
    assert(false);
    return CExpression::Canonize(eseqCount);
}

CBinaryExpression::CBinaryExpression( TOperatorType _operation, const CExpression* left, const CExpression* right )
    : operation( _operation ), leftOperand( left ), rightOperand( right ) {}
CBinaryExpression::CBinaryExpression( TOperatorType _operation, std::shared_ptr<const CExpression> left, std::shared_ptr<const CExpression> right )
    : operation( _operation ), leftOperand( left), rightOperand( right ) {}

std::shared_ptr<const IExpression> CBinaryExpression::Canonize(int eseqCount) {
    assert(false);
    return CExpression::Canonize(eseqCount);
}

CMemExpression::CMemExpression( const CExpression* _address ) : address( _address ) {}
CMemExpression::CMemExpression( std::shared_ptr<const CExpression> _address ) : address( _address ) {}

std::shared_ptr<const IExpression> CMemExpression::Canonize(int eseqCount) {
    assert(false);
    return CExpression::Canonize(eseqCount);
}

CCallExpression::CCallExpression( const CExpression* func, const CExpressionList* args )
    : function( func ), arguments( args ) {}
CCallExpression::CCallExpression( std::shared_ptr<const CExpression> func, std::shared_ptr<const CExpressionList> args )
    : function( func ), arguments( args ) {}

std::shared_ptr<const IExpression> CCallExpression::Canonize(int eseqCount) {
    assert(false);
    return CExpression::Canonize(eseqCount);
}

CEseqExpression::CEseqExpression( const CStatement* _statement, const CExpression* _expression )
    : statement( _statement ), expression( _expression ) {}
CEseqExpression::CEseqExpression( std::shared_ptr<const CStatement> _statement, std::shared_ptr<const CExpression> _expression )
    : statement( _statement ), expression( _expression ) {}

std::shared_ptr<const IExpression> CEseqExpression::Canonize(int eseqCount) {
    assert(false);
    return CExpression::Canonize(eseqCount);
}

std::shared_ptr<const IExpression> CExpression::Canonize(int eseqCount) {
    assert(false);
    return std::shared_ptr<const IExpression>();
}
