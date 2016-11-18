#pragma once

#include <Nodes/IExpression.h>
#include <Nodes/CIdExpression.h>

class CConstructClassExpression : public IExpression {
public:
    CConstructClassExpression(const Location location,
                              const std::shared_ptr<CIdExpression> &classID);
    const std::shared_ptr<CIdExpression> &getClassID() const;
    void Accept(IVisitor*);
private:
    std::shared_ptr<CIdExpression> classID;
};

