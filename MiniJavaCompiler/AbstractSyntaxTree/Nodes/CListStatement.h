#pragma once

#include <Nodes/IStatement.h>
#include <vector>

class CListStatement : public IStatement {
public:
    void Add(std::shared_ptr<IStatement> statement);
    void Accept(IVisitor*);

    CListStatement();

    const std::vector<std::shared_ptr<IStatement>> &GetStatements() const;

private:
    std::vector<std::shared_ptr<IStatement> > statements;
  /*  std::shared_ptr<CListStatement> prev;
    std::shared_ptr<IStatement> last;
*/
};
/*CListStatement
{
CListStatement BEFORE;
Istatement Last;

}
*/