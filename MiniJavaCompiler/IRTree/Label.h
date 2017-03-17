#pragma once

#include <string>
#include <cassert>

namespace IRTree {

enum class LabelTag { COMMON, FINISH };

class CLabel {
public:
    CLabel( LabelTag tag = LabelTag::COMMON )
        : tag( tag ) {
        label = "L" + std::to_string( counter++ );
    };
    CLabel( std::string _label ) : label( _label ) {}

    std::string ToString() const { return label; }
private:
    std::string label;
    LabelTag tag;
    static int counter;
};

}
