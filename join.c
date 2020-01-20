/* 
   Ecrire un programme (join.c) qui affiche les nombres lus sur
   l'entrée standard, séparés par virgule et finis par point.
   Exemples:
   ex/$ echo | ./join
   .
   ex/$ echo 11 | ./join
   11.
   ex/$ echo 11 22 33 | ./join
   11,22,33.
*/
#include <stdio.h>

int main(int argc, char *argv[]) {
  int x;
  int first = 1;
  while(scanf("%i", &x) == 1) {
    if(!first) {
      printf(",");
    } else {
      first = 0;
    }
    printf("%i", x);
  }
  printf(".\n");
}
