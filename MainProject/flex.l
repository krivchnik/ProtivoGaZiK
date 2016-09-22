%option noyywrap

%{
	/* This code goes at the "top" of the generated file. */
	#include <string.h>
	#include <stdio.h>	
	//using namespace std;

    typedef struct YYLTYPE  
	{  
	  int first_line;  
	  int first_column;  
	  int last_line;  
	  int last_column;  
	} YYLTYPE;

    YYLTYPE yylloc;   

    int line_number = 0;
    int column_number = 0;
	static void updateLocation()
	{
	    // Начало токена
	    yylloc.first_line = line_number;
	    yylloc.first_column = column_number;
	    for( int i = 0; i < strlen(yytext); i++ ) {
	   	 if( yytext[i] == '\n' ) {
	   		 line_number++;
	   		 column_number = 1;
	   	 } else {
             printf("hey");
	   		 column_number++;
	   	 }
	    }

	    yylloc.last_line = line_number;
	    yylloc.last_column = column_number;
	}
%}


DIGIT              [0-9]
LETER            [a-zA-Z_]
id               {LETER}({DIGIT}|{LETER})*
IntegerLiteral   [1-9]{DIGIT}*|0

%%

class       	    printf("CLASS");
extends  	    printf("EXTENDS");
public          printf("PUBLIC");
static          printf("STATIC");

{id}           	{printf("ID%d", yylloc.first_column);}
{IntegerLiteral} printf("NUMBER");

"{"  	{	printf("LFBRACE "); }
"}"				printf("RFBRACE");
"("				printf("LPBRACE");
")"				printf("RPBRACE");

"+"				printf("PLUS");
"-"				printf("MINUS");
"*"				printf("STAR");
"/"				printf("SLASH");


%%

int main( int argc, char* argv[]) {
    yylex();
}