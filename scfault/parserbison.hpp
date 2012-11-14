
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
#line 39 "parserbison.y"

	struct mytoken *token;



/* Line 1676 of yacc.c  */
#line 104 "parserbison.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


