//
// Created by nismohl on 17.03.17.
//

#pragma once

#include <IRTree/Nodes/Statement.h>

namespace IRTree {

typedef typename std::vector<std::shared_ptr<const CStatement>> Block;

class CBlockLinearizer {
public:

    std::vector<Block> Linearize(std::vector<std::shared_ptr<CStatementList>>& argBlocks);
};

}
