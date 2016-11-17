//
// Created by nismohl on 12.11.16.
//

#pragma once

#include <Nodes/IExpression.h>

class CMethodCallExpression : public IExpression{
public:
    CMethodCallExpression(const Location location,
                          const std::shared_ptr<IExpression> &object,
                          const std::shared_ptr<CIdExpression> &methodId,
                          const std::shared_ptr<CListExpression> &arguments);

    const std::shared_ptr<IExpression> &getObject() const;

    const std::shared_ptr<CIdExpression> &getMethodId() const;

    const std::shared_ptr<CListExpression> &getArguments() const;

    void Accept(IVisitor*);
private:
    std::shared_ptr<IExpression> object;
    std::shared_ptr<CIdExpression> methodId;
    std::shared_ptr<CListExpression> arguments;
};
