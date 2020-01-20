/*  Produit de 2 matrices */
#include <stdio.h>
#include <stdlib.h>

/* declaration des fonctions secondaires */
int **lecture_matrice(unsigned int, unsigned int);
void affiche(int **, unsigned int, unsigned int);
int **produit(int **, int **, unsigned int, unsigned int, unsigned int, unsigned int);

int **lecture_matrice(unsigned int nb_lignes, unsigned int nb_col)
{
  int **M;
  int i, j;

  scanf("%d", &nb_lignes);
  scanf("%d", &nb_col);
  M = (int**)malloc(nb_lignes * sizeof(int*));
  for (i=0; i<nb_lignes; i++)
    M[i] = (int*)malloc(nb_col * sizeof(int));
  for (i=0; i<nb_lignes; i++)
    {
      for (j=0; j<nb_col; j++)
	scanf("%d",&M[i][j]);
    }
  return(M);
}

void affiche(int **M, unsigned int nb_lignes, unsigned int nb_col)
{
  int i, j;
  for (i=0; i < nb_lignes; i++)
    {
      for (j=0; j < nb_col; j++)
	printf("%2d\t",M[i][j]);
      printf("\n");
    }
  return;
}


int **produit(int **A, int **B, unsigned int nb_lignes1, unsigned int nb_col1, unsigned int nb_lignes2, unsigned int nb_col2)
{
  int **P;
  int i, j, k;

  if (nb_col1 != nb_lignes2)
    {
      printf("\n Impossible d'effectuer le produit : dimensions incompatibles\n");
      return(NULL);
    }
  P = (int**)malloc(nb_lignes1 * sizeof(int*));
  for (i=0; i<nb_lignes1; i++);
    P[i] = (int*)calloc(nb_col2, sizeof(int));
  /* calcul de P[i][j] */
  for (i=0; i < nb_lignes1; i++)
    {
      for (j=0; j < nb_col2; j++)
	{
	  for (k=0; k < nb_lignes2; k++)
	    P[i][j] += A[i][k] * B[k][j];
	}
    }
  return(P);
}


int main()
{
  int **A, **B, **P;
  unsigned int nb_lignesA, nb_lignesB, nb_colA, nb_colB;
  
  A = lecture_matrice(nb_lignesA, nb_colA);
  printf("\n Affichage de A:\n");
  affiche(A, nb_lignesA, nb_colA);
  B = lecture_matrice(nb_lignesB, nb_colB);
  printf("\n Affichage de B:\n");
  affiche(B, nb_lignesB, nb_colB);
  P = produit(A, B, nb_lignesA, nb_colA, nb_lignesB, nb_colB);
  printf("\n Affichage du produit de A par B:\n");
  affiche(P, nb_lignesA, nb_colB);
  return(EXIT_SUCCESS);
}

