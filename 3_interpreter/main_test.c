// https://github.com/sheredom/utest.h/blob/master/utest.h
#include "utest.h"
#include "expr.h"
#include <stdio.h>

/* Clunky: Declare the parse function generated from parser.bison */
extern int yyparse();

/* Clunky: Declare the result of the parser from parser.bison */
extern struct stmt *parser_result;

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern int yyrestart();
extern YY_BUFFER_STATE yy_scan_buffer(char *str, int i);
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern FILE *yyin;
extern int yylineno;

UTEST_MAIN();

char* read_file_dynamic(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        return NULL;
    }

    // Seek to the end of the file to determine its size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate a buffer to hold the file contents
    char* buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("malloc");
        fclose(file);
        return NULL;
    }

    // Read the entire file into the buffer
    size_t read_size = fread(buffer, 1, file_size, file);
    if (read_size != file_size) {
        perror("fread");
        free(buffer);
        fclose(file);
        return NULL;
    }

    // Null-terminate the buffer
    buffer[file_size] = '\0';

    fclose(file);
    return buffer;
}

void redirect_stdout(const char *filename, int evalutate) {
  fflush(stdout);

  // Redirect stdout to a temporary file
  FILE *temp_file = fopen(filename, "w");
  if (temp_file == NULL) {
    perror("tmpfile");
    exit(EXIT_FAILURE);
  }
  int temp_fd = fileno(temp_file);
  int stdout_fd = dup(STDOUT_FILENO);
  dup2(temp_fd, STDOUT_FILENO);

  // Perform operations that generate output
  if (evalutate != 0) {
    stmt_evaluate(parser_result);
  } else {
    stmt_print(parser_result, 0);
  }

  // Flush and close stdout
  fflush(stdout);
  dup2(stdout_fd, STDOUT_FILENO);
  close(stdout_fd);
}

struct InterpreterTestFile {
  const char *evaluated_file;
  const char *evaluated_expected;
  const char *print_file;
  const char *parse_expected;
  const char *test_file;
};

UTEST_F_SETUP(InterpreterTestFile) {
}

UTEST_F_TEARDOWN(InterpreterTestFile) {
  // and also assert and expect in teardown!
  yyin = fopen(utest_fixture->test_file, "r");
  yyrestart(yyin);
  ASSERT_TRUE(yyin);

  yylineno = 1;
  int result = yyparse();

  if (result == 0) {
    // Catch the standard output and compare with expected test result
    redirect_stdout(utest_fixture->print_file, 0);
    redirect_stdout(utest_fixture->evaluated_file, 1);
  }

  // Assert the result to test correctness
  ASSERT_EQ(result, 0);

  char *actual_print = read_file_dynamic(utest_fixture->print_file);
  char *expected_print = read_file_dynamic(utest_fixture->parse_expected);
  ASSERT_STREQ(actual_print, expected_print);

  char *actual_evaluate = read_file_dynamic(utest_fixture->evaluated_file);
  char *expected_evaluate = read_file_dynamic(utest_fixture->evaluated_expected);
  ASSERT_STREQ(actual_evaluate, expected_evaluate);
}

UTEST_F(InterpreterTestFile, print) {
  utest_fixture->test_file = "samples/hello.swift";
    
  utest_fixture->print_file = "samples/output_logs/hello_parsed.txt";
  utest_fixture->parse_expected = "samples/output_logs/hello_parsed_expected.txt";
    
  utest_fixture->evaluated_file = "samples/output_logs/hello_evaluated.txt";
  utest_fixture->evaluated_expected = "samples/output_logs/hello_evaluated_expected.txt";

}

UTEST_F(InterpreterTestFile, program_file) {
  utest_fixture->test_file = "samples/quadratic.swift";
    
  utest_fixture->print_file = "samples/output_logs/quadratic_parsed.txt";
  utest_fixture->parse_expected = "samples/output_logs/quadratic_parsed_expected.txt";
    
  utest_fixture->evaluated_file = "samples/output_logs/quadratic_evaluated.txt";
  utest_fixture->evaluated_expected = "samples/output_logs/quadratic_evaluated_expected.txt";
}

UTEST_F(InterpreterTestFile, program_file2) {
  utest_fixture->test_file = "samples/sorting.swift";
    
  utest_fixture->print_file = "samples/output_logs/sorting_parsed.txt";
  utest_fixture->parse_expected = "samples/output_logs/sorting_parsed_expected.txt";
    
  utest_fixture->evaluated_file = "samples/output_logs/sorting_evaluated.txt";
  utest_fixture->evaluated_expected = "samples/output_logs/sorting_evaluated_expected.txt";
}
