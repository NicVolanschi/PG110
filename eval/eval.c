#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

char *pos;

char lookahead() {
  while (*pos == ' ') pos++;
  return *pos;
}

char *token() {
  char c = lookahead();
  if (c == '(') {
    pos++; // consume '('
    return "(";
  }
  if (c == ')') {
    pos++; // consume '('
    return ")";
  }
  if (c == '\0')
    return NULL;
  char *pos0 = pos;
  while (*pos && *pos != ' ' && *pos != '(' && *pos != ')') pos++;
  return strndup(pos0, pos - pos0);
}

expr parse() {
  char *tok = token();
  if (tok == NULL) {
    printf("expression expected but EOS found\n");
    exit(1);
  }
  if (strcmp(tok, ")") == 0) {
    printf("expression expected but ')' found\n");
    exit(1);
  }
  if (strcmp(tok, "(") == 0) {
    // parse list
    struct cell *l = NULL;
    struct cell **pl = &l;
    while (lookahead() != ')') {
      expr e = parse();
      struct cell *c = (struct cell *) malloc(sizeof(struct cell));
      c->data = e;
      c->next = NULL;
      *pl = c;
      pl = &(*pl)->next;
    }
    pos++; // consume ')'
    expr e;
    e.t = LST;
    e.u.l = l;
    return e;
  }
  if ('0' <= *tok && *tok <= '9') {
    int i = atoi(tok);
    expr e;
    e.t = INT;
    e.u.i = i;
    return e;
  }
  expr e;
  e.t = STR;
  e.u.s = tok;
  return e;
}

void print(expr e) {
  struct cell *l;
  switch(e.t) {
  case INT:
    printf("%i", e.u.i);
    break;
  case STR:
    printf("'%s'", e.u.s);
    break;
  case LST:
    printf("(");
    l = e.u.l;
    while (l != NULL) {
      print(l->data);
      printf(" ");
      l = l->next;
    }
    printf(")");
    break;
  default:
    printf("unknown expr type %i\n", e.t);
    exit(1);
  }
}

int valid(expr e) {
  if (e.t == STR) return 0;
  if (e.t == INT) return 1;
  // list
  if (e.u.l == NULL) return 0;
  if (e.u.l->data.t != STR) return 0;
  char *op = e.u.l->data.u.s;
  if (strcmp(op, "+") && strcmp(op, "-") && strcmp(op, "*") && strcmp(op, "/"))
    return 0;
  struct cell *args = e.u.l->next;
  int n = 0;
  while (args != NULL) {
    if (args->data.t == STR) return 0;
    if (args->data.t == LST && !valid(args->data)) return 0;
    n++;
    args = args->next;
  }
  return (n >= 2);
}

int eval(expr e) {
  if (e.t == INT) return e.u.i;
  // list
  char *op = e.u.l->data.u.s;
  if (strcmp(op, "+") == 0) {
    int sum = 0;
    struct cell *args = e.u.l->next;
    while (args != NULL) {
      sum += eval(args->data);
      args = args->next;
    }
    return sum;
  } else if (strcmp(op, "*") == 0) {
    int prod = 1;
    struct cell *args = e.u.l->next;
    while (args != NULL) {
      prod *= eval(args->data);
      args = args->next;
    }
    return prod;
  } else if (strcmp(op, "-") == 0) {
    struct cell *args = e.u.l->next;
    int sum = eval(args->data);
    args = args->next;
    while (args != NULL) {
      sum -= eval(args->data);
      args = args->next;
    }
    return sum;
  } else if (strcmp(op, "/") == 0) {
    struct cell *args = e.u.l->next;
    int sum = eval(args->data);
    args = args->next;
    while (args != NULL) {
      int val = eval(args->data);
      if (val == 0) {
	printf("division by 0\n");
	exit(1);
      }
      sum /= val;
      args = args->next;
    }
    return sum;
  } else {
    printf("op %s NYI\n", op);
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: %s expr\n", argv[0]);
    return 1;
  }
  pos = argv[1];
  char *tok;
  /* do { */
  /*   tok = token(); */
  /*   printf("lexeme:%s\n", tok); */
  /* } while (tok != NULL); */
  expr e = parse();
  print(e);
  printf("\n");
  if (!valid(e)) {
    printf("invalid expression\n");
    return 1;
  } 
  printf("expr is valid\n");
  printf("value is %i\n", eval(e));
}
