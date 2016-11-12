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
	void Visit(CAssignStatement*) override;
	void Visit(CAssignItemStatement*) override;
	void Visit(CPrintStatement*) override;
	void Visit(CIfElseStatement*) override;
	void Visit(CWhileStatement*) override;
	void Visit(CListStatement*) override;

	void Visit(CVarDecl*) override;
	void Visit(CMethod*) override;
    void Visit(CClass*) override;
	void Visit(CMainClass*) override;
    void Visit(CProgram*) override;

	void Visit(CIdExpression*) override;
	void Visit(CNumExpression*) override;
	void Visit(CBoolExpression*) override;
    void Visit(CNotExpression*) override;
	void Visit(COperationExpression*) override;
	void Visit(CLengthExpression*) override;
	void Visit(CArrayConstructionExpression*) override;
	void Visit(CConstructClassExpression*) override;

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
