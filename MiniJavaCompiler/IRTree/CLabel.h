//
// Created by nismohl on 23.02.17.
//

#pragma once

#include <string>

class CLabel {
public:
    CLabel()
            : label( "L" + std::to_string( counter++ ) ) {}

    CLabel( const std::string& _label )
            : label( _label ) {}

    std::string ToString() const {
        return label;
    }

private:
    std::string label;
    static int counter;
};
