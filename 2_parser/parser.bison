%{
#define YYDEBUG 1
#include <stdio.h>
extern int yylineno;
void yyerror(const char*);
int yylex();
%}

%debug
%locations

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

%%
file              : statements;
statements        : statements statement
                  | statement
                  ;
statement         : compound_stmt
                  | simple_stmts
                  ;
compound_stmt     : if_stmt
                  | for_stmt
                  | while_stmt
                  ;
if_stmt           : TOKEN_KEYWORD_IF named_expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE elif_stmt
                  | TOKEN_KEYWORD_IF named_expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE else_block
                  | TOKEN_KEYWORD_IF named_expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE
                  ;
elif_stmt         : TOKEN_KEYWORD_ELSE TOKEN_KEYWORD_IF named_expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE elif_stmt
                  | TOKEN_KEYWORD_ELSE TOKEN_KEYWORD_IF named_expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE else_block
                  | TOKEN_KEYWORD_ELSE TOKEN_KEYWORD_IF named_expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE
                  ;
else_block        : TOKEN_KEYWORD_ELSE TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE
                  ;
while_stmt        : TOKEN_KEYWORD_WHILE named_expression TOKEN_LEFT_BRACE block TOKEN_RIGHT_BRACE;
for_stmt          : TOKEN_KEYWORD_FOR TOKEN_IDENTIFIER TOKEN_KEYWORD_IN TOKEN_RANGE TOKEN_IDENTIFIER TOKEN_LEFT_BRACE statements TOKEN_RIGHT_BRACE
                  | TOKEN_KEYWORD_FOR TOKEN_IDENTIFIER TOKEN_KEYWORD_IN TOKEN_IDENTIFIER TOKEN_LEFT_BRACE statements TOKEN_RIGHT_BRACE
                  ;
block             : TOKEN_NEWLINE statements
named_expression  : assignment
                  | expression
                  ;
assignment        : TOKEN_KEYWORD_LET TOKEN_IDENTIFIER TOKEN_ASSIGNMENT expression
                  | TOKEN_KEYWORD_VAR TOKEN_IDENTIFIER TOKEN_ASSIGNMENT expression
                  | TOKEN_IDENTIFIER TOKEN_ASSIGNMENT expression
                  | array_element TOKEN_ASSIGNMENT expression
                  ;
array_element     : TOKEN_IDENTIFIER TOKEN_LEFT_BRACKET expression TOKEN_RIGHT_BRACKET;
expressions       : expressions TOKEN_COMMA expression
                  | expression
                  ; 
simple_stmts      : simple_stmt TOKEN_NEWLINE;
simple_stmt       : assignment
                  | import_stmt
                  | expressions
                  | print_stmt
                  | /* empty */
                  ;
print_stmt        : TOKEN_KEYWORD_PRINT TOKEN_LEFT_PARENTHESIS arguments TOKEN_RIGHT_PARENTHESIS;
                  ;
import_stmt       : TOKEN_KEYWORD_IMPORT TOKEN_IDENTIFIER;
expression        : conjunction
                  ;
conjunction       : conjunction TOKEN_AND disjunction
                  | disjunction
                  ;
disjunction       : disjunction TOKEN_OR inversion
                  | inversion
                  ;
inversion         : TOKEN_NOT comparison
                  | comparison
                  ;
comparison        : sum comparison_op sum
                  | sum
                  ;
comparison_op     : TOKEN_GREATER_THAN
                  | TOKEN_LESS_THAN
                  | TOKEN_EQUALITY
                  | TOKEN_GREATER_THAN_EQUAL
                  | TOKEN_LESS_THAN_EQUAL
                  | TOKEN_NOT_EQUAL
                  ;
sum               : sum TOKEN_PLUS term
                  | sum TOKEN_MINUS term
                  | term
                  ;
term              : term TOKEN_MULTIPLY factor
                  | term TOKEN_DIVIDE factor
                  | factor;
factor            : TOKEN_PLUS factor
                  | TOKEN_MINUS factor
                  | power
                  ;
power             : primary TOKEN_POWER factor
                  | primary
                  ;
primary           : primary TOKEN_DOT TOKEN_IDENTIFIER
                  | primary TOKEN_DOT TOKEN_KEYWORD_COUNT
                  | primary TOKEN_LEFT_PARENTHESIS arguments TOKEN_RIGHT_PARENTHESIS
                  | primary TOKEN_DOT TOKEN_SQUAREROOT TOKEN_LEFT_PARENTHESIS TOKEN_RIGHT_PARENTHESIS
                  | TOKEN_IDENTIFIER TOKEN_LEFT_BRACKET expression TOKEN_RIGHT_BRACKET
                  | atom
                  ;
arguments         : arguments TOKEN_COMMA expression
                  | expression
                  | /* empty */
                  ;
atom              : TOKEN_IDENTIFIER
                  | TOKEN_KEYWORD_TRUE
                  | TOKEN_KEYWORD_FALSE
                  | TOKEN_STRING
                  | TOKEN_INTEGER
                  | TOKEN_DOUBLE
                  | TOKEN_LEFT_PARENTHESIS expression TOKEN_RIGHT_PARENTHESIS
                  | array
                  ;
array             : TOKEN_LEFT_BRACKET elements TOKEN_RIGHT_BRACKET
                  ;
elements          : elements TOKEN_COMMA atom
                  | atom
                  ;
%%

void yyerror(const char* msg) {
    fprintf(stderr, "Error | Line: %d\n%s\n", yylineno, msg);
}
