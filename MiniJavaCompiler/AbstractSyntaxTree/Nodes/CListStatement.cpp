//
// Created by kagudkov on 27.10.16.
//

#include <Nodes/CListStatement.h>

void CListStatement::Accept(IVisitor* visitor) {
    visitor->Visit(this);
}

void CListStatement::Add(std::shared_ptr<IStatement> statement) {
    statements.push_back(statement);
}

const std::vector<std::shared_ptr<IStatement>> CListStatement::GetStatements() const {
    return statements;
}

CListStatement::CListStatement(const std::string &statementType)
        : statementType(statementType) {}

const std::string &CListStatement::GetStatementType() const {
    return statementType;
}
