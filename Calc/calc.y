/* Mini Calculator */
/* calc.y */

%{
#include "heading.h"
int yyerror(char *s);
int yylex(void);

extern shared_ptr<IStatement> ans;
%}
	
%union{
  int                           int_val;
  string*                       op_val;
  INode*             node_val;
  IExpression*       expr_val;
  IStatement*       stat_val;
}

%start	input

%token				LPBRACE RPBRACE SEMICOLON
%token				PRINTLN
%token <int_val>		INTEGER_LITERAL
%type	<expr_val>	exp
%type <stat_val>       	stat

%left    LESS AND OR
%left	PLUS MINUS
%left	STAR MOD

%%

input:	/* empty */
		| stat	{ ans = shared_ptr<IStatement>($1); return 0;}
		;

exp: 	INTEGER_LITERAL	{ $$ = new CNumExpression($1); }
		| exp PLUS exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::ADDITION); }
		| exp MINUS exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::SUBTRACTION); }
		| exp STAR exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::MULTIPLICATION); }
		| exp MOD exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::MOD); }
		| exp AND exp		{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::AND); }
		| exp OR exp		{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::OR); }
		| exp LESS exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::LESS); }
		;

stat:    PRINTLN LPBRACE exp RPBRACE SEMICOLON	{$$ = new CPrintStatement(shared_ptr<IExpression>($3)); }  
		;

/*
Goal: MainClass ( ClassDeclaration )* <EOF> {$$ = new IExpr($1)}

MainClass: "class" Identifier "{" "public" "static" "void" "main" "(" "String" "[" "]" Identifier ")" "{" Statement "}" "}"

ClassDeclaration: "class" Identifier ( "extends" Identifier )? "{" ( VarDeclaration )* ( MethodDeclaration )* "}"

VarDeclaration: Type Identifier ";"

MethodDeclaration: "public" | “private” Type Identifier "(" ( Type Identifier ( "," Type Identifier )* )? ")" "{" ( VarDeclaration )*( Statement )* "return" Expression ";" "}"

Type: "int" "[" "]"
| "boolean"
| "int"
| Identifier

Statement: 
	"{" ( Statement )* "}"
	| "if" "(" Expression ")" Statement "else" Statement
	| "while" "(" Expression ")" Statement
	| "System.out.println" "(" Expression ")" ";"
	| Identifier "=" Expression ";"
	| Identifier "[" Expression "]" "=" Expression ";"

Expression:
	| Expression "[" Expression "]"
	| Expression "." "length"
	| Expression "." Identifier "(" ( Expression ( "," Expression )* )? ")"
	| <INTEGER_LITERAL>
	| "true"
	| "false"
	| Identifier
	| "this"
	| "new" "int" "[" Expression "]"
	| "new" Identifier "(" ")"
	| "!" Expression | "(" Expression ")"

Identifier ::= <IDENTIFIER>
*/

%%

int yyerror(string s)
{
  extern int yylineno;	// defined and maintained in lex.c
  extern char *yytext;	// defined and maintained in lex.c
  
  cerr << "ERROR: " << s << " at symbol \"" << yytext;
  cerr << "\" on line " << yylineno << endl;
  exit(1);
}

int yyerror(char *s)
{
  return yyerror(string(s));
}


