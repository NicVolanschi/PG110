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
    // ... parse list
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

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: %s expr\n", argv[0]);
    return 1;
  }
  pos = argv[1];
  char *tok;
  do {
    tok = token();
    printf("lexeme:%s\n", tok);
  } while (tok != NULL);
  //expr e = parse();
}
