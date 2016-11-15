/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 4 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:339  */

#include <CommonInclude.h>
int yyerror(char *s);
int yylex(void);

extern shared_ptr<CProgram> ans;

#line 74 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "heading.h".  */
#ifndef YY_YY_HOME_KAGUDKOV_CLIONPROJECTS_PROTIVOGAZIK_MINIJAVACOMPILER_PARSER_HEADING_H_INCLUDED
# define YY_YY_HOME_KAGUDKOV_CLIONPROJECTS_PROTIVOGAZIK_MINIJAVACOMPILER_PARSER_HEADING_H_INCLUDED
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
    CLASS = 274,
    EXTENDS = 275,
    IF = 276,
    ELSE = 277,
    WHILE = 278,
    RETURN = 279,
    PRINTLN = 280,
    LENGTH = 281,
    THIS = 282,
    NEW = 283,
    MAIN = 284,
    POINT = 285,
    COMMA = 286,
    ASSIGN = 287,
    LESS = 288,
    OR = 289,
    AND = 290,
    NOT = 291,
    PLUS = 292,
    MINUS = 293,
    STAR = 294,
    END = 295,
    INTEGER_LITERAL = 296,
    ID = 297,
    MOD = 298
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 12 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:355  */

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

#line 172 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_HOME_KAGUDKOV_CLIONPROJECTS_PROTIVOGAZIK_MINIJAVACOMPILER_PARSER_HEADING_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 189 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   254

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  17
/* YYNRULES -- Number of rules.  */
#define YYNRULES  53
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  145

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   298

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    80,    80,    83,    89,    90,    94,   103,   116,   117,
     120,   121,   126,   127,   131,   132,   135,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   146,   148,   149,   150,
     151,   152,   153,   155,   157,   163,   164,   168,   169,   172,
     173,   177,   178,   179,   180,   185,   186,   191,   208,   210,
     214,   217,   219,   222
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LPBRACKET", "RPBRACKET", "LFBRACKET",
  "RFBRACKET", "LSBRACKET", "RSBRACKET", "SEMICOLON", "PUBLIC", "PRIVATE",
  "STATIC", "INT", "BOOLEAN", "VOID", "STRING", "TRUE", "FALSE", "CLASS",
  "EXTENDS", "IF", "ELSE", "WHILE", "RETURN", "PRINTLN", "LENGTH", "THIS",
  "NEW", "MAIN", "POINT", "COMMA", "ASSIGN", "LESS", "OR", "AND", "NOT",
  "PLUS", "MINUS", "STAR", "END", "INTEGER_LITERAL", "ID", "MOD",
  "$accept", "input", "mainClass", "classDeclList", "classDeclaration",
  "methodDeclList", "varDeclList", "paramList", "nonEmptyParamList", "exp",
  "expList", "nonEmptyExpList", "statList", "typeName", "visibility",
  "methodDeclaration", "stat", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298
};
# endif

#define YYPACT_NINF -79

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-79)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -1,   -27,    60,    53,    70,   -79,    34,   -79,    53,    76,
      75,   -79,    84,   -79,    66,    62,    -4,   107,    86,   -79,
     -79,   109,   -79,   -79,   113,    78,    65,    16,   -79,   123,
     120,   -79,   121,    89,   -79,    -4,   118,   -79,   -79,   133,
     134,   132,    65,   -79,   135,   138,   110,   103,   108,   153,
      65,   -79,   158,   -79,   125,   168,   104,   -79,    42,    42,
     173,   180,   184,    17,   164,    42,    17,   185,   193,    96,
      96,    96,    96,    96,    96,   -79,   194,   -79,    96,   -79,
     -79,   -79,    26,    96,   -79,   -79,     7,    18,    55,   114,
     126,   159,   -79,    67,   196,   209,   211,    42,    96,   -21,
      96,    96,    96,    96,    96,    96,    96,    42,   198,   183,
     -79,   210,   -79,    96,   213,   197,   147,   -79,   217,    35,
     -79,   190,    48,    48,   137,   137,   -79,   -79,    96,   -79,
     171,   -79,    42,   -79,    96,   204,   -79,   -79,   188,   224,
     199,   -79,   -79,    96,   188
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     4,     0,     1,     0,     2,     4,     0,
       0,     5,     0,    10,     0,     0,     8,     0,     0,    45,
      46,    43,    42,    44,     0,     0,     0,     8,    10,     0,
       0,     6,     0,     0,     9,     8,     0,    41,    11,     0,
       0,     0,    12,     7,     0,     0,    13,     0,     0,     0,
       0,    14,     0,    10,     0,     0,    39,    15,    39,    39,
       0,     0,     0,    44,     0,    39,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    40,     0,    48,     0,    24,
      25,    26,     0,     0,    16,    28,     0,     0,     0,     0,
       0,     0,     3,     0,     0,     0,    29,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,     0,    32,     0,     0,     0,     0,    27,     0,    23,
      22,    21,    17,    18,    19,    20,    50,    51,     0,    47,
       0,    33,     0,    31,    35,     0,    30,    49,    37,     0,
      36,    53,    34,     0,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -79,   -79,   -79,   221,   -79,   -15,    38,   -79,   -79,   -70,
     -79,   -79,   -42,    61,   -79,   -79,   -78
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     8,    24,    16,    45,    46,    86,
     139,   140,    64,    25,    26,    27,    65
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      87,    88,    89,    90,    91,   117,    19,    20,    93,    21,
      22,    97,    34,    96,    98,     4,    67,    68,     1,   115,
      40,   118,   107,    75,    72,    98,    19,    20,   116,   126,
     119,   120,   121,   122,   123,   124,   125,    99,    23,    94,
     100,   101,   102,   130,   103,   104,   105,    59,    99,    73,
     106,   100,   101,   102,   137,   103,   104,   105,   135,   108,
       5,   106,    98,    60,   138,    61,    35,    62,    95,   101,
     102,   112,     6,   144,    98,     9,    10,    18,    21,    22,
      13,   100,   101,   102,    66,    99,    12,    33,   100,   101,
     102,    56,   103,   104,   105,    14,    15,    99,   106,    78,
     100,   101,   102,    47,   103,   104,   105,    23,    17,    59,
     106,    54,    28,    79,    80,    29,    30,    21,    22,    31,
      32,    98,   109,    81,    82,    60,    36,    61,    37,    62,
      38,    39,    83,    98,    41,   110,    42,    84,    85,    44,
      43,    50,    49,    48,    99,    51,    63,   100,   101,   102,
      52,   103,   104,   105,    98,   133,    99,   106,    53,   100,
     101,   102,    55,   103,   104,   105,    98,    57,   111,   106,
     100,   101,   102,    58,   103,   104,    69,    99,    98,   136,
     100,   101,   102,    70,   103,   104,   105,    71,    74,    99,
     106,    76,   100,   101,   102,    98,   103,   104,   105,    77,
      92,    99,   106,   113,   100,   101,   102,   127,   103,   104,
     105,    98,   114,   141,   106,   128,   129,   131,    99,   132,
     134,   100,   101,   102,   101,   103,   104,   105,   142,    11,
     143,   106,     0,     0,    99,     0,     0,   100,   101,   102,
       0,   103,   104,   105,   100,   101,   102,   106,   103,   104,
     105,     0,     0,     0,   106
};

static const yytype_int16 yycheck[] =
{
      70,    71,    72,    73,    74,    26,    10,    11,    78,    13,
      14,     4,    27,    83,     7,    42,    58,    59,    19,    97,
      35,    42,     4,    65,     7,     7,    10,    11,    98,   107,
     100,   101,   102,   103,   104,   105,   106,    30,    42,    13,
      33,    34,    35,   113,    37,    38,    39,     5,    30,    32,
      43,    33,    34,    35,   132,    37,    38,    39,   128,     4,
       0,    43,     7,    21,   134,    23,    28,    25,    42,    34,
      35,     4,    19,   143,     7,     5,    42,    15,    13,    14,
       5,    33,    34,    35,    42,    30,    10,    26,    33,    34,
      35,    53,    37,    38,    39,    20,    12,    30,    43,     3,
      33,    34,    35,    42,    37,    38,    39,    42,    42,     5,
      43,    50,     5,    17,    18,    29,     7,    13,    14,     6,
      42,     7,     8,    27,    28,    21,     3,    23,     8,    25,
       9,    42,    36,     7,    16,     9,     3,    41,    42,     7,
       6,    31,     4,     8,    30,    42,    42,    33,    34,    35,
      42,    37,    38,    39,     7,     8,    30,    43,     5,    33,
      34,    35,     4,    37,    38,    39,     7,    42,     9,    43,
      33,    34,    35,     5,    37,    38,     3,    30,     7,     8,
      33,    34,    35,     3,    37,    38,    39,     3,    24,    30,
      43,     6,    33,    34,    35,     7,    37,    38,    39,     6,
       6,    30,    43,     7,    33,    34,    35,     9,    37,    38,
      39,     7,     3,     9,    43,    32,     6,     4,    30,    22,
       3,    33,    34,    35,    34,    37,    38,    39,     4,     8,
      31,    43,    -1,    -1,    30,    -1,    -1,    33,    34,    35,
      -1,    37,    38,    39,    33,    34,    35,    43,    37,    38,
      39,    -1,    -1,    -1,    43
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    19,    45,    46,    42,     0,    19,    47,    48,     5,
      42,    47,    10,     5,    20,    12,    50,    42,    15,    10,
      11,    13,    14,    42,    49,    57,    58,    59,     5,    29,
       7,     6,    42,    57,    49,    50,     3,     8,     9,    42,
      49,    16,     3,     6,     7,    51,    52,    57,     8,     4,
      31,    42,    42,     5,    57,     4,    50,    42,     5,     5,
      21,    23,    25,    42,    56,    60,    42,    56,    56,     3,
       3,     3,     7,    32,    24,    56,     6,     6,     3,    17,
      18,    27,    28,    36,    41,    42,    53,    53,    53,    53,
      53,    53,     6,    53,    13,    42,    53,     4,     7,    30,
      33,    34,    35,    37,    38,    39,    43,     4,     4,     8,
       9,     9,     4,     7,     3,    60,    53,    26,    42,    53,
      53,    53,    53,    53,    53,    53,    60,     9,    32,     6,
      53,     4,    22,     8,     3,    53,     8,    60,    53,    54,
      55,     9,     4,    31,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    44,    45,    46,    47,    47,    48,    48,    49,    49,
      50,    50,    51,    51,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    57,    57,    58,    58,    59,    60,    60,
      60,    60,    60,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,    17,     0,     2,     6,     8,     0,     2,
       0,     4,     0,     1,     2,     4,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     3,     1,     2,
       5,     4,     3,     4,     6,     0,     1,     1,     3,     0,
       2,     3,     1,     1,     1,     1,     1,    13,     3,     7,
       5,     5,     4,     7
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 80 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { ans = shared_ptr<CProgram>(new CProgram(shared_ptr<CMainClass>((yyvsp[-1].main_class)), shared_ptr<CListStatement>((yyvsp[0].stat_list)))); return 0;}
#line 1379 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 84 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.main_class) = new CMainClass(shared_ptr<CIdExpression>(new CIdExpression(std::string((yyvsp[-15].op_val)))),
								  shared_ptr<CIdExpression>(new CIdExpression(std::string((yyvsp[-5].op_val)))),
				 				  shared_ptr<CListStatement>((yyvsp[-2].stat_list))); }
#line 1387 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 89 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = new CListStatement(std::string("Classes")); }
#line 1393 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 90 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = std::move((yyvsp[0].stat_list)); (yyval.stat_list)->Add(shared_ptr<IStatement> ((yyvsp[-1].class_decl))); }
#line 1399 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 96 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    {
      	(yyval.class_decl) = new CClass(
      		std::shared_ptr<CIdExpression>(new CIdExpression(std::string((yyvsp[-4].op_val)))),
			std::shared_ptr<CListStatement>((yyvsp[-2].stat_list)), 
			std::shared_ptr<CListStatement>((yyvsp[-1].stat_list))
		);
    }
#line 1411 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 105 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    {
      	(yyval.class_decl) = new CClass(
      		std::shared_ptr<CIdExpression>(new CIdExpression(std::string((yyvsp[-6].op_val)))), 
      		std::shared_ptr<CIdExpression>(new CIdExpression(std::string((yyvsp[-4].op_val)))), 
      		std::shared_ptr<CListStatement>((yyvsp[-2].stat_list)), 
      		std::shared_ptr<CListStatement>((yyvsp[-1].stat_list))
      	);
    }
#line 1424 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 116 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = new CListStatement(std::string("Methods")); }
#line 1430 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 117 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = std::move((yyvsp[0].stat_list)); (yyval.stat_list)->Add(shared_ptr<CMethod>((yyvsp[-1].method))); }
#line 1436 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 120 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = new CListStatement(std::string("Variables")); }
#line 1442 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 121 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = std::move((yyvsp[-3].stat_list)); (yyval.stat_list)->Add(shared_ptr<CVarDecl>(
    									  new CVarDecl(std::string((yyvsp[-2].op_val)), std::string((yyvsp[-1].op_val))))); }
#line 1449 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 126 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = new CListStatement(std::string("Parameters")); }
#line 1455 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 127 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = std::move((yyvsp[0].stat_list)); }
#line 1461 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 131 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = new CListStatement(std::string("Parameters")); (yyval.stat_list)->Add(shared_ptr<CVarDecl>(new CVarDecl(std::string((yyvsp[-1].op_val)), std::string((yyvsp[0].op_val))))); }
#line 1467 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 132 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = std::move((yyvsp[-3].stat_list)); (yyval.stat_list)->Add(shared_ptr<CVarDecl>(new CVarDecl(std::string((yyvsp[-1].op_val)), std::string((yyvsp[0].op_val))))); }
#line 1473 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 135 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CNumExpression((yyvsp[0].int_val)); }
#line 1479 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 136 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new COperationExpression(shared_ptr<IExpression>((yyvsp[-2].expr_val)), shared_ptr<IExpression>((yyvsp[0].expr_val)), COperationExpression::ADDITION); }
#line 1485 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 137 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new COperationExpression(shared_ptr<IExpression>((yyvsp[-2].expr_val)), shared_ptr<IExpression>((yyvsp[0].expr_val)), COperationExpression::SUBTRACTION); }
#line 1491 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 138 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new COperationExpression(shared_ptr<IExpression>((yyvsp[-2].expr_val)), shared_ptr<IExpression>((yyvsp[0].expr_val)), COperationExpression::MULTIPLICATION); }
#line 1497 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 139 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new COperationExpression(shared_ptr<IExpression>((yyvsp[-2].expr_val)), shared_ptr<IExpression>((yyvsp[0].expr_val)), COperationExpression::MOD); }
#line 1503 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 140 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new COperationExpression(shared_ptr<IExpression>((yyvsp[-2].expr_val)), shared_ptr<IExpression>((yyvsp[0].expr_val)), COperationExpression::AND); }
#line 1509 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 141 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new COperationExpression(shared_ptr<IExpression>((yyvsp[-2].expr_val)), shared_ptr<IExpression>((yyvsp[0].expr_val)), COperationExpression::OR); }
#line 1515 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 142 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new COperationExpression(shared_ptr<IExpression>((yyvsp[-2].expr_val)), shared_ptr<IExpression>((yyvsp[0].expr_val)), COperationExpression::LESS); }
#line 1521 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 143 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CBoolExpression(true); }
#line 1527 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 144 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CBoolExpression(false); }
#line 1533 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 146 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CThisExpression(); }
#line 1539 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 148 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CLengthExpression(shared_ptr<IExpression>((yyvsp[-2].expr_val))); }
#line 1545 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 149 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CIdExpression(std::string((yyvsp[0].op_val))); }
#line 1551 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 150 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CNotExpression(shared_ptr<IExpression>((yyvsp[0].expr_val))); }
#line 1557 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 151 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CArrayConstructionExpression(shared_ptr<IExpression>((yyvsp[-1].expr_val))); }
#line 1563 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 152 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CGetItemExpression(shared_ptr<IExpression>((yyvsp[-3].expr_val)), shared_ptr<IExpression>((yyvsp[-1].expr_val))); }
#line 1569 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 153 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = (yyvsp[-1].expr_val); }
#line 1575 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 155 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CConstructClassExpression(shared_ptr<CIdExpression>
		                                                                        (new CIdExpression(std::string((yyvsp[-2].op_val))))); }
#line 1582 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 157 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.expr_val) = new CMethodCallExpression(shared_ptr<IExpression>((yyvsp[-5].expr_val)),
																					 shared_ptr<CIdExpression>(new CIdExpression((yyvsp[-3].op_val))), 
																				     shared_ptr<CListExpression>((yyvsp[-1].exp_list))); }
#line 1590 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 163 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.exp_list) = new CListExpression(std::string("Arguments")); }
#line 1596 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 164 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.exp_list) = std::move((yyvsp[0].exp_list)); }
#line 1602 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 168 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.exp_list) = new CListExpression(std::string("Arguments")); (yyval.exp_list)->Add(shared_ptr<IExpression>((yyvsp[0].expr_val))); }
#line 1608 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 169 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.exp_list) = std::move((yyvsp[-2].exp_list)); (yyval.exp_list)->Add(shared_ptr<IExpression>((yyvsp[0].expr_val))); }
#line 1614 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 172 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = new CListStatement(std::string("Statements")); }
#line 1620 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 173 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_list) = std::move((yyvsp[0].stat_list)); (yyval.stat_list)->Add(shared_ptr<IStatement> ((yyvsp[-1].stat_val))); }
#line 1626 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 177 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.op_val) = "intArray"; }
#line 1632 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 178 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.op_val) = "boolean"; }
#line 1638 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 179 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.op_val) = "int"; }
#line 1644 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 180 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.op_val) = (yyvsp[0].op_val); }
#line 1650 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 185 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.op_val) = "public"; }
#line 1656 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 186 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.op_val) = "private"; }
#line 1662 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 195 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    {
        (yyval.method) = new CMethod(
            std::string((yyvsp[-12].op_val)),
            std::string((yyvsp[-11].op_val)),
            shared_ptr<CIdExpression>(new CIdExpression(std::string((yyvsp[-10].op_val)))),
            shared_ptr<CListStatement>(std::move((yyvsp[-8].stat_list))),
            shared_ptr<CListStatement>((yyvsp[-5].stat_list)),
            shared_ptr<CListStatement>((yyvsp[-4].stat_list)),
            shared_ptr<IExpression>((yyvsp[-2].expr_val))
        );
    }
#line 1678 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 208 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_val) = (yyvsp[-1].stat_list); }
#line 1684 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 210 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_val) = new CIfElseStatement(shared_ptr<IExpression>((yyvsp[-4].expr_val)),
    																					shared_ptr<IStatement>((yyvsp[-2].stat_val)),
    																					shared_ptr<IStatement>((yyvsp[0].stat_val))); }
#line 1692 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 214 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_val) = new CWhileStatement(shared_ptr<IExpression>((yyvsp[-2].expr_val)),
    																				   shared_ptr<IStatement>((yyvsp[0].stat_val))); }
#line 1699 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 217 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_val) = new CPrintStatement(shared_ptr<IExpression>((yyvsp[-2].expr_val))); }
#line 1705 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 219 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_val) = new CAssignStatement(shared_ptr<CIdExpression>(new CIdExpression(std::string((yyvsp[-3].op_val)))), 
    																					shared_ptr<IExpression>((yyvsp[-1].expr_val))); }
#line 1712 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 222 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1646  */
    { (yyval.stat_val) = new CAssignItemStatement(shared_ptr<CIdExpression>(new CIdExpression(std::string((yyvsp[-6].op_val)))),
     																						shared_ptr<IExpression>((yyvsp[-4].expr_val)),
    																						shared_ptr<IExpression>((yyvsp[-1].expr_val))); }
#line 1720 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
    break;


#line 1724 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Output/parser.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 227 "/home/kagudkov/ClionProjects/ProtivoGaZiK/MiniJavaCompiler/Parser/bison.y" /* yacc.c:1906  */


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


