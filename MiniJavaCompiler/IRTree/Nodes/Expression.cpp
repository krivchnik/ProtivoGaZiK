#include <IRTree/Nodes/Expression.h>

#include <IRTree/Nodes/Statement.h>

using namespace IRTree;

IExpression::~IExpression() {}

CExpression::~CExpression() {}

CConstExpression::CConstExpression( int _value ) : value( _value ) {}
CConstExpression::~CConstExpression() {}

CNameExpression::CNameExpression( CLabel _label ) : label( _label ) {}
CNameExpression::~CNameExpression() {}

CTempExpression::CTempExpression( CTemp _temporary ) : temporary( _temporary ) {}
CTempExpression::~CTempExpression() {}

CBinaryExpression::CBinaryExpression( TOperatorType _operation, const CExpression* left, const CExpression* right )
    : operation( _operation ), leftOperand( left ), rightOperand( right ) {}
CBinaryExpression::CBinaryExpression( TOperatorType _operation, std::shared_ptr<const CExpression> left, std::shared_ptr<const CExpression> right )
    : operation( _operation ), leftOperand( left), rightOperand( right ) {}
CBinaryExpression::~CBinaryExpression() {}

CMemExpression::CMemExpression( const CExpression* _address ) : address( _address ) {}
CMemExpression::CMemExpression( std::shared_ptr<const CExpression> _address ) : address( _address ) {}
CMemExpression::~CMemExpression() {}

CCallExpression::CCallExpression( const CExpression* func, const CExpressionList* args )
    : function( func ), arguments( args ) {}
CCallExpression::CCallExpression( std::shared_ptr<const CExpression> func, std::shared_ptr<const CExpressionList> args )
    : function( func ), arguments( args ) {}
CCallExpression::~CCallExpression() {}

CEseqExpression::CEseqExpression( const CStatement* _statement, const CExpression* _expression )
    : statement( _statement ), expression( _expression ) {}
CEseqExpression::CEseqExpression( std::shared_ptr<const CStatement> _statement, std::shared_ptr<const CExpression> _expression )
    : statement( _statement ), expression( _expression ) {}
CEseqExpression::~CEseqExpression() {}
