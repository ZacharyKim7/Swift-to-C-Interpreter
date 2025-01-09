#include "token.h"
// https://github.com/sheredom/utest.h/blob/master/utest.h
#include "utest.h"
#include <stdio.h>

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern void yyrestart(FILE * input_file);
extern YY_BUFFER_STATE yy_scan_buffer(char *str, int i);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern FILE *yyin;
extern int yylex(void);
extern char *yytext;

UTEST_MAIN();

struct token_st {
  token_t t;
  char *p;
};

UTEST(scanner, hello) {
    struct token_st tokens[] = {
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_STRING, "\"Hello, World!\""},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        {TOKEN_EOF, ""},
    };
    yyin = fopen("samples/hello.swift", "r");
    ASSERT_TRUE(yyin);
    int index = 0;
    token_t t;
    do {
        ASSERT_EQ(tokens[index].t, (t = yylex()));
        ASSERT_STREQ(tokens[index].p, yytext);
        ++index;
    } while (t != TOKEN_EOF);
}

//UTEST(scanner, assignment) {
//  token_t t;
//  // Must include the null character to terminate input
//  char string[] = "=\0"; 
//  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));
//
//  ASSERT_EQ(TOKEN_ASSIGNMENT, (t = yylex()));
//  ASSERT_STREQ("=", yytext);
//
//  ASSERT_EQ(TOKEN_EOF, (t = yylex()));
//  ASSERT_STREQ("", yytext);
//
//  yy_delete_buffer(buffer);
//}

UTEST(scanner, sort) {
  struct token_st tokens[] = {
      {TOKEN_KEYWORD_VAR, "var"},
      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_LEFT_BRACKET, "["},
      {TOKEN_INTEGER, "4"},
      {TOKEN_COMMA, ","},
      {TOKEN_INTEGER, "3"},
      {TOKEN_COMMA, ","},
      {TOKEN_INTEGER, "2"},
      {TOKEN_COMMA, ","},
      {TOKEN_INTEGER, "1"},
      {TOKEN_COMMA, ","},
      {TOKEN_INTEGER, "5"},
      {TOKEN_COMMA, ","},
      {TOKEN_INTEGER, "9"},
      {TOKEN_COMMA, ","},
      {TOKEN_INTEGER, "7"},
      {TOKEN_COMMA, ","},
      {TOKEN_INTEGER, "0"},
      {TOKEN_COMMA, ","},
      {TOKEN_INTEGER, "6"},
      {TOKEN_COMMA, ","},
      {TOKEN_INTEGER, "8"},
      {TOKEN_RIGHT_BRACKET, "]"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_KEYWORD_LET, "let"},
      {TOKEN_IDENTIFIER, "n"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_DOT, "."},
      {TOKEN_KEYWORD_COUNT, "count"},
      {TOKEN_NEWLINE, "\n\n"},
      
      {TOKEN_KEYWORD_PRINT, "print"},
      {TOKEN_LEFT_PARENTHESIS, "("},
      {TOKEN_STRING, "\"Unsorted array is: \""},
      {TOKEN_RIGHT_PARENTHESIS, ")"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_KEYWORD_VAR, "var"},
      {TOKEN_IDENTIFIER, "k"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_INTEGER, "0"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_KEYWORD_WHILE, "while"},
      {TOKEN_IDENTIFIER, "k"},
      {TOKEN_LESS_THAN, "<"},
      {TOKEN_IDENTIFIER, "n"},
      {TOKEN_LEFT_BRACE, "{"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_KEYWORD_PRINT, "print"},
      {TOKEN_LEFT_PARENTHESIS, "("},
      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_LEFT_BRACKET, "["},
      {TOKEN_IDENTIFIER, "k"},
      {TOKEN_RIGHT_BRACKET, "]"},
      {TOKEN_RIGHT_PARENTHESIS, ")"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_IDENTIFIER, "k"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_IDENTIFIER, "k"},
      {TOKEN_PLUS, "+"},
      {TOKEN_INTEGER, "1"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_RIGHT_BRACE, "}"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_KEYWORD_PRINT, "print"},
      {TOKEN_LEFT_PARENTHESIS, "("},
      {TOKEN_RIGHT_PARENTHESIS, ")"},
      {TOKEN_NEWLINE, "\n"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_KEYWORD_FOR, "for"},
      {TOKEN_IDENTIFIER, "i"},
      {TOKEN_KEYWORD_IN, "in"},
      {TOKEN_INTEGER, "1"},
      {TOKEN_RANGE, "..."},
      {TOKEN_IDENTIFIER, "n"},
      {TOKEN_MINUS, "-"},
      {TOKEN_INTEGER, "1"},
      {TOKEN_LEFT_BRACE, "{"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_KEYWORD_VAR, "var"},
      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_IDENTIFIER, "i"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_KEYWORD_WHILE, "while"},
      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_GREATER_THAN, ">"},
      {TOKEN_INTEGER, "0"},
      {TOKEN_AND, "&&"},
      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_LEFT_BRACKET, "["},
      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_RIGHT_BRACKET, "]"},
      {TOKEN_LESS_THAN, "<"},
      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_LEFT_BRACKET, "["},
      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_MINUS, "-"},
      {TOKEN_INTEGER, "1"},
      {TOKEN_RIGHT_BRACKET, "]"},
      {TOKEN_LEFT_BRACE, "{"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_KEYWORD_LET, "let"},
      {TOKEN_IDENTIFIER, "temp"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_LEFT_BRACKET, "["},
      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_RIGHT_BRACKET, "]"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_LEFT_BRACKET, "["},
      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_RIGHT_BRACKET, "]"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_LEFT_BRACKET, "["},
      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_MINUS, "-"},
      {TOKEN_INTEGER, "1"},
      {TOKEN_RIGHT_BRACKET, "]"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_LEFT_BRACKET, "["},
      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_MINUS, "-"},
      {TOKEN_INTEGER, "1"},
      {TOKEN_RIGHT_BRACKET, "]"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_IDENTIFIER, "temp"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_IDENTIFIER, "j"},
      {TOKEN_MINUS, "-"},
      {TOKEN_INTEGER, "1"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_RIGHT_BRACE, "}"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_RIGHT_BRACE, "}"},
      {TOKEN_NEWLINE, "\n\n"},

      {TOKEN_KEYWORD_PRINT, "print"},
      {TOKEN_LEFT_PARENTHESIS, "("},
      {TOKEN_STRING, "\"Sorted array is: \""},
      {TOKEN_RIGHT_PARENTHESIS, ")"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_KEYWORD_VAR, "var"},
      {TOKEN_IDENTIFIER, "m"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_INTEGER, "0"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_KEYWORD_WHILE, "while"},
      {TOKEN_IDENTIFIER, "m"},
      {TOKEN_LESS_THAN, "<"},
      {TOKEN_IDENTIFIER, "n"},
      {TOKEN_LEFT_BRACE, "{"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_KEYWORD_PRINT, "print"},
      {TOKEN_LEFT_PARENTHESIS, "("},
      {TOKEN_IDENTIFIER, "array"},
      {TOKEN_LEFT_BRACKET, "["},
      {TOKEN_IDENTIFIER, "m"},
      {TOKEN_RIGHT_BRACKET, "]"},
      {TOKEN_RIGHT_PARENTHESIS, ")"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_IDENTIFIER, "m"},
      {TOKEN_ASSIGNMENT, "="},
      {TOKEN_IDENTIFIER, "m"},
      {TOKEN_PLUS, "+"},
      {TOKEN_INTEGER, "1"},
      {TOKEN_NEWLINE, "\n"},

      {TOKEN_RIGHT_BRACE, "}"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_KEYWORD_PRINT, "print"},
      {TOKEN_LEFT_PARENTHESIS, "("},
      {TOKEN_RIGHT_PARENTHESIS, ")"},
      {TOKEN_NEWLINE, "\n"},
      
      {TOKEN_EOF, ""}
  };
  yyin = fopen("samples/sorting.swift", "r");
  ASSERT_TRUE(yyin);
  int index = 0;
  token_t t;
  do {
//      printf("index: %d token: %d text: %s\n", index, t, yytext);
    ASSERT_EQ(tokens[index].t, (t = yylex()));
    ASSERT_STREQ(tokens[index].p, yytext);
    ++index;
  } while (t != TOKEN_EOF);
}


UTEST(scanner, quadratic) {
    struct token_st tokens[] = {
        {TOKEN_KEYWORD_LET, "let"},
        {TOKEN_IDENTIFIER, "a"},
        {TOKEN_ASSIGNMENT, "="},
        {TOKEN_DOUBLE, "1.0"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_LET, "let"},
        {TOKEN_IDENTIFIER, "b"},
        {TOKEN_ASSIGNMENT, "="},
        {TOKEN_MINUS, "-"},
        {TOKEN_DOUBLE, "3.0"},
        {TOKEN_NEWLINE, "\n"},
        //
        {TOKEN_KEYWORD_LET, "let"},
        {TOKEN_IDENTIFIER, "c"},
        {TOKEN_ASSIGNMENT, "="},
        {TOKEN_DOUBLE, "2.0"},
        {TOKEN_NEWLINE, "\n"},
        //
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_STRING, "\"a: \""},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        //
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_IDENTIFIER, "a"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_STRING, "\"b: \""},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_IDENTIFIER, "b"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_STRING, "\"c: \""},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_IDENTIFIER, "c"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n\n"},
        
        {TOKEN_KEYWORD_LET, "let"},
        {TOKEN_IDENTIFIER, "discriminant"},
        {TOKEN_ASSIGNMENT, "="},
        {TOKEN_IDENTIFIER, "b"},
        {TOKEN_MULTIPLY, "*"},
        {TOKEN_IDENTIFIER, "b"},
        {TOKEN_MINUS, "-"},
        {TOKEN_INTEGER, "4"},
        {TOKEN_MULTIPLY, "*"},
        {TOKEN_IDENTIFIER, "a"},
        {TOKEN_MULTIPLY, "*"},
        {TOKEN_IDENTIFIER, "c"},
        {TOKEN_NEWLINE, "\n"},
    
        {TOKEN_KEYWORD_IF, "if"},
        {TOKEN_IDENTIFIER, "discriminant"},
        {TOKEN_GREATER_THAN, ">"},
        {TOKEN_INTEGER, "0"},
        {TOKEN_LEFT_BRACE, "{"},
        {TOKEN_NEWLINE, "\n"},
       
        {TOKEN_KEYWORD_LET, "let"},
        {TOKEN_IDENTIFIER, "answer1"},
        {TOKEN_ASSIGNMENT, "="},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_MINUS, "-"},
        {TOKEN_IDENTIFIER, "b"},
        {TOKEN_PLUS, "+"},
        {TOKEN_IDENTIFIER, "discriminant"},
        {TOKEN_DOT, "."},
        {TOKEN_SQUAREROOT, "squareRoot"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_DIVIDE, "/"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_INTEGER, "2"},
        {TOKEN_MULTIPLY, "*"},
        {TOKEN_IDENTIFIER, "a"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},

        {TOKEN_KEYWORD_LET, "let"},
        {TOKEN_IDENTIFIER, "answer2"},
        {TOKEN_ASSIGNMENT, "="},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_MINUS, "-"},
        {TOKEN_IDENTIFIER, "b"},
        {TOKEN_MINUS, "-"},
        {TOKEN_IDENTIFIER, "discriminant"},
        {TOKEN_DOT, "."},
        {TOKEN_SQUAREROOT, "squareRoot"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_DIVIDE, "/"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_INTEGER, "2"},
        {TOKEN_MULTIPLY, "*"},
        {TOKEN_IDENTIFIER, "a"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_STRING, "\"Root 1: \""},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_IDENTIFIER, "answer1"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_STRING, "\"Root 2: \""},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_IDENTIFIER, "answer2"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_RIGHT_BRACE, "}"},
        {TOKEN_KEYWORD_ELSE_IF, "else if"},
        {TOKEN_IDENTIFIER, "discriminant"},
        {TOKEN_EQUALITY, "=="},
        {TOKEN_INTEGER, "0"},
        {TOKEN_LEFT_BRACE, "{"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_LET, "let"},
        {TOKEN_IDENTIFIER, "root"},
        {TOKEN_ASSIGNMENT, "="},
        {TOKEN_MINUS, "-"},
        {TOKEN_IDENTIFIER, "b"},
        {TOKEN_DIVIDE, "/"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_INTEGER, "2"},
        {TOKEN_MULTIPLY, "*"},
        {TOKEN_IDENTIFIER, "a"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_STRING, "\"One root: \""},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_IDENTIFIER, "root"},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_RIGHT_BRACE, "}"},
        {TOKEN_KEYWORD_ELSE, "else"},
        {TOKEN_LEFT_BRACE, "{"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_KEYWORD_PRINT, "print"},
        {TOKEN_LEFT_PARENTHESIS, "("},
        {TOKEN_STRING, "\"No real roots.\""},
        {TOKEN_RIGHT_PARENTHESIS, ")"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_RIGHT_BRACE, "}"},
        {TOKEN_NEWLINE, "\n"},
        
        {TOKEN_EOF, ""}
        
        
   };
   yyin = fopen("samples/quadratic.swift", "r");
   ASSERT_TRUE(yyin);
   int index = 0;
   token_t t;
   do {
 //      printf("index: %d token: %d text: %s\n", index, t, yytext);
     ASSERT_EQ(tokens[index].t, (t = yylex()));
     ASSERT_STREQ(tokens[index].p, yytext);
     ++index;
   } while (t != TOKEN_EOF);
 }
