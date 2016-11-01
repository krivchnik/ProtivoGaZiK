/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_HOME_NISMOHL_CLIONPROJECTS_PROTIVOGAZIK_2_MINIJAVACOMPILER_PARSER_HEADING_H_INCLUDED
# define YY_YY_HOME_NISMOHL_CLIONPROJECTS_PROTIVOGAZIK_2_MINIJAVACOMPILER_PARSER_HEADING_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LPBRACKET = 258,
    RPBRACKET = 259,
    LFBRACKET = 260,
    RFBRACKET = 261,
    LSBRACKET = 262,
    RSBRACKET = 263,
    SEMICOLON = 264,
    PUBLIC = 265,
    PRIVATE = 266,
    STATIC = 267,
    INT = 268,
    BOOLEAN = 269,
    VOID = 270,
    STRING = 271,
    TRUE = 272,
    FALSE = 273,
    NOT = 274,
    CLASS = 275,
    EXTENDS = 276,
    IF = 277,
    ELSE = 278,
    WHILE = 279,
    RETURN = 280,
    PRINTLN = 281,
    LENGTH = 282,
    THIS = 283,
    NEW = 284,
    MAIN = 285,
    POINT = 286,
    INTEGER_LITERAL = 287,
    ID = 288,
    OR = 289,
    AND = 290,
    PLUS = 291,
    MINUS = 292,
    STAR = 293,
    MOD = 294,
    ASSIGN = 295,
    LESS = 296
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "/home/nismohl/ClionProjects/ProtivoGaZiK_2/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1909  */

  int                int_val;
  char*              op_val;
  INode*             node_val;
  IExpression*       expr_val;
  IStatement*        stat_val;
  CListStatement*    stat_list;
  CListVarDecl*      var_decl_list;

#line 106 "/home/nismohl/ClionProjects/ProtivoGaZiK_2/MiniJavaCompiler/Parser/heading.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_NISMOHL_CLIONPROJECTS_PROTIVOGAZIK_2_MINIJAVACOMPILER_PARSER_HEADING_H_INCLUDED  */
