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

	friend std::ostream& operator <<(std::ostream &stream, const Location& loc) {
		stream << "(" << std::to_string(loc.first_line) << "," << std::to_string(loc.first_column) << "),("
           			  << std::to_string(loc.last_line) << "," << std::to_string(loc.last_column) << ")\n";
		return stream;
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