#pragma once
//реализация интерфейса обхода графа, создает дерево обхода для графвиза

#include <Visitors/IVisitor.h>
#include <Nodes/INode.h>
#include <vector>

#include <fstream>

class CPrintVisitor: public IVisitor {
public:
	//принимает корень дерева и имя файла с выводом для графвиза
	void StartVisit(INode* startNode, std::string filename);
	//Сюда нужно добавить методы visit для всех классов, которые мы хотим отображать в дереве.
	void Visit(CAssignStatement*);
	void Visit(CAssignItemStatement*);
	void Visit(CCompoundStatement*);
	void Visit(CPrintStatement*);
	void Visit(CIfElseStatement*);
	void Visit(CWhileStatement*);
	void Visit(CListStatement*);

	void Visit(CVarDecl*);
	void Visit(CListVarDecl*);
	void Visit(CMethod*);
	void Visit(CListMethodDecl*);
    void Visit(CClass*);

	void Visit(CIdExpression*);
	void Visit(CNumExpression*);
	void Visit(CBoolExpression*);
    void Visit(CNotExpression*);
	void Visit(COperationExpression*);
	void Visit(CLengthExpression*);
	void Visit(CArrayConstructionExpression*);
	void Visit(CConstructClassExpression*);

private:

	int expressionId;
	//в этот вектор нужно добавить все имена токенов, которые мы хотим отрисовывать в форме прямоугольника, а не эллипса
    std::vector<std::string> idsOfTokenWithBoxShape;
	//При использовании графвиза у нас возникла проблема - разные с нашей точки зрения токены, имеющие одно и то же имя
	// сливались в одну ноду на дереве, моэтому после каждого токена мы пишем его id в формате tokenName + A + id
	// в качестве разделителя не получилось использовать " " |_ и тому подобные символы
	std::string delim = "A";

	std::ofstream file;
    //метод рисует стрелочку межда именами нод в файле вывода
	std::string getArrow() const;
	//метод заканчиват эту строку в файле вывода и переходит на следующую
	std::string getEndLine() const;

	std::string getNodeNameWithLabel(std::string label, int id, std::string nodeName ) const;
};
