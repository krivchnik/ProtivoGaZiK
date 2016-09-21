%option noyywrap
%option c++

%top{
	/* This code goes at the "top" of the generated file. */
	#include <iostream>
	using namespace std;
}


DIGIT            [0-9]
LETER            [a-zA-Z_]
id               {LETER}({DIGIT}|{LETER})*
IntegerLiteral   [1-9]{DIGIT}*|0

%%

class      	std::cout << "CLASS";
extends  	std::cout << "EXTENDS";
public         std::cout << "PUBLIC";
static     std::cout << "STATIC";

{id}           	std::cout << "ID";
{IntegerLiteral}  std::cout << "NUMBER";

"{"  			std::cout << "LFBRACE";
"}"				std::cout << "RFBRACE";
"("				std::cout << "LPBRACE";
")"				std::cout << "RPBRACE";

"+"				std::cout << "PLUS";
"-"				std::cout << "MINUS";
"*"				std::cout << "STAR";
"/"				std::cout << "SLASH";


%%

int main( int argc, char* argv[]) {
	yylex();
	return 0;
}



