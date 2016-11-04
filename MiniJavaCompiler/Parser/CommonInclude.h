/* heading.h */

#define YY_NO_UNPUT

using namespace std;

#include <stdio.h>
#include <iostream>
#include <string>
#include <memory>

#include <Nodes/INode.h>
#include <Nodes/IExpression.h>
#include <Nodes/CIdExpression.h>
#include <Nodes/CBoolExpression.h>
#include <Nodes/CNumExpression.h>
#include <Nodes/CNotExpression.h>
#include <Nodes/COperationExpression.h>
#include <Nodes/CLengthExpression.h>
#include <Nodes/CArrayConstructionExpression.h>
#include <Nodes/CConstructClassExpression.h>

#include <Nodes/CAssignStatement.h>
#include <Nodes/CAssignItemStatement.h>
#include <Nodes/CPrintStatement.h>
#include <Nodes/CIfElseStatement.h>
#include <Nodes/CWhileStatement.h>
#include <Nodes/CListStatement.h>

#include <Nodes/CVarDecl.h>
#include <Nodes/CListVarDecl.h>
#include <Nodes/CMethod.h>
#include <Nodes/CListMethodDecl.h>
#include <Nodes/CClass.h>
#include <Nodes/CMainClass.h>
#include <Nodes/CProgram.h>

#include <Visitors/CPrintVisitor.h>

