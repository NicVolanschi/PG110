#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fact(int n) {
  int p;
  if (n<=1) return (1);
  p = n * fact(n-1); // appel récursif                                          
  return p;
}

int main (int argc, char *argv[]) {
  char **p = malloc(sizeof(char *) * (argc - 1));
  memcpy(p, argv + 1, sizeof(char *) * argc - 1);
  int res = fact(atoi(p[2]));
  printf("%d\n", res);
}
