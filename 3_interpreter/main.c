///*
//Main program of calculator example.
//Simply invoke the parser generated by bison, and then display the output.
//*/
//
//#include "expr.h"
//#include <stdio.h>
//
///* Clunky: Declare the parse function generated from parser.bison */
//extern int yyparse();
//
///* Clunky: Declare the result of the parser from parser.bison */
//extern struct stmt *parser_result;
//
//int main(int argc, char *argv[]) {
//  printf("Lab 6 Example Interpreter Compiler\n");
//  printf(
//      "Enter an infix expression using the operators +-*/() ending with ;\n\n");
//
//  if (yyparse() == 0) {
//    printf("Parse successful: ");
//    stmt_print(parser_result, 0);
//    printf("\n");
//    printf("Running the program, results in: \n");
//    stmt_evaluate(parser_result);
//    printf("\n");
//    return 0;
//  } else {
//    printf("Parse failed!\n");
//    return 1;
//  }
//}