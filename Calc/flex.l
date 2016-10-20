%option noyywrap

%{
	/* This code goes at the "top" of the generated file. */
	#include <string.h>
	#include <stdio.h>
	#include <ctype.h>	
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


DIGIT              [0-9]
LETER            [a-zA-Z_]
STRING           \"(\\.|[^"])*\"
id               {LETER}({DIGIT}|{LETER})*
IntegerLiteral   [1-9]{DIGIT}*|0
keyword          class|extends|public|private|static|int|double|boolean|void

%%

{keyword} {
	updateLocation();
	toUpper(yytext);
	printLocation(yytext);
}

{STRING}         {

	updateLocation();
 
	const unsigned int MAX_SIZE = 1000;
	char no_quotes[MAX_SIZE];

	strcpy(no_quotes, yytext + 1);
	no_quotes[strlen(yytext) - 2] = '\0';

	printValueLocation("STRING", no_quotes);

}

{id}           	 {updateLocation(); printValueLocation("ID", yytext);}
{IntegerLiteral} {updateLocation(); printValueLocation("NUMBER", yytext);}

"{"              {updateLocation(); printLocation("LFBRACE");}
"}"				 {updateLocation(); printLocation("LFBRACE");}
"("				 {updateLocation(); printLocation("LPBRACE");}
")"				 {updateLocation(); printLocation("RPBRACE");}

"+"              {updateLocation(); printLocation("PLUS");}
"-"              {updateLocation(); printLocation("MINUS");}
"*"              {updateLocation(); printLocation("STAR");}
"/"              {updateLocation(); printLocation("SLASH");}
"%"            {updateLocation(); printLocation("MOD");}

"<"		     {updateLocation(); printLocation("LESS");}
"&&"	    {updateLocation(); printLocation("AND");}
"||"	            {updateLocation(); printLocation("OR");}

"\n"|"\t"|" "    {updateLocation(); printf("%s", yytext);}
%%

int main( int argc, char* argv[]) {
    yylex();
}