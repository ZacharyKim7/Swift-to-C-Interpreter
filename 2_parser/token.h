/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
     TOKEN_ERROR = 258,
     TOKEN_EOF = 259,
     TOKEN_KEYWORD_BREAK = 260,
     TOKEN_KEYWORD_COUNT = 261,
     TOKEN_KEYWORD_FALSE = 262,
     TOKEN_KEYWORD_FOR = 263,
     TOKEN_KEYWORD_FUNC = 264,
     TOKEN_KEYWORD_IN = 265,
     TOKEN_KEYWORD_IF = 266,
     TOKEN_KEYWORD_ELSE = 267,
     TOKEN_KEYWORD_IMPORT = 268,
     TOKEN_KEYWORD_LET = 269,
     TOKEN_KEYWORD_NOT = 270,
     TOKEN_KEYWORD_PRINT = 271,
     TOKEN_KEYWORD_RETURN = 272,
     TOKEN_KEYWORD_TRUE = 273,
     TOKEN_KEYWORD_VAR = 274,
     TOKEN_KEYWORD_WHILE = 275,
     TOKEN_SQUAREROOT = 276,
     TOKEN_IDENTIFIER = 277,
     TOKEN_INTEGER = 278,
     TOKEN_LEFT_PARENTHESIS = 279,
     TOKEN_RIGHT_PARENTHESIS = 280,
     TOKEN_LEFT_BRACKET = 281,
     TOKEN_RIGHT_BRACKET = 282,
     TOKEN_LEFT_BRACE = 283,
     TOKEN_RIGHT_BRACE = 284,
     TOKEN_STRING = 285,
     TOKEN_NEWLINE = 286,
     TOKEN_ASSIGNMENT = 287,
     TOKEN_EQUALITY = 288,
     TOKEN_POWER = 289,
     TOKEN_MULTIPLY = 290,
     TOKEN_MINUS = 291,
     TOKEN_PLUS = 292,
     TOKEN_DIVIDE = 293,
     TOKEN_COMMA = 294,
     TOKEN_DOT = 295,
     TOKEN_RANGE = 296,
     TOKEN_COLON = 297,
     TOKEN_PERCENT = 298,
     TOKEN_GREATER_THAN = 299,
     TOKEN_GREATER_THAN_EQUAL = 300,
     TOKEN_LESS_THAN = 301,
     TOKEN_LESS_THAN_EQUAL = 302,
     TOKEN_NOT_EQUAL = 303,
     TOKEN_AND = 304,
     TOKEN_OR = 305,
     TOKEN_NOT = 306,
     TOKEN_DOUBLE = 307
   };
#endif
/* Tokens.  */
#define TOKEN_ERROR 258
#define TOKEN_EOF 259
#define TOKEN_KEYWORD_BREAK 260
#define TOKEN_KEYWORD_COUNT 261
#define TOKEN_KEYWORD_FALSE 262
#define TOKEN_KEYWORD_FOR 263
#define TOKEN_KEYWORD_FUNC 264
#define TOKEN_KEYWORD_IN 265
#define TOKEN_KEYWORD_IF 266
#define TOKEN_KEYWORD_ELSE 267
#define TOKEN_KEYWORD_IMPORT 268
#define TOKEN_KEYWORD_LET 269
#define TOKEN_KEYWORD_NOT 270
#define TOKEN_KEYWORD_PRINT 271
#define TOKEN_KEYWORD_RETURN 272
#define TOKEN_KEYWORD_TRUE 273
#define TOKEN_KEYWORD_VAR 274
#define TOKEN_KEYWORD_WHILE 275
#define TOKEN_SQUAREROOT 276
#define TOKEN_IDENTIFIER 277
#define TOKEN_INTEGER 278
#define TOKEN_LEFT_PARENTHESIS 279
#define TOKEN_RIGHT_PARENTHESIS 280
#define TOKEN_LEFT_BRACKET 281
#define TOKEN_RIGHT_BRACKET 282
#define TOKEN_LEFT_BRACE 283
#define TOKEN_RIGHT_BRACE 284
#define TOKEN_STRING 285
#define TOKEN_NEWLINE 286
#define TOKEN_ASSIGNMENT 287
#define TOKEN_EQUALITY 288
#define TOKEN_POWER 289
#define TOKEN_MULTIPLY 290
#define TOKEN_MINUS 291
#define TOKEN_PLUS 292
#define TOKEN_DIVIDE 293
#define TOKEN_COMMA 294
#define TOKEN_DOT 295
#define TOKEN_RANGE 296
#define TOKEN_COLON 297
#define TOKEN_PERCENT 298
#define TOKEN_GREATER_THAN 299
#define TOKEN_GREATER_THAN_EQUAL 300
#define TOKEN_LESS_THAN 301
#define TOKEN_LESS_THAN_EQUAL 302
#define TOKEN_NOT_EQUAL 303
#define TOKEN_AND 304
#define TOKEN_OR 305
#define TOKEN_NOT 306
#define TOKEN_DOUBLE 307




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;
