/* Mini Calculator */
/* calc.y */

%{
#include <CommonInclude.h>
int yyerror(char *s);
int yylex(void);

extern shared_ptr<IStatement> ans;
%}
	
%union{
  int                int_val;
  char*              op_val;
  INode*             node_val;
  IExpression*       expr_val;
  IStatement*        stat_val;
  CListStatement*    stat_list;
  CListVarDecl*      var_decl_list;
  CMethod*           method;
}

%start	input

%token				LPBRACKET RPBRACKET LFBRACKET RFBRACKET LSBRACKET RSBRACKET SEMICOLON
                    PUBLIC PRIVATE STATIC
                    INT BOOLEAN VOID STRING
	                TRUE FALSE
	                NOT
                    CLASS EXTENDS
                    IF ELSE WHILE
                    RETURN PRINTLN LENGTH
                    THIS NEW
                    MAIN POINT COMMA
%token <int_val>	INTEGER_LITERAL
%token <op_val>     ID

%type  <expr_val>		exp
%type  <stat_val>   	stat
%type  <stat_list>  	statList
%type  <method>  	    methodDeclaration
%type  <op_val>  		typeName visibility
%type  <var_decl_list> 	varDeclList paramList nonEmptyParamList

%left	POINT
%left 	OR
%left   AND
%left	NOT PLUS MINUS
%left	STAR MOD

%nonassoc ASSIGN
%nonassoc LESS

%%

input:	methodDeclaration	{ ans = shared_ptr<CMethod>($1); return 0;}
		;


varDeclList
    : %empty                            { $$ = new CListVarDecl(); }
    | varDeclList typeName ID SEMICOLON { $$ = std::move($1); $$->Add(shared_ptr<CVarDecl>(new CVarDecl(std::string($2), std::string($3)))); }
    ;

paramList
 	: %empty   							{}
 	| nonEmptyParamList                 { $$ = std::move($1); }
 	;

nonEmptyParamList
	: typeName ID 								{ $$ = new CListVarDecl(); $$->Add(shared_ptr<CVarDecl>(new CVarDecl(std::string($1), std::string($2)))); }
    | nonEmptyParamList COMMA typeName ID       { $$ = std::move($1); $$->Add(shared_ptr<CVarDecl>(new CVarDecl(std::string($3), std::string($4)))); }
	;

exp: 	INTEGER_LITERAL	{ $$ = new CNumExpression($1); }
		| exp PLUS exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::ADDITION); }
		| exp MINUS exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::SUBTRACTION); }
		| exp STAR exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::MULTIPLICATION); }
		| exp MOD exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::MOD); }
		| exp AND exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::AND); }
		| exp OR exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::OR); }
		| exp LESS exp	{ $$ = new COperationExpression(shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::LESS); }
        | TRUE      	{ $$ = new CBoolExpression(true); }
        | FALSE 		{ $$ = new CBoolExpression(false); }

		| exp POINT LENGTH 				     { $$ = new CLengthExpression(shared_ptr<IExpression>($1)); }
		| ID 							     { $$ = new CIdExpression(std::string($1)); }
		| NOT exp   					     { $$ = new CNotExpression(shared_ptr<IExpression>($2)); }
		| NEW INT LSBRACKET exp RSBRACKET    { $$ = new CArrayConstructionExpression(shared_ptr<IExpression>($4)); }
		| NEW ID LPBRACKET RPBRACKET         { $$ = new CConstructClassExpression(shared_ptr<CIdExpression>
		                                                                        (new CIdExpression(std::string($2)))); }
		;

statList : %empty { $$ = new CListStatement(); }
         | statList stat { $$ = std::move($1); $$->Add(shared_ptr<IStatement> ($2)); }
         ;

typeName
    : INT LSBRACKET RSBRACKET                    { $$ = "int[]"; }
    | BOOLEAN                                    { $$ = "boolean"; }
    | INT                                        { $$ = "int"; }
    | ID                                         { $$ = $1; }
;


visibility
    : PUBLIC                                     { $$ = "public"; }
    | PRIVATE                                    { $$ = "private"; }
;

methodDeclaration
    //TODO Visibility
    : visibility typeName ID LPBRACKET paramList RPBRACKET LFBRACKET
            varDeclList
            statList
            RETURN exp SEMICOLON
      RFBRACKET {
        $$ = new CMethod(
            std::string($1),
            std::string($2),
            shared_ptr<CIdExpression>(new CIdExpression(std::string($3))),
            shared_ptr<CListVarDecl>(std::move($5)),
            shared_ptr<CListVarDecl>($8),
            shared_ptr<CListStatement>($9),
            shared_ptr<IExpression>($11)
        );
    }
    ;

stat 	: LFBRACKET statList RFBRACKET                       { $$ = $2; }

    	| IF LPBRACKET exp RPBRACKET stat ELSE stat 		{ $$ = new CIfElseStatement(shared_ptr<IExpression>($3),
    																					shared_ptr<IStatement>($5),
    																					shared_ptr<IStatement>($7)); }

    	| WHILE LPBRACKET exp RPBRACKET stat         		{ $$ = new CWhileStatement(shared_ptr<IExpression>($3),
    																				   shared_ptr<IStatement>($5)); }

    	| PRINTLN LPBRACKET exp RPBRACKET SEMICOLON 		{ $$ = new CPrintStatement(shared_ptr<IExpression>($3)); }

    	| ID ASSIGN exp SEMICOLON                			{ $$ = new CAssignStatement(shared_ptr<CIdExpression>(new CIdExpression(std::string($1))), 
    																					shared_ptr<IExpression>($3)); }

    	| ID LSBRACKET exp RSBRACKET ASSIGN exp SEMICOLON 	{ $$ = new CAssignItemStatement(shared_ptr<CIdExpression>(new CIdExpression(std::string($1))),
     																						shared_ptr<IExpression>($3),
    																						shared_ptr<IExpression>($6)); }
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


