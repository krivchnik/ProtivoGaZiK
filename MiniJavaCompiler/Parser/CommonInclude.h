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
#include <Nodes/CNumExpression.h>
#include <Nodes/COperationExpression.h>
#include <Nodes/CLengthExpression.h>

#include <Nodes/CAssignStatement.h>
#include <Nodes/CAssignItemStatement.h>
#include <Nodes/CPrintStatement.h>
#include <Nodes/CIfElseStatement.h>
#include <Nodes/CWhileStatement.h>
#include <Nodes/CListStatement.h>

#include <Visitors/CPrintVisitor.h>

