#include <IRTree/Nodes/Statement.h>

#include <IRTree/Nodes/Expression.h>
#include <assert.h>

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

std::shared_ptr<const IStatement> CExpStatement::Canonize(int eseqCount) {
    assert(false);
    return CStatement::Canonize(eseqCount);
}

CJumpStatement::CJumpStatement( CLabel _target )
    : target( _target ) {}
CJumpStatement::~CJumpStatement() {}

std::shared_ptr<const IStatement> CJumpStatement::Canonize(int eseqCount) {
    assert(false);
    return CStatement::Canonize(eseqCount);
}

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

std::shared_ptr<const IStatement> CJumpConditionalStatement::Canonize(int eseqCount) {
    assert(false);
    return CStatement::Canonize(eseqCount);
}

CSeqStatement::CSeqStatement(const CStatement* _left, const CStatement* _right )
    : leftStatement( _left ), rightStatement( _right ) {}
CSeqStatement::CSeqStatement( std::shared_ptr<const CStatement> _left, std::shared_ptr<const CStatement> _right )
    : leftStatement( _left ), rightStatement( _right ) {}

std::shared_ptr<const IStatement> CSeqStatement::Canonize(int eseqCount) {
    assert(false);
    return CStatement::Canonize(eseqCount);
}

CLabelStatement::CLabelStatement( CLabel _label ) : label( _label ) {}
CLabelStatement::~CLabelStatement() {}

std::shared_ptr<const IStatement> CLabelStatement::Canonize(int eseqCount) {
    assert(false);
    return CStatement::Canonize(eseqCount);
}
