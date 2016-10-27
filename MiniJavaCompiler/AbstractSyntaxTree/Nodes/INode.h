#pragma once
//интерфейс от которого должны быть унаследованы все классы, которые могут быть узлом дерева объхода
#include <Visitors/IVisitor.h>

#include <memory>

class INode {
public:
	virtual void Accept(IVisitor*) = 0;
};