#include <IRTree/Nodes/StatementList.h>
#include <cassert>

#include <IRTree/Nodes/Statement.h>

namespace IRTree {

    std::shared_ptr<const CStatementList> CStatementList::Clone() const {
        CStatementList *newList = new CStatementList();
        for (auto it = statements.begin(); it != statements.end(); ++it) {
            newList->Add((*it)->Clone());

        }

        return std::shared_ptr<const CStatementList>(newList);

    }

    std::shared_ptr<const CStatementList> CStatementList::Canonize() const {
        CStatementList *newList = new CStatementList();
        for (auto it = statements.begin(); it != statements.end(); ++it) {
            newList->Add((*it)->Canonize());
        }
        return std::shared_ptr<const CStatementList>(newList);
    }
}