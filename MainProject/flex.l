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
	   	 } else if (yytext[i] == '\t'){
	   	 	column_number += 4;
	   	 } 
	   	 else {
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

class       	{updateLocation(); printf("CLASS (%d, %d)", yylloc.first_column, yylloc.first_line);}
extends  	    {updateLocation(); printf("EXTENDS (%d, %d)", yylloc.first_column, yylloc.first_line);}
public          {updateLocation(); printf("PUBLIC (%d, %d)", yylloc.first_column, yylloc.first_line);}
static          {updateLocation(); printf("STATIC (%d, %d)", yylloc.first_column, yylloc.first_line);}

{id}           	{updateLocation(); printf("ID (%d, %d)", yylloc.first_column, yylloc.first_line);}
{IntegerLiteral} {updateLocation(); printf("NUMBER (%d, %d)", yylloc.first_column, yylloc.first_line);}

"{"  	{updateLocation(); printf("LFBRACE (%d, %d)", yylloc.first_column, yylloc.first_line);}
"}"				{updateLocation(); printf("LFBRACE (%d, %d)", yylloc.first_column, yylloc.first_line);}
"("				{updateLocation(); printf("LPBRACE (%d, %d)", yylloc.first_column, yylloc.first_line);}
")"				{updateLocation(); printf("RPBRACE (%d, %d)", yylloc.first_column, yylloc.first_line);}

"+"				{updateLocation(); printf("PLUS (%d, %d)", yylloc.first_column, yylloc.first_line);}
"-"				{updateLocation(); printf("MINUS (%d, %d)", yylloc.first_column, yylloc.first_line);}
"*"				{updateLocation(); printf("STAR (%d, %d)", yylloc.first_column, yylloc.first_line);}
"/"				{updateLocation(); printf("SLASH (%d, %d)", yylloc.first_column, yylloc.first_line);}
"\n"|"\t"|" "           {updateLocation(); printf("%s", yytext);}
%%

int main( int argc, char* argv[]) {
    yylex();
}