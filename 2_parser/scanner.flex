%{
#include "token.h"
%}
NAME            [a-zA-Z_][a-zA-Z0-9_]*
INTEGER         [0-9]+
DOUBLE          [0-9]+(\.[0-9]+)?([eE][-+]?[0-9]+)?
%%
"//".*"\n"       /* comment */
(" "|"\t")+     /* whitespace */
"break"         { return TOKEN_KEYWORD_BREAK; }
"count"         { return TOKEN_KEYWORD_COUNT; }
"false"         { return TOKEN_KEYWORD_FALSE; }
"for"           { return TOKEN_KEYWORD_FOR; }
"func"          { return TOKEN_KEYWORD_FUNC; }
"if"            { return TOKEN_KEYWORD_IF; }
"in"            { return TOKEN_KEYWORD_IN; }
"else"          { return TOKEN_KEYWORD_ELSE; }
"import"        { return TOKEN_KEYWORD_IMPORT; }
"let"           { return TOKEN_KEYWORD_LET; }
"not"           { return TOKEN_KEYWORD_NOT; }
"print"         { return TOKEN_KEYWORD_PRINT; }
"return"        { return TOKEN_KEYWORD_RETURN; }
"true"          { return TOKEN_KEYWORD_TRUE; }
"var"           { return TOKEN_KEYWORD_VAR; }
"while"         { return TOKEN_KEYWORD_WHILE; }
"squareRoot"    { return TOKEN_SQUAREROOT; }
{NAME}          { return TOKEN_IDENTIFIER; }
{INTEGER}       { return TOKEN_INTEGER; }
"("             { return TOKEN_LEFT_PARENTHESIS; }
")"             { return TOKEN_RIGHT_PARENTHESIS; }
"["             { return TOKEN_LEFT_BRACKET; }
"]"             { return TOKEN_RIGHT_BRACKET; }
"{"             { return TOKEN_LEFT_BRACE; }
"}"             { return TOKEN_RIGHT_BRACE; }
"\""[^"]*"\""   { return TOKEN_STRING; }
"\'"[^']*"\'"   { return TOKEN_STRING; }
"\n"+           { return TOKEN_NEWLINE; }
"="             { return TOKEN_ASSIGNMENT; }
"=="            { return TOKEN_EQUALITY; }
"**"            { return TOKEN_POWER; }
"*"             { return TOKEN_MULTIPLY; }
"-"             { return TOKEN_MINUS; }
"+"             { return TOKEN_PLUS; }
"/"             { return TOKEN_DIVIDE; }
","             { return TOKEN_COMMA; }
"."             { return TOKEN_DOT; }
"..."           { return TOKEN_RANGE; }
":"             { return TOKEN_COLON; }
"%"             { return TOKEN_PERCENT; }
">"             { return TOKEN_GREATER_THAN; }
"<"             { return TOKEN_LESS_THAN; }
">="            { return TOKEN_GREATER_THAN_EQUAL; }
"<="            { return TOKEN_LESS_THAN_EQUAL; }
"!="            { return TOKEN_NOT_EQUAL; }
"&&"            { return TOKEN_AND; }
"||"            { return TOKEN_OR; }
"!"             { return TOKEN_NOT; }
{DOUBLE}        { return TOKEN_DOUBLE; }


%%
int yywrap()  { return 1; }

