#pragma once
//интерфейс от которого должны быть унаследованы все классы, которые могут быть узлом дерева объхода
#include <Visitors/IVisitor.h>

#include <iostream>
#include <memory>

struct Location {
	int first_line;
	int first_column;
	int last_line;
	int last_column;

    void Print(std::ostream& ss) {
        ss << "    Location:\n";
        ss << "\t\t(" << std::to_string(first_line) << "," << std::to_string(first_column) << "),("
           << std::to_string(last_line) << "," << std::to_string(last_column) << ")\n";
    }
};

class INode {
public:
	virtual void Accept(IVisitor*) = 0;

    Location GetLocation() const {
        return location;
    }

	void SetLocation(const Location locationArg) {
		location = locationArg;
	}

protected:
	Location location;
};