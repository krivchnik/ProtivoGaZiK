/* Mini Calculator */
/* calc.y */

%{
#include <CommonInclude.h>
#include <heading.h>

int yyerror(char *s);
int yylex(void);

extern shared_ptr<CProgram> ans;

Location GetTokenLocation(YYLTYPE loc) {
	Location location {loc.first_line, loc.first_column, loc.last_line, loc.last_column};
	return location;
}

Location ComposeLocation(YYLTYPE loc1, YYLTYPE loc2) {
	Location location {loc1.first_line, loc1.first_column, loc2.last_line, loc2.last_column};
	return location;
}

%}

%locations
	
%union{
  int                     int_val;
  char*                   op_val;
  INode*                  node_val;
  IExpression*            expr_val;
  IStatement*             stat_val;
  CListStatement*         stat_list;
  CListExpression*		  exp_list;
  CMethod*                method;
  CClass*			      class_decl;
  CMainClass*		      main_class;
  CMethodCallExpression*  method_call;
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

%type  <exp_list>           expList nonEmptyExpList
%type  <stat_list> 			varDeclList paramList nonEmptyParamList
%type  <stat_list>			methodDeclList
%type  <stat_list>			classDeclList

%type  <method>  	    	methodDeclaration

%type  <class_decl>			classDeclaration
%type  <main_class>	     	mainClass

%left ASSIGN
%left OR
%left AND
%left LESS
%left PLUS MINUS
%left STAR MOD
%right NOT
%left LSBRACKET POINT LPBRACKET

%%

input:	mainClass classDeclList { ans = shared_ptr<CProgram>(new CProgram(GetTokenLocation(@$), shared_ptr<CMainClass>($1), shared_ptr<CListStatement>($2))); return 0;}
		;

mainClass:	CLASS ID LFBRACKET PUBLIC STATIC VOID MAIN LPBRACKET STRING LSBRACKET RSBRACKET ID RPBRACKET LFBRACKET statList RFBRACKET RFBRACKET
			{ 
				CListStatement* params = new CListStatement(ComposeLocation(@9, @12), std::string("Arguments"));
				params->Add(shared_ptr<CVarDecl>(new CVarDecl(ComposeLocation(@9, @12), "StringArray", std::string($12))));

				CMethod* mainMethod = new CMethod(
					ComposeLocation(@4, @13),
					std::string("public"),
					std::string("void"),
					shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@7), "main")),
					shared_ptr<CListStatement>(params),
					shared_ptr<CListStatement>(new CListStatement(GetTokenLocation(@14), std::string("Variables"))),
					shared_ptr<CListStatement>($15),
					nullptr
				);

				$$ = new CMainClass(GetTokenLocation(@$),
								  shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@2), std::string($2))),
								  shared_ptr<CMethod>(mainMethod)); 
			}
;

classDeclList : %empty 				 				{ $$ = new CListStatement(GetTokenLocation(@$), std::string("Classes")); }
         	  | classDeclaration classDeclList 		{ $$ = std::move($2); $$->Add(shared_ptr<IStatement> ($1)); 
         	  	                           			  $$->SetLocation(GetTokenLocation(@$)); }
;

classDeclaration
    : CLASS ID LFBRACKET
        varDeclList methodDeclList
      RFBRACKET {
      	$$ = new CClass(GetTokenLocation(@$),
      		std::shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@2), std::string($2))),
			std::shared_ptr<CListStatement>($4), 
			std::shared_ptr<CListStatement>($5)
		);
    }
    | CLASS ID EXTENDS ID LFBRACKET
        varDeclList methodDeclList
      RFBRACKET {
      	$$ = new CClass(GetTokenLocation(@$),
      		std::shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@2), std::string($2))), 
      		std::shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@4), std::string($4))), 
      		std::shared_ptr<CListStatement>($6), 
      		std::shared_ptr<CListStatement>($7)
      	);
    }
;

methodDeclList
	: %empty                            { $$ = new CListStatement(GetTokenLocation(@$), std::string("Methods")); }
	| methodDeclaration methodDeclList  { $$ = std::move($2); $$->Add(shared_ptr<CMethod>($1)); 
										  $$->SetLocation(GetTokenLocation(@$)); }

varDeclList
    : %empty                            { $$ = new CListStatement(GetTokenLocation(@$), std::string("Variables")); }
    | varDeclList typeName ID SEMICOLON { $$ = std::move($1); 
    									  $$->Add(shared_ptr<CVarDecl>(new CVarDecl(ComposeLocation(@2, @3), std::string($2), std::string($3)))); 
										  $$->SetLocation(GetTokenLocation(@$));}
    ;

paramList
 	: %empty   							{ $$ = new CListStatement(GetTokenLocation(@$), std::string("Parameters")); }
 	| nonEmptyParamList                 { $$ = std::move($1); }
 	;

nonEmptyParamList
	: typeName ID 								{ $$ = new CListStatement(GetTokenLocation(@$), std::string("Parameters")); 
												 $$->Add(shared_ptr<CVarDecl>(new CVarDecl(ComposeLocation(@1, @2), std::string($1), std::string($2)))); }

    | nonEmptyParamList COMMA typeName ID       { $$ = std::move($1); 
    											  $$->Add(shared_ptr<CVarDecl>(new CVarDecl(ComposeLocation(@3, @4), std::string($3), std::string($4)))); 
    											  $$->SetLocation(GetTokenLocation(@$)); }
	;

exp: 	INTEGER_LITERAL	{ $$ = new CNumExpression(GetTokenLocation(@$), $1); }
		| exp PLUS exp	{ $$ = new COperationExpression(GetTokenLocation(@$),
														shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::ADDITION); }

		| exp MINUS exp	{ $$ = new COperationExpression(GetTokenLocation(@$),
														shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::SUBTRACTION); }

		| exp STAR exp	{ $$ = new COperationExpression(GetTokenLocation(@$),
														shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::MULTIPLICATION); }

		| exp MOD exp	{ $$ = new COperationExpression(GetTokenLocation(@$),
														shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::MOD); }

		| exp AND exp	{ $$ = new COperationExpression(GetTokenLocation(@$),
														shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::AND); }

		| exp OR exp	{ $$ = new COperationExpression(GetTokenLocation(@$),
														shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::OR); }

		| exp LESS exp	{ $$ = new COperationExpression(GetTokenLocation(@$),
													    shared_ptr<IExpression>($1), shared_ptr<IExpression>($3), COperationExpression::LESS); }
        
        | TRUE      	{ $$ = new CBoolExpression(GetTokenLocation(@$), true); }
        | FALSE 		{ $$ = new CBoolExpression(GetTokenLocation(@$), false); }

        | THIS			{ $$ = new CThisExpression(GetTokenLocation(@$)); }

		| exp POINT LENGTH 				     { $$ = new CLengthExpression(GetTokenLocation(@$), 
																		  shared_ptr<IExpression>($1)); }

		| ID 							     { $$ = new CIdExpression(GetTokenLocation(@$), std::string($1)); }
		
		| NOT exp   					     { $$ = new CNotExpression(GetTokenLocation(@$), shared_ptr<IExpression>($2)); }

		| NEW INT LSBRACKET exp RSBRACKET    { $$ = new CArrayConstructionExpression(GetTokenLocation(@$), 
																					 shared_ptr<IExpression>($4)); }
		
		| exp LSBRACKET exp RSBRACKET		 { $$ = new CGetItemExpression(GetTokenLocation(@$), 
																		   shared_ptr<IExpression>($1), shared_ptr<IExpression>($3)); }	
		| LPBRACKET exp RPBRACKET			 { $$ = $2; }

		| NEW ID LPBRACKET RPBRACKET         { $$ = new CConstructClassExpression(GetTokenLocation(@$), 
																				  shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@2), std::string($2)))); }
		| exp POINT ID LPBRACKET expList RPBRACKET  { $$ = new CMethodCallExpression(GetTokenLocation(@$),
																					 shared_ptr<IExpression>($1),
																					 shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@3), $3)), 
																				     shared_ptr<CListExpression>($5)); }
		;

expList
 	: %empty   							{ $$ = new CListExpression(GetTokenLocation(@$), std::string("Arguments")); }
 	| nonEmptyExpList                   { $$ = std::move($1); }
 	;

nonEmptyExpList
	: exp 								{ $$ = new CListExpression(GetTokenLocation(@$), std::string("Arguments")); $$->Add(shared_ptr<IExpression>($1)); }
    | nonEmptyExpList COMMA exp         { $$ = std::move($1); $$->Add(shared_ptr<IExpression>($3)); 
    									  $$->SetLocation(GetTokenLocation(@$)); }


statList : %empty 				 { $$ = new CListStatement(GetTokenLocation(@$), std::string("Statements")); }
         | stat statList		 { $$ = std::move($2); $$->Add(shared_ptr<IStatement> ($1)); 
         						   $$->SetLocation(GetTokenLocation(@$)); }
;

typeName
    : INT LSBRACKET RSBRACKET                    { $$ = "intArray"; }
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
        	GetTokenLocation(@$),
            std::string($1),
            std::string($2),
            shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@3), std::string($3))),
            shared_ptr<CListStatement>(std::move($5)),
            shared_ptr<CListStatement>($8),
            shared_ptr<CListStatement>($9),
            shared_ptr<IExpression>($11)
        );
    }
    ;

stat 	: LFBRACKET statList RFBRACKET                      { $$ = $2; }

    	| IF LPBRACKET exp RPBRACKET stat ELSE stat 		{ $$ = new CIfElseStatement(GetTokenLocation(@$),
    																					shared_ptr<IExpression>($3),
    																					shared_ptr<IStatement>($5),
    																					shared_ptr<IStatement>($7)); }

    	| WHILE LPBRACKET exp RPBRACKET stat         		{ $$ = new CWhileStatement(GetTokenLocation(@$),
    																				   shared_ptr<IExpression>($3),
    																				   shared_ptr<IStatement>($5)); }

    	| PRINTLN LPBRACKET exp RPBRACKET SEMICOLON 		{ $$ = new CPrintStatement(GetTokenLocation(@$),
    																				   shared_ptr<IExpression>($3)); }

    	| ID ASSIGN exp SEMICOLON                			{ $$ = new CAssignStatement(GetTokenLocation(@$),
    																					shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@1), std::string($1))), 
    																					shared_ptr<IExpression>($3)); }

    	| ID LSBRACKET exp RSBRACKET ASSIGN exp SEMICOLON 	{ $$ = new CAssignItemStatement(GetTokenLocation(@$),
    																						shared_ptr<CIdExpression>(new CIdExpression(GetTokenLocation(@1), std::string($1))),
     																						shared_ptr<IExpression>($3),
    																						shared_ptr<IExpression>($6)); }
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


