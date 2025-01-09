
#include "expr.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string.h>

/*
Create one node in an expression tree and return the structure.
*/

struct type *type_create(type_t kind, struct type *sub) {
  struct type *t = malloc(sizeof(*t));
  t->kind = kind;
  t->subtype = sub;
  return t;
}

struct decl *decl_create(struct expr *name, int type,
                         struct expr *value, struct stmt *code,
                         struct decl *next) {
  struct decl *d = malloc(sizeof(*d));
  d->name = name;
  d->type = type;
  d->value = value;
  d->code = code;
  d->next = next;
  return d;
}

struct stmt *stmt_create(stmt_t kind, struct decl *decl, struct expr *init_expr,
                         struct expr *expr, struct expr *next_expr,
                         struct stmt *body, struct stmt *else_body,
                         struct stmt *next) {
  struct stmt *s = malloc(sizeof(*s));
  s->kind = kind;
  s->decl = decl;
  s->init_expr = init_expr;
  s->expr = expr;
  s->next_expr = next_expr;
  s->body = body;
  s->else_body = else_body;
  s->next = next;
  return s;
}

struct expr *expr_create(expr_t kind, struct expr *left, struct expr *right) {
  /* Shortcut: sizeof(*e) means "the size of what e points to" */
  struct expr *e = malloc(sizeof(*e));

  e->kind = kind;
  e->left = left;
  e->right = right;
  e->name = "";
  e->integer_value = 0;
  e->float_value = 0.0;
  e->string_literal = "";

  return e;
}

struct expr *expr_create_name(const char *value) {
  struct expr *e = expr_create(EXPR_NAME, 0, 0);
  char *dest = malloc(sizeof(*value));
  strcpy(dest, value); // copy contents of source to dest
  e->name = dest;
  return e;
}

struct expr *expr_create_integer_literal(int value) {
  struct expr *e = expr_create(EXPR_INTEGER_LITERAL, 0, 0);
  e->integer_value = value;
  return e;
}

struct expr *expr_create_float_literal(float value) {
  struct expr *e = expr_create(EXPR_FLOAT_LITERAL, 0, 0);
  e->float_value = value;
  return e;
}

struct expr *expr_create_string_literal(const char *value) {
  struct expr *e = expr_create(EXPR_STRING_LITERAL, 0, 0);
  e->string_literal = strdup(value);
  return e;
}

/*
Recursively delete an expression tree.
*/

void expr_delete(struct expr *e) {
  /* Careful: Stop on null pointer. */
  if (!e)
    return;
  expr_delete(e->left);
  expr_delete(e->right);
  free(e);
}

void scope_bind(const char *name, struct expr *value) {
//    printf("scope %f\n", expr_evaluate(value));
//    printf("name %c\n", *name);
  if (symbol_table == NULL) {
//      printf("here");
    symbol_table = createSymbolMap();
  }
  insertSymbol(symbol_table, name, value);
}

void scope_remove(const char *name) {
    if (symbol_table == NULL) {
      symbol_table = createSymbolMap();
    }
    deleteSymbol(symbol_table, name);
}

struct expr *scope_lookup(const char *name) {
  return getSymbol(symbol_table, name);
}

/*
Recursively print an expression tree by performing an
in-order traversal of the tree, printing the current node
between the left and right nodes.
*/

void print_indent(int level) {
    for (int i = 0; i < level; i++) {
        printf("    ");  // Print four spaces for each indent level
    }
}

void stmt_print(struct stmt *s, int indent_level) {
  if (!s)
    return;

  switch (s->kind) {
  case STMT_DECL:
    decl_print(s->decl, indent_level);
    printf("\n");
    break;
  case STMT_EXPR:
    expr_print(s->expr);
    break;
  case STMT_IMPORT:
    printf("import ");
    expr_print(s->expr);
    printf("\n");
    break;
  case STMT_FOR:
    print_indent(indent_level);
    printf("for ");
    printf(s->decl->name->name);
    printf(" in ");
    expr_print(s->init_expr);
    printf("...");
    expr_print(s->next_expr);
    printf(" {\n");
    stmt_print(s->body, indent_level + 1);
    print_indent(indent_level);
    printf("}\n");
    break;
  case STMT_WHILE:
    printf("while ");
    expr_print(s->expr);
    printf(" {\n");
    stmt_print(s->body, indent_level + 1);
    printf("}\n");
    break;
  case STMT_IF:
      print_indent(indent_level);
      printf("if ");
      expr_print(s->expr);
      printf(" {\n");
      stmt_print(s->body, indent_level + 1);
      print_indent(indent_level);
      if (s->else_body) {
          printf("} ");
          stmt_print(s->else_body, indent_level);
      } else {
          printf("}\n");
      }
      break;
  case STMT_ELSE_IF:
      print_indent(indent_level);
      printf("else if ");
      expr_print(s->expr);
      printf(" {\n");
      stmt_print(s->body, indent_level + 1);
      print_indent(indent_level);
      printf("} ");
      if (s->else_body) {
          stmt_print(s->else_body, indent_level);
      }
      break;

  case STMT_ELSE:
      print_indent(indent_level);
      printf("else {\n");
      stmt_print(s->body, indent_level + 1);
      print_indent(indent_level);
      printf("}\n");
      break;

  case STMT_PRINT:
      print_indent(indent_level);
      printf("print(");
      expr_print(s->expr);
      printf(")\n");
      break;
  case STMT_BLOCK:
    stmt_print(s->body, indent_level);
    break;
  }

  stmt_print(s->next, indent_level);
}

void decl_print(struct decl *d, int indent_level) {
  print_indent(indent_level);
  if (d->value->kind == EXPR_ARRAY) {
    printf("var ");
  } else if (d->type == 1) {
      printf("let ");
  }
  expr_print(d->name);
  printf(" = ");
  if (d->value->kind == EXPR_ARRAY) {
    printf("[");
  }
  expr_print(d->value);
  if (d->value->kind == EXPR_ARRAY) {
    printf("]");
  }
}

void expr_print(struct expr *e) {
  /* Careful: Stop on null pointer. */
  if (!e)
    return;

//  if (e->kind != EXPR_NAME && e->kind != EXPR_ARRAY) {
//    printf("(");
//  }

  expr_print(e->left);

  switch (e->kind) {
  case EXPR_NAME:
    printf("%s", e->name);
    break;
  case EXPR_ARRAY:
    if (e->right) {
      printf(", ");
    }
    break;
  case EXPR_SUBSCRIPT:
    printf("[");
    break;
  case EXPR_ADD:
    printf(" + ");
    break;
  case EXPR_SUBTRACT:
    printf(" - ");
    break;
  case EXPR_MULTIPLY:
    printf(" * ");
    break;
  case EXPR_DIVIDE:
    printf(" / ");
    break;
  case EXPR_POWER:
    printf(" ** ");
    break;
  case EXPR_NEGATIVE:
    printf("-");
    break;
  case EXPR_SQRT:
    printf(".squareRoot()");
    break;
  case EXPR_COUNT:
    printf(".count");
    break;
  case EXPR_EQUAL_EQUAL:
    printf(" == ");
    break;
  case EXPR_NOT_EQUAL:
    printf(" != ");
    break;
  case EXPR_GREATER_THAN:
    printf(" > ");
    break;
  case EXPR_GREATER_THAN_OR_EQUAL:
    printf(" >= ");
    break;
  case EXPR_LESS_THAN:
    printf(" < ");
    break;
  case EXPR_LESS_THAN_OR_EQUAL:
    printf(" <= ");
    break;
  case EXPR_AND:
    printf(" && ");
    break;
  case EXPR_OR:
    printf(" || ");
    break;
  case EXPR_NOT:
    printf(" !");
    break;
  case EXPR_INTEGER_LITERAL:
    printf("%d", e->integer_value);
    break;
  case EXPR_FLOAT_LITERAL:
    printf("%.1f", e->float_value);
    break;
  case EXPR_STRING_LITERAL:
    printf("%s", e->string_literal);
    break;
  }

  expr_print(e->right);

  // Options for closing
  if (e->kind == EXPR_SUBSCRIPT) {
    printf("]");
  }
//  if (e->kind != EXPR_NAME && e->kind != EXPR_ARRAY) {
//    printf(")");
//  }
}

/*
Recursively evaluate an expression by performing
the desired operation and returning it up the tree.
*/

void stmt_evaluate(struct stmt *s) {
  if (!s)
    return;

  switch (s->kind) {
  case STMT_DECL:
    decl_evaluate(s->decl);
    break;
  case STMT_EXPR:
    expr_evaluate(s->expr);
    break;
  case STMT_IMPORT:
    break;
  case STMT_FOR:
      for (int i = expr_evaluate(s->init_expr); i <= expr_evaluate(s->next_expr); i = i + 1) {
        scope_bind(s->decl->name->name, expr_create_integer_literal(i));
        stmt_evaluate(s->body);
    }
    break;
  case STMT_WHILE:
    while (expr_evaluate(s->expr)) {
      stmt_evaluate(s->body);
    }
    break;
  case STMT_IF:
    if (expr_evaluate(s->expr)) {
      stmt_evaluate(s->body);
    }  else if (s->else_body) {
      stmt_evaluate(s->else_body);
    }
    break;
  case STMT_ELSE_IF:
    if (expr_evaluate(s->expr)) {
        stmt_evaluate(s->body);
    } else if (s->else_body) {
      stmt_evaluate(s->else_body);
    }
    break;
  case STMT_ELSE:
    stmt_evaluate(s->body);
    break;
  case STMT_PRINT:
    if (s->expr->kind == EXPR_STRING_LITERAL) {
//      printf("%s\n", expr_string_evaluate(s->expr));
      printf("%.*s\n", (int)strlen(s->expr->string_literal) - 2, s->expr->string_literal + 1);
    } else if (s->expr->kind == EXPR_FLOAT_LITERAL) {
      printf("%f\n", expr_evaluate(s->expr));
    } else if (s->expr->kind == EXPR_INTEGER_LITERAL ||
               s->expr->kind == EXPR_NAME || s->expr->kind == EXPR_SUBSCRIPT) {
      printf("%.0f\n", expr_evaluate(s->expr));
    } else {
      printf("%f\n", expr_evaluate(s->expr));
    }
    break;
  case STMT_BLOCK:
    stmt_evaluate(s->body);
    break;
  }

  stmt_evaluate(s->next);
}

void decl_evaluate(struct decl *d) {
  if (!d)
    return;

  if (d->name->kind == EXPR_NAME && d->value->kind == EXPR_ARRAY) {
    struct expr *e = expr_sub_evaluate(d->value);
    scope_bind(d->name->name, e);
  } else if (d->name->kind == EXPR_NAME) {
    float value = expr_evaluate(d->value);
    struct expr *e = expr_create_float_literal(value);
    scope_bind(d->name->name, e);
  } else if (d->name->kind == EXPR_SUBSCRIPT) {
    float value = expr_evaluate(d->value);
    decl_subscript_evaluate(d->name, value);
  } else {
    printf("Error: expression type unknown for name");
    exit(1);
  }
}

void decl_subscript_evaluate(struct expr *e, float value) {
  /* Careful: Return zero on null pointer. */
  if (!e)
    return;

  if (e->kind != EXPR_SUBSCRIPT) {
    printf("runtime error: not a subscript expression\n");
    exit(1);
  }

  if (e->left->kind != EXPR_NAME) {
    printf("runtime error: subscript has no name\n");
    exit(1);
  }

  // Get array expresion
  struct expr *a = scope_lookup(e->left->name);
  float index = expr_evaluate(e->right);

  // Find the right offset
  while (index > 0) {
    a = a->right;
    index--;
  }
  expr_delete(a->left);
  a->left = expr_create_float_literal(value);
}

const char *expr_string_evaluate(struct expr *e) {
  /* Careful: Return zero on null pointer. */
  if (!e)
    return 0;

  switch (e->kind) {
  case EXPR_NAME:
  case EXPR_ARRAY:
  case EXPR_SUBSCRIPT:
  case EXPR_ADD:
  case EXPR_SUBTRACT:
  case EXPR_NEGATIVE:
  case EXPR_MULTIPLY:
  case EXPR_DIVIDE:
  case EXPR_POWER:
  case EXPR_SQRT:
  case EXPR_COUNT:
  case EXPR_EQUAL_EQUAL:
  case EXPR_NOT_EQUAL:
  case EXPR_GREATER_THAN:
  case EXPR_GREATER_THAN_OR_EQUAL:
  case EXPR_LESS_THAN:
  case EXPR_LESS_THAN_OR_EQUAL:
  case EXPR_AND:
  case EXPR_OR:
  case EXPR_NOT:
  case EXPR_INTEGER_LITERAL:
  case EXPR_STRING_LITERAL:
  case EXPR_FLOAT_LITERAL:
    printf("runtime error: not a string expression\n");
    exit(1);
  }

  return "";
}

struct expr *expr_sub_evaluate(struct expr *e) {
  /* Careful: Return zero on null pointer. */
  if (!e)
    return 0;

  // TODO evaluate each item in the array and save the result

  return e;
}

/*
Recursively evaluate an expression by performing
the desired operation and returning it up the tree.
*/

float expr_subscript_evaluate(struct expr *e) {
    /* Careful: Return zero on null pointer. */
    if (!e)
      return 0;

    if (e->kind != EXPR_SUBSCRIPT) {
      printf("runtime error: not a subscript expression\n");
      exit(1);
    }

    if (e->left->kind != EXPR_NAME) {
      printf("runtime error: subscript has no name\n");
      exit(1);
    }

    // Get array expresion
    struct expr *a = scope_lookup(e->left->name);
    float index = expr_evaluate(e->right);

    // Find the right offset
    while (index > 0) {
      a = a->right;
      index--;
    }
    return expr_evaluate(a->left);
  }

float expr_evaluate(struct expr *e) {
  /* Careful: Return zero on null pointer. */
  if (!e)
    return 0;

  if (e->kind == EXPR_SUBSCRIPT) {
    return expr_subscript_evaluate(e);
  }
    

  float l = expr_evaluate(e->left);
  float r = expr_evaluate(e->right);

  switch (e->kind) {
  case EXPR_NAME:
    // Get the variable expression and then evaluate it.
    return expr_evaluate(scope_lookup(e->name));
  case EXPR_ARRAY:
    return l;
  case EXPR_SUBSCRIPT:
    printf(
        "runtime error: subscript should be processed earlier in expression\n");
    exit(1);
  case EXPR_ADD:
    return l + r;
  case EXPR_SUBTRACT:
    return l - r;
  case EXPR_NEGATIVE:
    return -r;
  case EXPR_MULTIPLY:
    return l * r;
  case EXPR_DIVIDE:
    if (r == 0) {
      printf("runtime error: divide by zero\n");
      exit(1);
    }
    return l / r;
  case EXPR_POWER:
    return pow(l, r);
  case EXPR_SQRT:
    return sqrt(l);
  case EXPR_COUNT:
    return 10;
  case EXPR_EQUAL_EQUAL:
    return l == r;
  case EXPR_NOT_EQUAL:
    return l != r;
  case EXPR_GREATER_THAN:
    return l > r;
  case EXPR_GREATER_THAN_OR_EQUAL:
    return l >= r;
  case EXPR_LESS_THAN:
    return l < r;
  case EXPR_LESS_THAN_OR_EQUAL:
    return l <= r;
  case EXPR_AND:
    return l && r;
  case EXPR_OR:
    return l || r;
  case EXPR_NOT:
    return !l;
  case EXPR_INTEGER_LITERAL:
    return e->integer_value;
  case EXPR_FLOAT_LITERAL:
    return e->float_value;
  case EXPR_STRING_LITERAL:
    printf("runtime error: string in expression\n");
    exit(1);
  }

  return 0;
}

void close_parser() { destroySymbolMap(symbol_table); }
