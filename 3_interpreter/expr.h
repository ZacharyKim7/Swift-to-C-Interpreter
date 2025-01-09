/*
expr.h defines the structure of an expression node,
and the operations that can be performed upon it.
Note some things about this file that you should emulate:
- Every symbol in expr.[ch] begins with expr_.
- Use enumerations to define variant types.
- Build complex trees one node at a time.
- Define methods with recurse over those trees.
*/

#ifndef EXPR_H
#define EXPR_H

#include "symbol_map.h"
#include <stdio.h>
#include <stdlib.h>

typedef enum {
  EXPR_ADD,
  EXPR_ARRAY,
  EXPR_DIVIDE,
  EXPR_POWER,
  EXPR_AND,
  EXPR_OR,
  EXPR_NOT,
  EXPR_EQUAL_EQUAL,
  EXPR_FLOAT_LITERAL,
  EXPR_GREATER_THAN,
  EXPR_GREATER_THAN_OR_EQUAL,
  EXPR_INTEGER_LITERAL,
  EXPR_LESS_THAN,
  EXPR_LESS_THAN_OR_EQUAL,
  EXPR_MULTIPLY,
  EXPR_NAME,
  EXPR_NOT_EQUAL,
  EXPR_SQRT,
  EXPR_COUNT,
  EXPR_STRING_LITERAL,
  EXPR_SUBSCRIPT,
  EXPR_SUBTRACT,
  EXPR_NEGATIVE,
} expr_t;

struct expr {
  expr_t kind;
  struct expr *left;
  struct expr *right;
  const char *name;
  int integer_value;
  float float_value;
  const char *string_literal;
};

typedef enum { TYPE_ARRAY, TYPE_FLOAT, TYPE_INTEGER, TYPE_STRING } type_t;

struct type {
  type_t kind;
  struct type *subtype;
};

struct decl {
  struct expr *name;
  int         type;
  struct expr *value;
  struct stmt *code;
  struct decl *next;
};

typedef enum { STMT_BLOCK, STMT_DECL, STMT_EXPR, STMT_IMPORT, STMT_FOR, STMT_WHILE, STMT_IF, STMT_ELSE_IF, STMT_ELSE, STMT_PRINT } stmt_t;

struct stmt {
  stmt_t kind;
  struct decl *decl;
  struct expr *init_expr;
  struct expr *expr;
  struct expr *next_expr;
  struct stmt *body;
  struct stmt *else_body;
  struct stmt *next;
};

static struct SymbolMap *symbol_table = NULL;

struct stmt *stmt_create(stmt_t kind, struct decl *decl, struct expr *init_expr,
                         struct expr *expr, struct expr *next_expr,
                         struct stmt *body, struct stmt *else_body,
                         struct stmt *next);
struct decl *decl_create(struct expr *name, int type,
                         struct expr *value, struct stmt *code,
                         struct decl *next);
struct expr *expr_create_name(const char *name);
struct expr *expr_create_integer_literal(int i);
struct expr *expr_create_float_literal(float f);
struct expr *expr_create_string_literal(const char *str);
struct expr *expr_create(expr_t kind, struct expr *left, struct expr *right);
struct type *type_create(type_t kind, struct type *sub);

void scope_bind(const char *name, struct expr *sym);
struct expr *scope_lookup(const char *name);

void stmt_print(struct stmt *e, int indent_level);
void decl_print(struct decl *d, int indent_level);
void expr_print(struct expr *e);

void stmt_evaluate(struct stmt *e);
void decl_evaluate(struct decl *e);
void decl_subscript_evaluate(struct expr *e, float value);
float expr_evaluate(struct expr *e);
struct expr *expr_sub_evaluate(struct expr *e);
float expr_subscript_evaluate(struct expr *e);
const char *expr_string_evaluate(struct expr *e);

void expr_delete(struct expr *e);
void close_parser();

#endif
