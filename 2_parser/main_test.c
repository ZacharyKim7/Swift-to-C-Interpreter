// https://github.com/sheredom/utest.h/blob/master/utest.h
#include "utest.h"
#include <stdio.h>

extern int yyparse();

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyrestart();
extern YY_BUFFER_STATE yy_scan_buffer(char *str, int i);
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern FILE *yyin;
extern int yylineno;

UTEST_MAIN();

// Passing test for assignment
UTEST(parser, assignment_pass) {
  char string[] = "let a = 5\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);
}

// Failing test for assignment
UTEST(parser, assignment_fail) {
  char string[] = "let = 5\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 1);
}

// Passing test for print
UTEST(parser, print_pass) {
  char string[] = "print('hi')\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);
}

// Failing test for print
UTEST(parser, print_fail) {
  char string[] = "print('hi'\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 1);
}

// Passing test for math
UTEST(parser, math_pass) {
  char string[] = "3*1+8/4-3\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 0); 
}

// Failing test for math
UTEST(parser, parser_math_fail) {
  char string[] = "3*1+8//4-3\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 1); 
}

// Passing test for boolean expressions
UTEST(parser, boolean_pass) {
  char string[] = "day >= 4\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);
}

// Failing test for boolean expressions
UTEST(parser, boolean_fail) {
  char string[] = "day >=< 4\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 1);
}

UTEST(parser, boolean_pass_AND) {
  char string[] = "blue && yellow\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);
}

UTEST(parser, boolean_fail_AND) {
  char string[] = "blue & yellow\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 1);
}

// Test OR
UTEST(parser, boolean_pass_OR) {
  char string[] = "blue || yellow\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);
}

UTEST(parser, boolean_fail_OR) {
  char string[] = "blue | yellow\n\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 1);
}

// Passing test for branching
UTEST(parser, branching_pass) {
  char string[] = "if num > 5 {\n number + 5\n} else if num < 5 {\n number = 5\n} else {\n number - 5\n}\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);
}

// Failing test for branching
UTEST(parser, branching_fail) {
  char string[] = "if num > 5 {\n number + 5\n else if num < 5 {\n number = 5\n} else {\n number - 5\n}\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 1);
}

// Passing test for looping
UTEST(parser, while_loop_pass) {
  char string[] = "while something > 3 {\n another = 6\n}\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);
}

// Failing test for looping
UTEST(parser, while_loop_fail) {
  char string[] = "while something > 3 \n another = 6\n}\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 1);
}

UTEST(parser, for_loop_pass) {
  char string[] = "for i in thing {\n do_something \n}\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);
}

UTEST(parser, for_loop_fail) {
  char string[] = "for {\n do_something \n}\0";
  YY_BUFFER_STATE buffer = yy_scan_buffer(string, sizeof(string));

  yylineno = 1;
  int result = yyparse();

  yy_delete_buffer(buffer);

  // Assert the result to test correctness
  ASSERT_EQ(result, 1);
}

// Passing test for hello
UTEST(parser, hello_world) {
  // Read sample file as input
  yyin = fopen("samples/hello.swift", "r");
  yyrestart(yyin);
  ASSERT_TRUE(yyin);

  yylineno = 1;
  int result = yyparse();

  // Assert the result to test correctness
  ASSERT_EQ(result, 0); 
}

// Passing test for quadratic
UTEST(parser, quadratic) {
  // Read sample file as input
  yyin = fopen("samples/quadratic.swift", "r");
  yyrestart(yyin);
  ASSERT_TRUE(yyin);

  yylineno = 1;
  int result = yyparse();

  // Assert the result to test correctness
  ASSERT_EQ(result, 0); 
}

// Passing test for sorting
UTEST(parser, sorting) {
  // Read sample file as input
  yyin = fopen("samples/sorting.swift", "r");
  yyrestart(yyin);
  ASSERT_TRUE(yyin);

  yylineno = 1;
  int result = yyparse();

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);
}
