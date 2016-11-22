%option noyywrap

%{
	/* This code goes at the "top" of the generated file. */
	#include <string.h>
	#include <stdio.h>
	#include <ctype.h>

    #include <CommonInclude.h>
    #include <heading.h>

    int line_number = 1;
    int column_number = 1;
	static void updateLocation(YYLTYPE* yylloc)
	{
	    // Начало токена
	    yylloc->first_line = line_number;
	    yylloc->first_column = column_number;
	    for( unsigned int i = 0; i < strlen(yytext); i++ ) {
	   	 if( yytext[i] == '\n' ) {
	   		 line_number++;
	   		 column_number = 1;
	   	 } else if (yytext[i] == '\t'){
	   	 	column_number += 4;
	   	 } 
	   	 else {
	   		 column_number++;
	   	 }
	    }

	    yylloc->last_line = line_number;
	    yylloc->last_column = column_number;
	}

	void printValueLocation(char *token_name, char *token_value) {
		printf("%s(%s){%d,%d}", token_name, token_value, yylloc.first_column, yylloc.first_line);
	}

	void printLocation(char *token_name) {
		printf("%s{%d,%d}", token_name, yylloc.first_column, yylloc.first_line);
	}

	void toUpper(char *str) {
		int i = 0; 
		while (str[i]) {
			str[i] = toupper(str[i]);
			++i;
		}
	}

%}


DIGIT            [0-9]
LETER            [a-zA-Z_]
STRING           \"(\\.|[^"])*\"
id               {LETER}({DIGIT}|{LETER})*
IntegerLiteral   [1-9]{DIGIT}*|0
keyword          class|extends|public|private|static|int|double|boolean|void
comment          \/\/.*\n

%%

"\n"|"\t"|" "           { updateLocation(&yylloc); }

"System.out.println"	{ updateLocation(&yylloc); return PRINTLN;}

{comment}               {updateLocation(&yylloc);}

"public"              { updateLocation(&yylloc); return(PUBLIC); }
"private"             { updateLocation(&yylloc); return(PRIVATE); }
"static"              { updateLocation(&yylloc); return(STATIC); }

"int"                 { updateLocation(&yylloc); return(INT); }
"boolean"             { updateLocation(&yylloc); return(BOOLEAN); }
"void"                { updateLocation(&yylloc); return(VOID); }
"String"              { updateLocation(&yylloc); return(STRING); }

"class"               { updateLocation(&yylloc); return(CLASS); }
"extends"             { updateLocation(&yylloc); return(EXTENDS); }

"if"                  { updateLocation(&yylloc); return(IF); }
"else"                { updateLocation(&yylloc); return(ELSE); }
"while"               { updateLocation(&yylloc); return(WHILE); }
"return"              { updateLocation(&yylloc); return(RETURN); }

"length"              { updateLocation(&yylloc); return(LENGTH); }

"this"                { updateLocation(&yylloc); return(THIS); }
"new"                 { updateLocation(&yylloc); return(NEW); }

"main"                { updateLocation(&yylloc); return(MAIN); }

{keyword} {
	updateLocation(&yylloc);
	toUpper(yytext);
	printLocation(yytext);
}

{id}           	 {
	              updateLocation(&yylloc); 
	              size_t len = strlen(yytext);
                  char *token_name = (char*)malloc(len + 1 ); /* one for extra char, one for trailing zero */
                  strcpy(token_name, yytext);
                  token_name[len] = '\0';
                  yylval.op_val = token_name;
                  return ID;
                  }
{IntegerLiteral} {updateLocation(&yylloc); yylval.int_val = atoi(yytext); return INTEGER_LITERAL;}

"{"              {updateLocation(&yylloc); return LFBRACKET;}
"}"				 {updateLocation(&yylloc); return RFBRACKET;}
"("				 {updateLocation(&yylloc); return LPBRACKET;}
")"				 {updateLocation(&yylloc); return RPBRACKET;}
"["				 {updateLocation(&yylloc); return LSBRACKET;}
"]"				 {updateLocation(&yylloc); return RSBRACKET;}

"+"              {updateLocation(&yylloc); return PLUS;}
"-"              {updateLocation(&yylloc); return MINUS;}
"*"              {updateLocation(&yylloc); return STAR;}
"%"		         {updateLocation(&yylloc); return MOD;}

"!"				 {updateLocation(&yylloc); return NOT;}

"="		         {updateLocation(&yylloc); return ASSIGN;}

"<"		     	 {updateLocation(&yylloc); return LESS;}
"&&"	    	 {updateLocation(&yylloc); return AND;}
"||"	         {updateLocation(&yylloc); return OR;}

";"				 { updateLocation(&yylloc); return SEMICOLON; }
"."              { updateLocation(&yylloc); return POINT; }
","				 { updateLocation(&yylloc); return COMMA; }


{STRING}         {

	updateLocation(&yylloc);

	const unsigned int MAX_SIZE = 1000;
	char no_quotes[MAX_SIZE];

	strcpy(no_quotes, yytext + 1);
	no_quotes[strlen(yytext) - 2] = '\0';

	printValueLocation("STRING", no_quotes);

}

%%

/*int main( int argc, char* argv[]) {
    yylex();
}*/