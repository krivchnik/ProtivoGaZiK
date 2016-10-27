%option noyywrap

%{
	/* This code goes at the "top" of the generated file. */
	#include <string.h>
	#include <stdio.h>
	#include <ctype.h>

    #include <CommonInclude.h>
    #include <heading.h>

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


DIGIT            [0-9]
LETER            [a-zA-Z_]
STRING           \"(\\.|[^"])*\"
id               {LETER}({DIGIT}|{LETER})*
IntegerLiteral   [1-9]{DIGIT}*|0
keyword          class|extends|public|private|static|int|double|boolean|void

%%

"System.out.println"	{ updateLocation(); return PRINTLN;}

"\n"|"\t"|" "    {updateLocation();}

"public"              { updateLocation(); return(PUBLIC); }
"private"             { updateLocation(); return(PRIVATE); }
"static"              { updateLocation(); return(STATIC); }

"int"                 { updateLocation(); return(INT); }
"boolean"             { updateLocation(); return(BOOLEAN); }
"void"                { updateLocation(); return(VOID); }
"string"              { updateLocation(); return(STRING); }

"class"               { updateLocation(); return(CLASS); }
"extends"             { updateLocation(); return(EXTENDS); }

"if"                  { updateLocation(); return(IF); }
"else"                { updateLocation(); return(ELSE); }
"while"               { updateLocation(); return(WHILE); }
"return"              { updateLocation(); return(RETURN); }

"length"              { updateLocation(); return(LENGTH); }

"this"                { updateLocation(); return(THIS); }
"new"                 { updateLocation(); return(NEW); }

"main"                { updateLocation(); return(MAIN); }

{keyword} {
	updateLocation();
	toUpper(yytext);
	printLocation(yytext);
}

{id}           	 {
	              updateLocation(); 
	              size_t len = strlen(yytext);
                  char *token_name = (char*)malloc(len + 1 ); /* one for extra char, one for trailing zero */
                  strcpy(token_name, yytext);
                  token_name[len] = '\0';
                  yylval.op_val = token_name;
                  return ID;
                  }
{IntegerLiteral} {updateLocation(); yylval.int_val = atoi(yytext); return INTEGER_LITERAL;}

"{"              {updateLocation(); return LFBRACKET;}
"}"				 {updateLocation(); return RFBRACKET;}
"("				 {updateLocation(); return LPBRACKET;}
")"				 {updateLocation(); return RPBRACKET;}
"["				 {updateLocation(); return LSBRACKET;}
"]"				 {updateLocation(); return RSBRACKET;}

"+"              {updateLocation(); return PLUS;}
"-"              {updateLocation(); return MINUS;}
"*"              {updateLocation(); return STAR;}
"%"		         {updateLocation(); return MOD;}

"="		         {updateLocation(); return ASSIGN;}

"<"		     	 {updateLocation(); return LESS;}
"&&"	    	 {updateLocation(); return AND;}
"||"	         {updateLocation(); return OR;}

";"				 {updateLocation(); return SEMICOLON;}


{STRING}         {

	updateLocation();

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