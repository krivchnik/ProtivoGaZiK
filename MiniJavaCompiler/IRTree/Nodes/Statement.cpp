#include <IRTree/Nodes/Statement.h>

#include <IRTree/Nodes/Expression.h>

using namespace IRTree;

IStatement::~IStatement() {}

CStatement::CStatement() {}
CStatement::~CStatement() {}

CMoveStatement::CMoveStatement( const CExpression* _destination, const CExpression* _source )
    : destination( _destination ), source( _source ) {}
CMoveStatement::CMoveStatement( std::shared_ptr<const CExpression> _destination, std::shared_ptr<const CExpression> _source )
    : destination( _destination ), source( _source ) {}
CMoveStatement::~CMoveStatement() {}

CExpStatement::CExpStatement( const CExpression* _expression ) : expression( _expression ) {}
CExpStatement::CExpStatement( std::shared_ptr<const CExpression> _expression )
    : expression( _expression ) {}
CExpStatement::~CExpStatement() {}

CJumpStatement::CJumpStatement( CLabel _target )
    : target( _target ) {}
CJumpStatement::~CJumpStatement() {}

CJumpConditionalStatement::CJumpConditionalStatement( TLogicOperatorType _operation,
    const CExpression* left, const CExpression* right,
    CLabel _labelTrue, CLabel _labelFalse )
        : leftOperand( left ), rightOperand( right ),
        labelTrue( _labelTrue ), labelFalse( _labelFalse ), operation( _operation ) {}
CJumpConditionalStatement::CJumpConditionalStatement( TLogicOperatorType _operation,
    std::shared_ptr<const CExpression> left, std::shared_ptr<const CExpression> right,
    CLabel _labelTrue, CLabel _labelFalse )
        : leftOperand( left ), rightOperand( right ),
        labelTrue( _labelTrue ), labelFalse( _labelFalse ), operation( _operation ) {}
CJumpConditionalStatement::~CJumpConditionalStatement() {}

CSeqStatement::CSeqStatement(std::shared_ptr<const CLabelStatement> &&_left, std::shared_ptr<const CStatement> &&_right )
    : leftStatement( _left ), rightStatement( _right ) {}
CSeqStatement::CSeqStatement( std::shared_ptr<const CStatement>&& _left, std::shared_ptr<const CStatement>&& _right )
    : leftStatement( _left ), rightStatement( _right ) {}
CSeqStatement::~CSeqStatement() {}

CLabelStatement::CLabelStatement( CLabel _label ) : label( _label ) {}
CLabelStatement::~CLabelStatement() {}
