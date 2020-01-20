/*
  Ecrire un programme qui affiche le 1er et le dernier nombres pairs
  passés sur la ligne de commande, ou un message d'échec si aucun nombre
  paire ne s'y trouve.
  Exemples:
  ex/$ ./pairs 1
  no even number
  ex/$ ./pairs 1 2 3
  1st even = 2
  last even = 2
  ex/$ ./pairs 1 2 3 4 
  1st even = 2
  last even = 4
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int first = 1, last = 1;
  for(int i = 1; i < argc; i++) {
    int x = atoi(argv[i]);
    if(x % 2 == 0) {
      if (first == 1) {
	first = x;
      }
      last = x;
    }
  }
  if(last == 1) {
    printf("no even number\n");
  } else {
    printf("1st even = %d\n", first);
    printf("last even = %d\n", last);
  }
}
