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
  CMethod*           method;
  CClass*			 class_decl;
}

%start	input

%token				LPBRACKET RPBRACKET LFBRACKET RFBRACKET LSBRACKET RSBRACKET SEMICOLON
                    PUBLIC PRIVATE STATIC
                    INT BOOLEAN VOID STRING
	                TRUE FALSE
                    CLASS EXTENDS
                    IF ELSE WHILE
                    RETURN PRINTLN LENGTH
                    THIS NEW
                    MAIN POINT COMMA
                    ASSIGN LESS
                    OR AND NOT
                    PLUS MINUS STAR

%token <int_val>	INTEGER_LITERAL
%token <op_val>     ID

%type  <expr_val>			exp
%type  <stat_val>   		stat
%type  <stat_list>  		statList
%type  <op_val>  			typeName visibility

%type  <stat_list> 			varDeclList paramList nonEmptyParamList

%type  <method>  	    	methodDeclaration
%type  <stat_list>			methodDeclList

%type  <class_decl>			classDeclaration
%type  <stat_list>			classDeclList

%left	POINT
%left 	OR
%left   AND
%left	NOT PLUS MINUS
%left	STAR MOD

%nonassoc ASSIGN
%nonassoc LESS

%precedence VAR_DECL_LIST
%precedence METHOD_DECL

%%

input:	statList { ans = shared_ptr<IStatement>($1); return 0;}
		;

classDeclList : %empty 				 				{ $$ = new CListStatement(std::string("Classes")); }
         	  | classDeclList classDeclaration 		{ $$ = std::move($1); $$->Add(shared_ptr<IStatement> ($2)); }
;

classDeclaration
    : CLASS ID LFBRACKET
        varDeclList methodDeclList
      RFBRACKET {
      	$$ = new CClass(
      		std::shared_ptr<CIdExpression>(new CIdExpression(std::string($2))),
			std::shared_ptr<CListStatement>($4), 
			std::shared_ptr<CListStatement>($5)
		);
    }
    | CLASS ID EXTENDS ID LFBRACKET
        varDeclList methodDeclList
      RFBRACKET {
      	$$ = new CClass(
      		std::shared_ptr<CIdExpression>(new CIdExpression(std::string($2))), 
      		std::shared_ptr<CIdExpression>(new CIdExpression(std::string($4))), 
      		std::shared_ptr<CListStatement>($6), 
      		std::shared_ptr<CListStatement>($7)
      	);
    }
;

methodDeclList
	: %empty                            { $$ = new CListStatement(std::string("Methods")); }
	| methodDeclList methodDeclaration  { $$ = std::move($1); $$->Add(shared_ptr<CMethod>($2)); }

varDeclList
    : %empty                            { $$ = new CListStatement(std::string("Variables")); }
    | varDeclList typeName ID SEMICOLON { $$ = std::move($1); $$->Add(shared_ptr<CVarDecl>(
    									  new CVarDecl(std::string($2), std::string($3)))); } %prec VAR_DECL_LIST
    ;

paramList
 	: %empty   							{ $$ = new CListStatement(std::string("Parameters")); }
 	| nonEmptyParamList                 { $$ = std::move($1); }
 	;

nonEmptyParamList
	: typeName ID 								{ $$ = new CListStatement(std::string("Parameters")); $$->Add(shared_ptr<CVarDecl>(new CVarDecl(std::string($1), std::string($2)))); }
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

statList : %empty 				 { $$ = new CListStatement(std::string("Statements")); }
         | statList stat 		 { $$ = std::move($1); $$->Add(shared_ptr<IStatement> ($2)); }
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
            shared_ptr<CListStatement>(std::move($5)),
            shared_ptr<CListStatement>($8),
            shared_ptr<CListStatement>($9),
            shared_ptr<IExpression>($11)
        );
    } %prec METHOD_DECL
    ;

stat 	: LFBRACKET statList RFBRACKET                      { $$ = $2; }

    	| IF LPBRACKET exp RPBRACKET stat ELSE stat 		{ $$ = new CIfElseStatement(shared_ptr<IExpression>($3),
    																					shared_ptr<IStatement>($5),
    																					shared_ptr<IStatement>($7)); }

    	| WHILE LPBRACKET exp RPBRACKET stat         		{ $$ = new CWhileStatement(shared_ptr<IExpression>($3),
    																				   shared_ptr<IStatement>($5)); }

    	| PRINTLN LPBRACKET exp RPBRACKET SEMICOLON 		{ $$ = new CPrintStatement(shared_ptr<IExpression>($3)); }

    	| ID ASSIGN exp SEMICOLON                			{ $$ = new CAssignStatement(shared_ptr<CIdExpression>(new CIdExpression(std::string($1))), 
    																					shared_ptr<IExpression>($3)); } %prec STAT_LIST

    	| ID LSBRACKET exp RSBRACKET ASSIGN exp SEMICOLON 	{ $$ = new CAssignItemStatement(shared_ptr<CIdExpression>(new CIdExpression(std::string($1))),
     																						shared_ptr<IExpression>($3),
    																						shared_ptr<IExpression>($6)); } %prec STAT_LIST
        ;

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


