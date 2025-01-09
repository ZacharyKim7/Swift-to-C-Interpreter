%{
#define YYDEBUG 1

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "expr.h"

extern int yylineno;
extern char *yytext;
extern int yylex();
extern void yyerror(const char*);


struct stmt * parser_result = 0;

%}

%debug

%token TOKEN_ERROR
%token TOKEN_EOF
%token TOKEN_KEYWORD_BREAK
%token TOKEN_KEYWORD_COUNT
%token TOKEN_KEYWORD_FALSE
%token TOKEN_KEYWORD_FOR
%token TOKEN_KEYWORD_FUNC
%token TOKEN_KEYWORD_IN
%token TOKEN_KEYWORD_IF
%token TOKEN_KEYWORD_ELSE
%token TOKEN_KEYWORD_IMPORT
%token TOKEN_KEYWORD_LET
%token TOKEN_KEYWORD_NOT
%token TOKEN_KEYWORD_PRINT
%token TOKEN_KEYWORD_RETURN
%token TOKEN_KEYWORD_TRUE
%token TOKEN_KEYWORD_VAR
%token TOKEN_KEYWORD_WHILE
%token TOKEN_SQUAREROOT
%token TOKEN_IDENTIFIER
%token TOKEN_INTEGER
%token TOKEN_LEFT_PARENTHESIS
%token TOKEN_RIGHT_PARENTHESIS
%token TOKEN_LEFT_BRACKET
%token TOKEN_RIGHT_BRACKET
%token TOKEN_LEFT_BRACE
%token TOKEN_RIGHT_BRACE
%token TOKEN_STRING
%token TOKEN_NEWLINE
%token TOKEN_ASSIGNMENT
%token TOKEN_EQUALITY
%token TOKEN_POWER
%token TOKEN_MULTIPLY
%token TOKEN_MINUS
%token TOKEN_PLUS
%token TOKEN_DIVIDE
%token TOKEN_COMMA
%token TOKEN_DOT
%token TOKEN_RANGE
%token TOKEN_COLON
%token TOKEN_PERCENT
%token TOKEN_GREATER_THAN
%token TOKEN_GREATER_THAN_EQUAL
%token TOKEN_LESS_THAN
%token TOKEN_LESS_THAN_EQUAL
%token TOKEN_NOT_EQUAL
%token TOKEN_AND
%token TOKEN_OR
%token TOKEN_NOT
%token TOKEN_DOUBLE

%left TOKEN_OR
%left TOKEN_AND
%left TOKEN_NOT
%left TOKEN_EQUALITY TOKEN_NOT_EQUAL
%left TOKEN_LESS_THAN TOKEN_LESS_THAN_EQUAL TOKEN_GREATER_THAN TOKEN_GREATER_THAN_EQUAL
%left TOKEN_PLUS TOKEN_MINUS
%left TOKEN_MULTIPLY TOKEN_DIVIDE TOKEN_PERCENT
%right TOKEN_POWER

%union {
  struct stmt *stmt;
  struct expr *expr;
  struct decl *decl;
};

%type <stmt> file statement_list statement simple_stmts simple_stmt assignment_stmt compound_stmt print_stmt import_stmt for_stmt while_stmt if_stmt elif_stmt block else_block
%type <expr> star_expr expression name conjunction disjunction inversion comparison sum term factor primary power atom array_element
%type <decl> declaration


%%
file              : statement_list
                    { parser_result = $1; return 0; }
                  ;
statement_list    : statement statement_list
                    { $$ = $1; $1->next = $2; }
                  | statement
                    { $$ = $1; }
                  ;
statement         : compound_stmt
                    { $$ = $1; }
                  | simple_stmts
                    { $$ = $1; }
                  ;
compound_stmt     : if_stmt
                    { $$ = $1; }
                  | while_stmt
                    { $$ = $1; }
                  | for_stmt
                    { $$ = $1; }
                  ;
if_stmt           : TOKEN_KEYWORD_IF expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE elif_stmt
                    { $$ = stmt_create(STMT_IF,0,0,$2,0,$4,$6,0); }
                  | TOKEN_KEYWORD_IF expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE else_block
                    { $$ = stmt_create(STMT_IF,0,0,$2,0,$4,$6,0); }
                  | TOKEN_KEYWORD_IF expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE
                    { $$ = stmt_create(STMT_IF,0,0,$2,0,$4,0,0); }
                  ;
elif_stmt         : TOKEN_KEYWORD_ELSE TOKEN_KEYWORD_IF expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE elif_stmt
                    { $$ = stmt_create(STMT_ELSE_IF,0,0,$3,0,$5,$7,0); }
                  | TOKEN_KEYWORD_ELSE TOKEN_KEYWORD_IF expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE else_block
                    { $$ = stmt_create(STMT_ELSE_IF,0,0,$3,0,$5,$7,0); }
                  | TOKEN_KEYWORD_ELSE TOKEN_KEYWORD_IF expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE
                    { $$ = stmt_create(STMT_IF,0,0,$3,0,$5,0,0); }
                  ;
else_block        : TOKEN_KEYWORD_ELSE TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE
                    { $$ = stmt_create(STMT_ELSE,0,0,0,0,$3,0,0); }
                  ;
for_stmt          : TOKEN_KEYWORD_FOR assignment_stmt TOKEN_RANGE expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE
                    { $$ = stmt_create(STMT_FOR,$2->decl,$2->decl->value,0,$4,$6,0,0); }
                  ;
while_stmt        : TOKEN_KEYWORD_WHILE expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE
                    { $$ = stmt_create(STMT_WHILE,0,0,$2,0,$4,0,0); }
                  ;
block             : TOKEN_NEWLINE statement_list
                    { $$ = $2; }
                  ;
name              : TOKEN_IDENTIFIER
                    { $$ = expr_create_name(yytext); }
                  ;
declaration       : TOKEN_KEYWORD_LET name TOKEN_ASSIGNMENT expression
                    { $$ = decl_create($2,0,$4,0,0); }
                  | TOKEN_KEYWORD_VAR name TOKEN_ASSIGNMENT expression
                    { $$ = decl_create($2,0,$4,0,0); }
                  | name TOKEN_ASSIGNMENT expression
                    { $$ = decl_create($1,0,$3,0,0); }
                  | array_element TOKEN_ASSIGNMENT expression
                    { $$ = decl_create($1,0,$3,0,0); }
                  | name TOKEN_KEYWORD_IN expression
                    { $$ = decl_create($1,0,$3,0,0); }
                  ;
array_element     : name TOKEN_LEFT_BRACKET expression TOKEN_RIGHT_BRACKET
                    { $$ = expr_create(EXPR_SUBSCRIPT,$1,$3); }
                  ;
simple_stmts      : simple_stmt TOKEN_NEWLINE
                    { $$ = $1; }
                  ;
simple_stmt       : assignment_stmt
                    { $$ = $1; }
                  | import_stmt
                    { $$ = $1; }
                  | print_stmt
                    { $$ = $1; }
                  | /* empty */
                    { $$ = NULL; }
                  ;
assignment_stmt   : declaration
                    { $$ = stmt_create(STMT_DECL,$1,0,0,0,0,0,0); }
                  ;
print_stmt        : TOKEN_KEYWORD_PRINT TOKEN_LEFT_PARENTHESIS expression TOKEN_RIGHT_PARENTHESIS
                    { $$ = stmt_create(STMT_PRINT,0,0,$3,0,0,0,0); }
                  ;
import_stmt       : TOKEN_KEYWORD_IMPORT name
                    { $$ = stmt_create(STMT_IMPORT,0,0,$2,0,0,0,0); }
                  ;
expression        : conjunction
                    { $$ = $1; }
                  ;
conjunction       : conjunction TOKEN_AND disjunction
                    { $$ = expr_create(EXPR_AND,$1,$3); }
                  | disjunction
                    { $$ = $1; }
                  ;
disjunction       : disjunction TOKEN_OR inversion
                    { $$ = expr_create(EXPR_OR,$1,$3); }
                  | inversion
                    { $$ = $1; }
                  ;
inversion         : TOKEN_NOT comparison
                    { $$ = expr_create(EXPR_NOT,$2,0); }
                  | comparison
                    { $$ = $1; }
                  ;
comparison        : sum TOKEN_GREATER_THAN sum
                    { $$ = expr_create(EXPR_GREATER_THAN,$1,$3); }
                  | sum TOKEN_LESS_THAN sum
                    { $$ = expr_create(EXPR_LESS_THAN,$1,$3); }
                  | sum TOKEN_EQUALITY sum
                    { $$ = expr_create(EXPR_EQUAL_EQUAL,$1,$3); }
                  | sum TOKEN_GREATER_THAN_EQUAL sum
                    { $$ = expr_create(EXPR_GREATER_THAN_OR_EQUAL,$1,$3); }
                  | sum TOKEN_LESS_THAN_EQUAL sum
                    { $$ = expr_create(EXPR_LESS_THAN_OR_EQUAL,$1,$3); }
                  | sum TOKEN_NOT_EQUAL sum
                    { $$ = expr_create(EXPR_NOT_EQUAL,$1,$3); }
                  | sum
                    { $$ = $1; }
                  ;
sum               : sum TOKEN_PLUS term
                    { $$ = expr_create(EXPR_ADD,$1,$3); }
                  | sum TOKEN_MINUS term
                    { $$ = expr_create(EXPR_SUBTRACT,$1,$3); }
                  | term
                    { $$ = $1; }
                  ;
term              : term TOKEN_MULTIPLY factor
                    { $$ = expr_create(EXPR_MULTIPLY,$1,$3); }
                  | term TOKEN_DIVIDE factor
                    { $$ = expr_create(EXPR_DIVIDE,$1,$3); }
                  | factor
                    { $$ = $1; }
                  ;
factor            : TOKEN_MINUS factor
                    { $$ = expr_create(EXPR_NEGATIVE,0,$2); }
                  | power
                    { $$ = $1; }
                  ;
power             : primary TOKEN_POWER factor
                    { $$ = expr_create(EXPR_POWER, $1, $3); }
                  | primary
                    { $$ = $1; }
                  ;
primary           : primary TOKEN_DOT TOKEN_KEYWORD_COUNT
                    { $$ = expr_create(EXPR_COUNT,$1,0); }
                  | primary TOKEN_DOT TOKEN_SQUAREROOT TOKEN_LEFT_PARENTHESIS TOKEN_RIGHT_PARENTHESIS
                    { $$ = expr_create(EXPR_SQRT,$1,0); }
                  | atom
                    { $$ = $1; }
                  ;
atom              : name
                    { $$ = $1; }
                  | TOKEN_STRING
                    { $$ = expr_create_string_literal(yytext); }
                  | TOKEN_INTEGER
                    { $$ = expr_create_integer_literal(atoi(yytext)); }
                  | TOKEN_DOUBLE
                    { $$ = expr_create_float_literal(atof(yytext)); }
                  | TOKEN_LEFT_PARENTHESIS expression TOKEN_RIGHT_PARENTHESIS
                    { $$ = $2; }
                  | array_element
                    { $$ = $1; }
                  | TOKEN_LEFT_BRACKET star_expr TOKEN_RIGHT_BRACKET
                    { $$ = $2; }
                  ;
star_expr         : expression
                    { $$ = expr_create(EXPR_ARRAY,$1,0); }
                  | expression TOKEN_COMMA star_expr
                    { $$ = expr_create(EXPR_ARRAY,$1,$3); }
%%

void yyerror(const char* msg) {
    fprintf(stderr, "Error | Line: %d\n%s\n", yylineno, msg);
}


