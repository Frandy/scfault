
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "parserbison.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parserdefs.h"
#include <ctype.h>

#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::ios;
using std::fstream;

/*
head files
*/
#include "edge.h"
#include "node.h"
#include "symbol.h"
#include "ckt.h"
#include "option.h"
#include "stringenc.h"


extern FILE *yyin;
extern int linenum;

extern CKT* myckt;
extern Symbol* symbolX;

int yylex();
int myparser(const char filename[]);
void yyerror(char *s,...);


/* Line 189 of yacc.c  */
#line 110 "parserbison.cpp"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     RID = 258,
     CID = 259,
     LID = 260,
     VID = 261,
     IID = 262,
     EID = 263,
     FID = 264,
     GID = 265,
     HID = 266,
     XID = 267,
     SID = 268,
     TEXT = 269,
     NUM = 270,
     INF = 271,
     DC = 272,
     AC = 273,
     DEC = 274,
     LIN = 275,
     DOTTITLE = 276,
     DOTOP = 277,
     DOTPRINT = 278,
     DOTDC = 279,
     DOTTRAN = 280,
     DOTAC = 281,
     DOTPZ = 282,
     DOTDDD = 283,
     DOTPARAM = 284,
     DOTCLOCK = 285,
     OPAMP = 286,
     LEVEL = 287,
     EQUAL = 288,
     PHASE = 289,
     SHORTOPEN = 290,
     FAULT = 291,
     OP = 292,
     CP = 293,
     COMMA = 294,
     DOTSC = 295,
     VOO = 296,
     VOE = 297,
     VEO = 298,
     VEE = 299,
     COMMENT = 300,
     LINEEND = 301
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 39 "parserbison.y"

	struct mytoken *token;



/* Line 214 of yacc.c  */
#line 198 "parserbison.cpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 210 "parserbison.cpp"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  77
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   262

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  179

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   301

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    12,    14,    16,    18,    19,
      22,    24,    27,    29,    31,    33,    35,    37,    39,    41,
      43,    45,    47,    49,    51,    53,    55,    57,    59,    61,
      63,    65,    67,    69,    71,    73,    78,    83,    91,    99,
     107,   112,   118,   126,   132,   140,   147,   154,   161,   167,
     174,   181,   188,   194,   200,   207,   212,   218,   225,   232,
     240,   242,   244,   246,   248,   250,   253,   256,   259,   262,
     269,   278,   285,   287,   289,   295,   301,   308,   315,   321,
     328,   332
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      48,     0,    -1,    48,    49,    -1,    48,    50,    -1,    48,
      46,    -1,    49,    -1,    50,    -1,    46,    -1,    -1,    49,
      51,    -1,    51,    -1,    50,    52,    -1,    52,    -1,    53,
      -1,    54,    -1,    55,    -1,    56,    -1,    57,    -1,    58,
      -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,    63,
      -1,    66,    -1,    67,    -1,    69,    -1,    70,    -1,    71,
      -1,    72,    -1,    73,    -1,    74,    -1,    68,    -1,    75,
      -1,    76,    -1,     3,    64,    64,    65,    -1,     4,    64,
      64,    65,    -1,     4,    64,    64,    65,    32,    33,    15,
      -1,     4,    64,    64,    16,    32,    33,    15,    -1,     4,
      64,    64,    14,    32,    33,    15,    -1,     5,    64,    64,
      65,    -1,     6,    64,    64,    18,    65,    -1,     6,    64,
      64,    17,    65,    18,    65,    -1,     7,    64,    64,    18,
      65,    -1,     7,    64,    64,    17,    65,    18,    65,    -1,
       8,    64,    64,    64,    64,    65,    -1,     8,    64,    64,
      64,    64,    16,    -1,     8,    64,    64,    64,    64,    14,
      -1,     9,    64,    64,    14,    65,    -1,     9,    64,    64,
      64,    64,    65,    -1,    10,    64,    64,    64,    64,    65,
      -1,    13,    64,    64,    34,    33,    15,    -1,    13,    64,
      64,    15,    35,    -1,    13,    64,    64,    15,    36,    -1,
      13,    64,    64,    15,    36,    35,    -1,    13,    64,    64,
      15,    -1,    11,    64,    64,    14,    65,    -1,    11,    64,
      64,    64,    64,    65,    -1,    12,    31,    64,    64,    64,
      64,    -1,    12,    31,    64,    64,    64,    64,    14,    -1,
      15,    -1,    14,    -1,    15,    -1,    21,    -1,    22,    -1,
      40,    41,    -1,    40,    42,    -1,    40,    43,    -1,    40,
      44,    -1,    23,    18,    14,    37,    64,    38,    -1,    23,
      18,    14,    37,    64,    39,    64,    38,    -1,    23,    18,
      14,    37,    14,    38,    -1,    24,    -1,    25,    -1,    26,
      19,    65,    65,    65,    -1,    26,    20,    65,    65,    65,
      -1,    27,    14,    37,    14,    38,    14,    -1,    27,    14,
      37,    64,    38,    14,    -1,    28,    14,    37,    64,    38,
      -1,    28,    18,    14,    37,    64,    38,    -1,    29,    14,
      14,    -1,    30,    65,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    57,    57,    58,    59,    60,    61,    62,    63,    66,
      67,    70,    71,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    99,   115,   129,   196,   249,
     303,   319,   352,   373,   393,   414,   433,   456,   483,   512,
     531,   558,   571,   589,   607,   627,   639,   667,   687,   697,
     714,   715,   718,   721,   724,   727,   730,   733,   736,   740,
     776,   799,   846,   849,   852,   855,   860,   867,   875,   879,
     884,   890
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "RID", "CID", "LID", "VID", "IID", "EID",
  "FID", "GID", "HID", "XID", "SID", "TEXT", "NUM", "INF", "DC", "AC",
  "DEC", "LIN", "DOTTITLE", "DOTOP", "DOTPRINT", "DOTDC", "DOTTRAN",
  "DOTAC", "DOTPZ", "DOTDDD", "DOTPARAM", "DOTCLOCK", "OPAMP", "LEVEL",
  "EQUAL", "PHASE", "SHORTOPEN", "FAULT", "OP", "CP", "COMMA", "DOTSC",
  "VOO", "VOE", "VEO", "VEE", "COMMENT", "LINEEND", "$accept", "netlist",
  "ckt_statements", "cmd_statements", "ckt_elem", "cmd_elem", "r_elem",
  "c_elem", "l_elem", "v_elem", "i_elem", "e_elem", "f_elem", "g_elem",
  "s_elem", "h_elem", "x_elem", "node", "elem_param", "cmd_title",
  "cmd_op", "cmd_sc", "cmd_print", "cmd_dc", "cmd_tran", "cmd_ac",
  "cmd_pz", "cmd_ddd", "cmd_param", "cmd_clock", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    48,    48,    48,    48,    48,    49,
      49,    50,    50,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    52,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    54,    54,    54,    54,
      55,    56,    56,    57,    57,    58,    58,    58,    59,    59,
      60,    61,    61,    61,    61,    61,    62,    62,    63,    63,
      64,    64,    65,    66,    67,    68,    68,    68,    68,    69,
      69,    69,    70,    71,    72,    72,    73,    73,    74,    74,
      75,    76
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     1,     1,     0,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     7,     7,     7,
       4,     5,     7,     5,     7,     6,     6,     6,     5,     6,
       6,     6,     5,     5,     6,     4,     5,     6,     6,     7,
       1,     1,     1,     1,     1,     2,     2,     2,     2,     6,
       8,     6,     1,     1,     5,     5,     6,     6,     5,     6,
       3,     2
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    63,    64,     0,    72,    73,     0,     0,     0,
       0,     0,     0,     7,     0,     5,     6,    10,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    32,    26,    27,    28,    29,    30,    31,    33,
      34,    61,    60,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    62,    81,    65,    66,    67,    68,     1,     4,     2,
       3,     9,    11,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      80,    35,     0,     0,    36,    40,     0,     0,     0,     0,
       0,    61,     0,     0,    61,     0,     0,    55,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      41,     0,    43,     0,    48,     0,     0,    56,     0,     0,
      52,    53,     0,    61,     0,    74,    75,     0,     0,    78,
       0,     0,     0,     0,     0,     0,    47,    46,    45,    49,
      50,    57,    58,    54,    51,    71,    69,     0,    76,    77,
      79,    39,    38,    37,    42,    44,    59,     0,    70
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    53,    72,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -18
static const yytype_int16 yypact[] =
{
     216,    22,    22,    22,    22,    22,    22,    22,    22,    22,
       0,    22,   -18,   -18,    45,   -18,   -18,    19,    69,     8,
      70,    61,    -9,   -18,   172,    62,   -10,   -18,   -18,   -18,
     -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,    22,    22,    22,    22,    22,    22,    22,
      22,    22,    22,    22,    71,    61,    61,    54,    55,    79,
      80,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,    62,
     -10,   -18,   -18,    61,     9,    61,    24,    26,    22,    31,
      22,    33,    22,     6,    60,    61,    61,    63,    22,    66,
     -18,   -18,    67,    72,    73,   -18,    61,    61,    61,    61,
      22,    61,    22,    22,    61,    22,    22,    14,    74,    65,
      61,    61,    64,    68,    77,    22,    76,    83,    88,    94,
     -18,   104,   -18,    13,   -18,    61,    61,   -18,    61,    22,
     -18,    89,   110,    90,    43,   -18,   -18,    84,   112,   -18,
      91,   117,   118,   119,    61,    61,   -18,   -18,   -18,   -18,
     -18,   -18,   113,   -18,   -18,   -18,   -18,    22,   -18,   -18,
     -18,   -18,   -18,   -18,   -18,   -18,   -18,    97,   -18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -18,   -18,   114,   115,   -17,   -16,   -18,   -18,   -18,   -18,
     -18,   -18,   -18,   -18,   -18,   -18,   -18,    -2,    35,   -18,
     -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18,   -18
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      54,    55,    56,    57,    58,    59,    60,    61,    81,    63,
      82,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,   117,    68,   102,    71,   103,    69,   156,    71,   157,
      22,    62,    73,    74,    75,    76,    51,    52,    65,    66,
     118,   106,   107,   108,   109,   111,    52,   114,    52,   140,
     141,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    81,    64,    82,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    71,   122,    52,   143,
      52,   166,   167,    67,    70,    94,   110,   112,   113,   115,
     116,    97,    98,    99,   100,   123,   124,   119,   168,   126,
      95,    96,   147,   125,   127,   128,   148,   142,   133,   151,
     135,   136,   154,   138,   139,   149,   152,   144,   101,   104,
     105,   153,   155,   150,   163,   164,   169,   176,   165,   170,
     120,   121,   171,   172,   173,   178,     0,   162,    79,    80,
       0,   129,   130,   131,   132,     0,   134,     0,     0,   137,
       0,     0,     0,     0,     0,   145,   146,     0,     0,     0,
       0,     0,     0,     0,     0,   177,     0,     0,   158,     0,
     159,   160,    77,   161,     0,     1,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,     0,     0,     0,   174,
     175,     0,     0,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    22,     0,     0,     0,     0,     0,    78,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
       0,     0,     0,     0,     0,     0,     0,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    22,     0,     0,     0,
       0,     0,    23
};

static const yytype_int16 yycheck[] =
{
       2,     3,     4,     5,     6,     7,     8,     9,    25,    11,
      26,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    15,    14,    14,    15,    16,    18,    14,    15,    16,
      40,    31,    41,    42,    43,    44,    14,    15,    19,    20,
      34,    17,    18,    17,    18,    14,    15,    14,    15,    35,
      36,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    79,    18,    80,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    15,    14,    15,    14,
      15,    38,    39,    14,    14,    14,    88,    89,    90,    91,
      92,    37,    37,    14,    14,    97,    98,    37,    14,    32,
      65,    66,    38,    37,    32,    32,    38,    33,   110,    33,
     112,   113,    18,   115,   116,    38,    33,   119,    83,    84,
      85,    33,    18,   125,    35,    15,    14,    14,    38,    38,
      95,    96,    15,    15,    15,    38,    -1,   139,    24,    24,
      -1,   106,   107,   108,   109,    -1,   111,    -1,    -1,   114,
      -1,    -1,    -1,    -1,    -1,   120,   121,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   167,    -1,    -1,   133,    -1,
     135,   136,     0,   138,    -1,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,   154,
     155,    -1,    -1,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    -1,    46,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,    -1,
      -1,    -1,    46
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    40,    46,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    14,    15,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    31,    64,    18,    19,    20,    14,    14,    18,
      14,    15,    65,    41,    42,    43,    44,     0,    46,    49,
      50,    51,    52,    64,    64,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    14,    65,    65,    37,    37,    14,
      14,    65,    14,    16,    65,    65,    17,    18,    17,    18,
      64,    14,    64,    64,    14,    64,    64,    15,    34,    37,
      65,    65,    14,    64,    64,    37,    32,    32,    32,    65,
      65,    65,    65,    64,    65,    64,    64,    65,    64,    64,
      35,    36,    33,    14,    64,    65,    65,    38,    38,    38,
      64,    33,    33,    33,    18,    18,    14,    16,    65,    65,
      65,    65,    64,    35,    15,    38,    38,    39,    14,    14,
      38,    15,    15,    15,    65,    65,    14,    64,    38
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
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
  int yytoken;
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

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 35:

/* Line 1455 of yacc.c  */
#line 99 "parserbison.y"
    {
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS((yyvsp[(2) - (4)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (4)].token)->s);
		Edge* edge = new Edge(a,b);
		Symbol* symbol = new Symbol((yyvsp[(1) - (4)].token)->s,R,edge,1/(yyvsp[(4) - (4)].token)->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 115 "parserbison.y"
    {
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS((yyvsp[(2) - (4)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (4)].token)->s);
		Edge* edge = new Edge(a,b);
		Symbol* symbol = new Symbol((yyvsp[(1) - (4)].token)->s,C,edge,(yyvsp[(4) - (4)].token)->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 129 "parserbison.y"
    {
/* add for switched capacitor */	
		if(int((yyvsp[(7) - (7)].token)->d)==1)
		{
			int a = -1, b = -1; 
			
			a = myckt->AddNodeS((yyvsp[(2) - (7)].token)->s);
			b = myckt->AddNodeS((yyvsp[(3) - (7)].token)->s);
			string tmp1 = string((yyvsp[(1) - (7)].token)->s) + "_la";
			string tmp2 = string((yyvsp[(1) - (7)].token)->s) + "_lb";
			int c = -1, d = -1;
			c = myckt->AddNodeS(tmp1);
			d = myckt->AddNodeS(tmp2);
			string name = string((yyvsp[(1) - (7)].token)->s);

			string name1 = "XOPAMP" + name + "_SC_1";
			Edge* edge1 = new Edge(a,c);
			Edge* pedge1 = new Edge(a,c);
	//		Edge* pedge1 = new Edge(c,a);
			Symbol* symb1 = new Symbol(name1,NUNO,edge1,pedge1,0);
			
			Edge* edge2 = new Edge(b,d);
			Edge* pedge2 = new Edge(b,d);
	//		Edge* pedge2 = new Edge(d,b);
			string name2 = "XOPAMP" + name + "_SC_2";
			Symbol* symb2 = new Symbol(name2,NUNO,edge2,pedge2,0);
			
			Edge* edge3 = new Edge(c,d);
			string name3 = "L" + name ;//+ "_SC";
			Symbol* symb3 = new Symbol(name3,L,edge3,-(yyvsp[(4) - (7)].token)->d);

			Edge* edge4 = new Edge(a,b);
			string name4 = "R" + name ;//+ "_SC";
			Symbol* symb4 = new Symbol(name4,R,edge4,(yyvsp[(4) - (7)].token)->d);
	//		myckt->AddSwitch(symb1);
	//		myckt->AddSwitch(symb2);
			myckt->AddOpamp(symb1);
			myckt->AddOpamp(symb2);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
			myckt->AddSymbolInOrder(symb3);
			myckt->AddSymbolInOrder(symb4);
#else
			myckt->AddSymbol(symb3);
			myckt->AddSymbol(symb4);
#endif
		}
		else if(int((yyvsp[(7) - (7)].token)->d)==2)
		{
			int a = -1, b = -1; 
			a = myckt->AddNodeS((yyvsp[(2) - (7)].token)->s);
			b = myckt->AddNodeS((yyvsp[(3) - (7)].token)->s);
			string name = string((yyvsp[(1) - (7)].token)->s);
			
			string name1 = "G" + name;
			Edge* edge1 = new Edge(b,a);
			Edge* pedge1 = new Edge(b,a);
			Symbol* symb1 = new Symbol(name1,G,edge1,pedge1,(yyvsp[(4) - (7)].token)->d);

			string name4 = "R" + name ;//+ "_SC";
			Edge* edge4 = new Edge(a,b);
			Symbol* symb4 = new Symbol(name4,R,edge4,(yyvsp[(4) - (7)].token)->d);

			myckt->AddSymbol(symb1);
			myckt->AddSymbol(symb4);
		
		}
	;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 196 "parserbison.y"
    {
/* add for switched capacitor */	
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS((yyvsp[(2) - (7)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (7)].token)->s);
		string tmp1 = string((yyvsp[(1) - (7)].token)->s) + "_la";
		string tmp2 = string((yyvsp[(1) - (7)].token)->s) + "_lb";
		int c = -1, d = -1;
		c = myckt->AddNodeS(tmp1);
		d = myckt->AddNodeS(tmp2);
		string name = string((yyvsp[(1) - (7)].token)->s);

		string name1 = "XOPAMP" + name + "_SC_1";
		Edge* edge1 = new Edge(a,c);
		Edge* pedge1 = new Edge(a,c);
//		Edge* pedge1 = new Edge(c,a);
		Symbol* symb1 = new Symbol(name1,NUNO,edge1,pedge1,0);
		
		Edge* edge2 = new Edge(b,d);
		Edge* pedge2 = new Edge(b,d);
//		Edge* pedge2 = new Edge(d,b);
		string name2 = "XOPAMP" + name + "_SC_2";
		Symbol* symb2 = new Symbol(name2,NUNO,edge2,pedge2,0);
	
		double var = 1.0;
		if((yyvsp[(4) - (7)].token)->s[0]=='-')
			var = -var;
		myckt->Infinity(true);

		Edge* edge3 = new Edge(c,d);
		string name3 = "L" + name ;//+ "_SC";
		Symbol* symb3 = new Symbol(name3,L,edge3,-var);
		symb3->Infinity(1);

		Edge* edge4 = new Edge(a,b);
		string name4 = "R" + name ;//+ "_SC";
		Symbol* symb4 = new Symbol(name4,R,edge4,var);
		symb4->Infinity(1);
//		myckt->AddSwitch(symb1);
//		myckt->AddSwitch(symb2);
		myckt->AddOpamp(symb1);
		myckt->AddOpamp(symb2);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symb3);
		myckt->AddSymbolInOrder(symb4);
#else
		myckt->AddSymbol(symb3);
		myckt->AddSymbol(symb4);
#endif
	;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 249 "parserbison.y"
    {
/* add for switched capacitor */	
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS((yyvsp[(2) - (7)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (7)].token)->s);
		string tmp1 = string((yyvsp[(1) - (7)].token)->s) + "_la";
		string tmp2 = string((yyvsp[(1) - (7)].token)->s) + "_lb";
		int c = -1, d = -1;
		c = myckt->AddNodeS(tmp1);
		d = myckt->AddNodeS(tmp2);
		string name = string((yyvsp[(1) - (7)].token)->s);

		string name1 = "XOPAMP" + name + "_SC_1";
		Edge* edge1 = new Edge(a,c);
		Edge* pedge1 = new Edge(a,c);
//		Edge* pedge1 = new Edge(c,a);
		Symbol* symb1 = new Symbol(name1,NUNO,edge1,pedge1,0);
		
		Edge* edge2 = new Edge(b,d);
		Edge* pedge2 = new Edge(b,d);
//		Edge* pedge2 = new Edge(d,b);
		string name2 = "XOPAMP" + name + "_SC_2";
		Symbol* symb2 = new Symbol(name2,NUNO,edge2,pedge2,0);
		
		Edge* edge3 = new Edge(c,d);
		string name3 = "L" + name ;//+ "_SC";
		Symbol* symb3 = new Symbol(name3,L,edge3,-(yyvsp[(4) - (7)].token)->d);

		Edge* edge4 = new Edge(a,b);
		string name4 = "R" + name ;//+ "_SC";
		Symbol* symb4 = new Symbol(name4,R,edge4,(yyvsp[(4) - (7)].token)->d);
//		myckt->AddSwitch(symb1);
//		myckt->AddSwitch(symb2);
		myckt->AddOpamp(symb1);
		myckt->AddOpamp(symb2);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symb3);
		myckt->AddSymbolInOrder(symb4);
#else
		myckt->AddSymbol(symb3);
		myckt->AddSymbol(symb4);
#endif
		//cout << "match here," << $<token>1->s << endl;
		if(myckt->paramList.IsParam((yyvsp[(4) - (7)].token)->s))
		{
			//cout << $<token>4->d << endl;	
			myckt->paramList.AddParamSymb((yyvsp[(4) - (7)].token)->s,symb3);
			myckt->paramList.AddParamSymb((yyvsp[(4) - (7)].token)->s,symb4);
		}
	;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 303 "parserbison.y"
    {
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS((yyvsp[(2) - (4)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (4)].token)->s);
		Edge* edge = new Edge(a,b);
		Symbol* symbol = new Symbol((yyvsp[(1) - (4)].token)->s,L,edge,1/(yyvsp[(4) - (4)].token)->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 319 "parserbison.y"
    {
		int a = -1, b = -1; 
	
		a = myckt->AddNodeS((yyvsp[(2) - (5)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (5)].token)->s);
		Edge* edge = new Edge(a,b);
		double var = (yyvsp[(5) - (5)].token)->d;
//cout << "vs:" << $<token>1->s << " var: " << var << endl;		
		if(var<=1e-9)
		{
			Symbol* symbol = new Symbol((yyvsp[(1) - (5)].token)->s,VS,edge,var);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif
		}
		else
		{
			if(symbolX==NULL)
			{
				symbolX = new Symbol((yyvsp[(1) - (5)].token)->s,VS,edge,(yyvsp[(5) - (5)].token)->d);
			}
			else
			{
				if(symbolX->Type()==VS)
					symbolX->SetType(E);
				else if(symbolX->Type()==IS)
					symbolX->SetType(H);
				symbolX->SetEdge(edge);
			}
		}
	;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 352 "parserbison.y"
    {
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS((yyvsp[(2) - (7)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (7)].token)->s);
		Edge* edge = new Edge(a,b);
		if(symbolX==NULL)
		{
			symbolX = new Symbol((yyvsp[(1) - (7)].token)->s,VS,edge,(yyvsp[(7) - (7)].token)->d);
		}
		else
		{
			if(symbolX->Type()==VS)
				symbolX->SetType(E);	// VC VS
			else if(symbolX->Type()==IS)
				symbolX->SetType(H);	// CC VS
			symbolX->SetEdge(edge);
		}
	;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 373 "parserbison.y"
    {
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS((yyvsp[(2) - (5)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (5)].token)->s);
		Edge* edge = new Edge(a,b);
		//Edge* edge = new Edge(b,a);
		if(symbolX==NULL)
		{
			symbolX = new Symbol((yyvsp[(1) - (5)].token)->s,IS,edge,(yyvsp[(5) - (5)].token)->d);
		}
		else
		{
			if(symbolX->Type()==VS)
				symbolX->SetType(G);	// VC CS
			else if(symbolX->Type()==IS)
				symbolX->SetType(F);	// CC CS
			symbolX->SetEdge(edge);
		}
	;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 393 "parserbison.y"
    {
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS((yyvsp[(2) - (7)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (7)].token)->s);
		Edge* edge = new Edge(a,b);
		if(symbolX==NULL)
		{
			symbolX = new Symbol((yyvsp[(1) - (7)].token)->s,IS,edge,(yyvsp[(7) - (7)].token)->d);
		}
		else
		{
			if(symbolX->Type()==VS)
				symbolX->SetType(G);	// VC CS
			else if(symbolX->Type()==IS)
				symbolX->SetType(F);	// CC CS
			symbolX->SetEdge(edge);
		}
	;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 414 "parserbison.y"
    {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS((yyvsp[(2) - (6)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (6)].token)->s);
		c = myckt->AddNodeS((yyvsp[(4) - (6)].token)->s);
		d = myckt->AddNodeS((yyvsp[(5) - (6)].token)->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		Symbol* symbol = new Symbol((yyvsp[(1) - (6)].token)->s,E,e1,e2,(yyvsp[(6) - (6)].token)->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 433 "parserbison.y"
    {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS((yyvsp[(2) - (6)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (6)].token)->s);
		c = myckt->AddNodeS((yyvsp[(4) - (6)].token)->s);
		d = myckt->AddNodeS((yyvsp[(5) - (6)].token)->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		double var = 1.0;
		if((yyvsp[(6) - (6)].token)->s[0]=='-')
			var = -var;
		myckt->Infinity(true);
		Symbol* symbol = new Symbol((yyvsp[(1) - (6)].token)->s,E,e1,e2,var);
		symbol->Infinity(1);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif
	;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 456 "parserbison.y"
    {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS((yyvsp[(2) - (6)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (6)].token)->s);
		c = myckt->AddNodeS((yyvsp[(4) - (6)].token)->s);
		d = myckt->AddNodeS((yyvsp[(5) - (6)].token)->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		cout << (yyvsp[(6) - (6)].token)->s << endl;
		double var = 1.0;
		if((yyvsp[(6) - (6)].token)->s[0]=='-')
			var = -var;
		myckt->Infinity(true);
		Symbol* symbol = new Symbol((yyvsp[(1) - (6)].token)->s,E,e1,e2,var);
		symbol->Infinity(1);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 483 "parserbison.y"
    {
	  /* CCCS */
		int a = -1, b = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS((yyvsp[(2) - (5)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (5)].token)->s);
		e1 = new Edge(a,b);
/*	
		Symbol* tmp_symbol = myckt->FindSymbol($<token>4->s);	// control current must appear earlier
		Edge* tmp_edge = tmp_symbol->GetEdge();
		string mcnode = "mc_";
		mcnode = mcnode + tmp_symbol->Name();
		int newnode = myckt->AddNodeS(mcnode);
		int oldnode = tmp_edge->ReplaceNode(newnode);
		e2 = new Edge(oldnode,newnode);
		Symbol* symbol = new Symbol($<token>1->s,F,e1,e2,$<token>5->d);
*/
		Symbol* symbol = new Symbol((yyvsp[(1) - (5)].token)->s,F,e1,(yyvsp[(5) - (5)].token)->d);
		myckt->AddCCXS(symbol,(yyvsp[(4) - (5)].token)->s);

#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 512 "parserbison.y"
    {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		a = myckt->AddNodeS((yyvsp[(2) - (6)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (6)].token)->s);
		c = myckt->AddNodeS((yyvsp[(4) - (6)].token)->s);
		d = myckt->AddNodeS((yyvsp[(5) - (6)].token)->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		Symbol* symbol = new Symbol((yyvsp[(1) - (6)].token)->s,F,e1,e2,(yyvsp[(6) - (6)].token)->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif	
	;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 531 "parserbison.y"
    {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS((yyvsp[(2) - (6)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (6)].token)->s);
		c = myckt->AddNodeS((yyvsp[(4) - (6)].token)->s);
		d = myckt->AddNodeS((yyvsp[(5) - (6)].token)->s);
		e1 = new Edge(a,b);
		Symbol* symbol = NULL;
		if(a==c && b==d)
			symbol = new Symbol((yyvsp[(1) - (6)].token)->s,R,e1,(yyvsp[(6) - (6)].token)->d);
		else	
		{	
			e2 = new Edge(c,d);
			symbol = new Symbol((yyvsp[(1) - (6)].token)->s,G,e1,e2,(yyvsp[(6) - (6)].token)->d);
		}
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 558 "parserbison.y"
    {
/* add for switched capacitor */	
		int a = -1, b = -1; 
		
		a = myckt->AddNodeS((yyvsp[(2) - (6)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (6)].token)->s);
		Edge* edge = new Edge(a,b);
		Edge* pedge = new Edge(a,b);
		Symbol* symbol = new Symbol((yyvsp[(1) - (6)].token)->s,S,edge,pedge,(yyvsp[(6) - (6)].token)->d);
	//	myckt->AddSwitch(symbol);
		myckt->AddOpamp(symbol);
	//	myckt->AddSymbol(symbol);
	;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 571 "parserbison.y"
    {
		string ft = strtolower(((yyvsp[(5) - (5)].token)->s));
		if(ft=="SHORT" || ft=="short")	
		{
			int a = -1, b = -1; 
			a = myckt->AddNodeS((yyvsp[(2) - (5)].token)->s);
			b = myckt->AddNodeS((yyvsp[(3) - (5)].token)->s);
			Edge* edge = new Edge(a,b);
			Edge* pedge = new Edge(a,b);
			Symbol* symbol = new Symbol((yyvsp[(1) - (5)].token)->s,S,edge,pedge,(yyvsp[(4) - (5)].token)->d);
			//symbol->Fault("short");
			symbol->Fault(ft);
			//myckt->AddSymbol(symbol);
			myckt->AddOpamp(symbol);
			cout << "a short switch:" << (yyvsp[(1) - (5)].token)->s << endl;		
		}
			// if open, no need to parse
	;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 589 "parserbison.y"
    {
		string ft = strtolower(((yyvsp[(5) - (5)].token)->s));
		//if(ft=="SHORT" || ft=="short")	
		//{
		int a = -1, b = -1; 
		a = myckt->AddNodeS((yyvsp[(2) - (5)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (5)].token)->s);
		Edge* edge = new Edge(a,b);
		Edge* pedge = new Edge(a,b);
		Symbol* symbol = new Symbol((yyvsp[(1) - (5)].token)->s,S,edge,pedge,(yyvsp[(4) - (5)].token)->d);
		//symbol->Fault("short");
		symbol->Fault(ft);
		myckt->AddSymbol(symbol);
		//myckt->AddOpamp(symbol);
		cout << "a short switch:" << (yyvsp[(1) - (5)].token)->s << endl;		
		//}
		// if open, no need to parse
	;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 607 "parserbison.y"
    {
		string ft = strtolower(((yyvsp[(5) - (6)].token)->s));
		string st = strtolower(((yyvsp[(6) - (6)].token)->s));
		//if(ft=="SHORT" || ft=="short")	
		//{
		int a = -1, b = -1; 
		a = myckt->AddNodeS((yyvsp[(2) - (6)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (6)].token)->s);
		Edge* edge = new Edge(a,b);
		Edge* pedge = new Edge(a,b);
		Symbol* symbol = new Symbol((yyvsp[(1) - (6)].token)->s,S,edge,pedge,(yyvsp[(4) - (6)].token)->d);
		//symbol->Fault("short");
		symbol->Fault(st);
		myckt->AddSymbol(symbol);
		//myckt->AddOpamp(symbol);
		cout << "a fault switch:" << (yyvsp[(1) - (6)].token)->s << endl;		
		//}
		// if open, no need to parse
	;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 627 "parserbison.y"
    {
		int a = -1, b = -1; 
		a = myckt->AddNodeS((yyvsp[(2) - (4)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (4)].token)->s);
		Edge* edge = new Edge(a,b);
		Edge* pedge = new Edge(a,b);
		Symbol* symbol = new Symbol((yyvsp[(1) - (4)].token)->s,S,edge,pedge,(yyvsp[(4) - (4)].token)->d);
	//	myckt->AddSymbol(symbol);
		myckt->AddOpamp(symbol);
	;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 639 "parserbison.y"
    {
		int a = -1, b = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		
		a = myckt->AddNodeS((yyvsp[(2) - (5)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (5)].token)->s);
		e1 = new Edge(a,b);
/*
		Symbol* tmp_symbol = myckt->FindSymbol($<token>4->s);	// control current must appear earlier
		Edge* tmp_edge = tmp_symbol->GetEdge();
		string mcnode = "mc_";
		mcnode = mcnode + tmp_symbol->Name();
		int newnode = myckt->AddNodeS(mcnode);
		int oldnode = tmp_edge->ReplaceNode(newnode);
		e2 = new Edge(oldnode,newnode);

		Symbol* symbol = new Symbol($<token>1->s,H,e1,e2,$<token>5->d);
*/
		Symbol* symbol = new Symbol((yyvsp[(1) - (5)].token)->s,H,e1,(yyvsp[(5) - (5)].token)->d);
		myckt->AddCCXS(symbol,(yyvsp[(4) - (5)].token)->s);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif

	;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 667 "parserbison.y"
    {
		int a = -1, b = -1, c = -1, d = -1; 
		Edge* e1 = NULL;
		Edge* e2 = NULL;
		a = myckt->AddNodeS((yyvsp[(2) - (6)].token)->s);
		b = myckt->AddNodeS((yyvsp[(3) - (6)].token)->s);
		c = myckt->AddNodeS((yyvsp[(4) - (6)].token)->s);
		d = myckt->AddNodeS((yyvsp[(5) - (6)].token)->s);
		e1 = new Edge(a,b);
		e2 = new Edge(c,d);
		Symbol* symbol = new Symbol((yyvsp[(1) - (6)].token)->s,H,e1,e2,(yyvsp[(6) - (6)].token)->d);
#ifdef  SYMBOL_ORDER_TYPE_DOMAIN
		myckt->AddSymbolInOrder(symbol);
#else
		myckt->AddSymbol(symbol);
#endif	
	
	;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 687 "parserbison.y"
    {
		int a = myckt->AddNodeS((yyvsp[(3) - (6)].token)->s);
		int b = myckt->AddNodeS((yyvsp[(4) - (6)].token)->s);
		int c = myckt->AddNodeS((yyvsp[(5) - (6)].token)->s);
		int d = myckt->AddNodeS((yyvsp[(6) - (6)].token)->s);
		Edge *e1 = new Edge(a,b);
		Edge *e2 = new Edge(c,d);
		Symbol* symbol = new Symbol((yyvsp[(1) - (6)].token)->s,NUNO,e1,e2,1);
		myckt->AddOpamp(symbol);
	  ;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 697 "parserbison.y"
    {
		int a = myckt->AddNodeS((yyvsp[(3) - (7)].token)->s);
		int b = myckt->AddNodeS((yyvsp[(4) - (7)].token)->s);
		int c = myckt->AddNodeS((yyvsp[(5) - (7)].token)->s);
		int d = myckt->AddNodeS((yyvsp[(6) - (7)].token)->s);
		Edge *e1 = new Edge(a,b);
		Edge *e2 = new Edge(c,d);
		Symbol* symbol = new Symbol((yyvsp[(1) - (7)].token)->s,E,e1,e2,(yyvsp[(7) - (7)].token)->d);
		myckt->AddSymbol(symbol);	
		if(myckt->paramList.IsParam((yyvsp[(7) - (7)].token)->s))
		{
			cout << "param opamp" << endl;
			myckt->paramList.AddParamSymb((yyvsp[(7) - (7)].token)->s,symbol);
		}
	  ;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 727 "parserbison.y"
    {
	  	myckt->SetSCOutStat(0);
	  ;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 730 "parserbison.y"
    {
	  	myckt->SetSCOutStat(1);
	  ;}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 733 "parserbison.y"
    {
	  	myckt->SetSCOutStat(2);
	  ;}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 736 "parserbison.y"
    {
	  	myckt->SetSCOutStat(3);
	  ;}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 740 "parserbison.y"
    {
	  	char outtype = toupper(((yyvsp[(3) - (6)].token)->s)[0]);
		Edge* outedge = NULL;
		if(symbolX!=NULL)
		{
			if(outtype=='V')
			{
				int node = myckt->FindNodeIndex((yyvsp[(5) - (6)].token)->s);
				outedge = new Edge(node,0);
				if(symbolX->Type()==VS)
					symbolX->SetType(E);
				else if(symbolX->Type()==IS)
					symbolX->SetType(G);
			}
	/*		
			else if(outtype=='I')
			{
				Symbol* tmp_symbol = myckt->FindSymbol($<token>5->s);
				Edge* tmp_edge = tmp_symbol->GetEdge();
				string mcnode = "mc_";
				mcnode = mcnode + tmp_symbol->Name();
				int newnode = myckt->AddNodeS(mcnode);
				int oldnode = tmp_edge->ReplaceNode(newnode);
				outedge = new Edge(oldnode,newnode);
				if(symbolX->Type()==VS)
					symbolX->SetType(H);
				else if(symbolX->Type()==IS)
					symbolX->SetType(F);
			}
	*/			symbolX->SetPairEdge(outedge);
		}
		else if(symbolX==NULL)
		{
			// some problems 
		}
	;}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 776 "parserbison.y"
    {
	  	char outtype = toupper(((yyvsp[(3) - (8)].token)->s)[0]);
		Edge* outedge = NULL;
		if(symbolX!=NULL)
		{
			if(outtype=='V')
			{
				int node1 = myckt->FindNodeIndex((yyvsp[(5) - (8)].token)->s);
				int node2 = myckt->FindNodeIndex((yyvsp[(7) - (8)].token)->s);
				outedge = new Edge(node1,node2);
				if(symbolX->Type()==VS)
					symbolX->SetType(E);
				else if(symbolX->Type()==IS)
					symbolX->SetType(G);
			}
			symbolX->SetPairEdge(outedge);
		}
		else if(symbolX==NULL)
		{
			// some problems 
		}
		
	;}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 799 "parserbison.y"
    {
	  	char outtype = toupper(((yyvsp[(3) - (6)].token)->s)[0]);
		Edge* outedge = NULL;
		if(symbolX!=NULL)
		{
			if(outtype=='V')
			{
				Symbol* tmp_symbol = myckt->FindSymbol((yyvsp[(5) - (6)].token)->s);
				if(tmp_symbol!=NULL)
				{
					int node1 = tmp_symbol->GetEdge()->Node().first;
					int node2 = tmp_symbol->GetEdge()->Node().second;
					outedge = new Edge(node1,node2);
				}
				else
				{
					int node = myckt->FindNodeIndex((yyvsp[(5) - (6)].token)->s);
					outedge = new Edge(node,0);
				}
				if(symbolX->Type()==VS)
					symbolX->SetType(E);
				else if(symbolX->Type()==IS)
					symbolX->SetType(G);
			}
			else if(outtype=='I')
			{
				Symbol* tmp_symbol = myckt->FindSymbol((yyvsp[(5) - (6)].token)->s);
				Edge* tmp_edge = tmp_symbol->GetEdge();
				string mcnode = "mc_";
				mcnode = mcnode + tmp_symbol->Name();
				int newnode = myckt->AddNodeS(mcnode);
				int oldnode = tmp_edge->ReplaceNode(newnode);
				outedge = new Edge(oldnode,newnode);
				if(symbolX->Type()==VS)
					symbolX->SetType(H);
				else if(symbolX->Type()==IS)
					symbolX->SetType(F);
			}
				symbolX->SetPairEdge(outedge);
		}
		else if(symbolX==NULL)
		{
			// some problems 
		}
	;}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 852 "parserbison.y"
    {
		myckt->SetACTask(1,(yyvsp[(3) - (5)].token)->d,(yyvsp[(4) - (5)].token)->d,(yyvsp[(5) - (5)].token)->d);
	;}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 855 "parserbison.y"
    {
		myckt->SetACTask(0,(yyvsp[(3) - (5)].token)->d,(yyvsp[(4) - (5)].token)->d,(yyvsp[(5) - (5)].token)->d);
	;}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 860 "parserbison.y"
    {
/*	  	char intype = toupper(($<token>2->s)[0]);
		char outtype = toupper(($<token>6->s)[0]);
		PZTask* task = new PZTask(intype,$<token>4->s,outtype,$<token>6->s);
		ckt->AddTask(task);
		task->Print(cout);
*/	;}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 867 "parserbison.y"
    {
/*	  	char intype = toupper(($<token>2->s)[0]);
		char outtype = toupper(($<token>6->s)[0]);
		PZTask* task = new PZTask(intype,$<token>4->s,outtype,$<token>6->s);
		ckt->AddTask(task);
		task->Print(cout);
*/	;}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 875 "parserbison.y"
    {
/*	    cout << "to set ddd output" << endl;
		ckt->SetDDDOutput($<token>4->s);   
*/	;}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 879 "parserbison.y"
    {
/*	    cout << "to set ddd output" << endl;
		ckt->SetDDDOutput($<token>5->s);   
*/	;}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 884 "parserbison.y"
    {
		ParamNode* p = new ParamNode((yyvsp[(2) - (3)].token)->s,(yyvsp[(3) - (3)].token)->s);
		myckt->paramList.AddParam(p)
	;}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 890 "parserbison.y"
    {
		myckt->Clock((yyvsp[(2) - (2)].token)->d);	 
	;}
    break;



/* Line 1455 of yacc.c  */
#line 2557 "parserbison.cpp"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
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

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 895 "parserbison.y"



int myparser(const char filename[]){
	
	myckt = new CKT(filename);
	symbolX = NULL;

	yyin = fopen(filename,"r");
	yyparse();
	symbolX->SetNameX();
	myckt->AddSymbolX(symbolX);
	myckt->PostProcessCCXSList();
	fclose(yyin);
	
	return 0;
}

void yyerror(char *s,...){
	fprintf(stderr,"line %d error %s\n",linenum,s);	
	exit(-1);
}

