/* Mini Calculator */
/* calc.lex */

%{
#include "heading.h"
#include "tok.h"
int yyerror(char *s);
%}

digit		[0-9]
int_const	{digit}+

%%

{int_const}	{ yylval.int_val = atoi(yytext); return INTEGER_LITERAL; }
"+"		{ return PLUS; }
"*"		{ return MULT; }

[ \t]*		{}
[\n]		{ yylineno++;	}

.		{ std::cerr << "SCANNER "; yyerror(""); exit(1);	}

