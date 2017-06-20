#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define multiplier 20
#define columnsA 20
#define columnsB 10
#define rowsA 70

int main(void)
{
  clock_t startTime = clock();
  int i, j, k;

  double a[rowsA][columnsA], b[columnsA][columnsB], c[rowsA][columnsB];

  for (i = 0; i < rowsA; i++)
    for (j = 0; j < columnsA; j++)
      a[i][j] = i + j;
  for (i = 0; i < columnsA; i++)
    for (j = 0; j < columnsB; j++)
      b[i][j] = i * j;
  for (i = 0; i < rowsA; i++)
    for (j = 0; j < columnsB; j++)
      c[i][j] = 0;

  for (i = 0; i < rowsA; i++)
  {
    for (j = 0; j < columnsB; j++)
      for (k = 0; k < columnsA; k++)
        c[i][j] += (a[i][k] * b[k][j]);
  }

  printf("Final Matrix: \n");
  for (i = 0; i < rowsA; i++)
  {
    for (j = 0; j < columnsB; j++)
      printf("%5f  ", c[i][j]);
    printf("\n");
  }

  clock_t endTime = clock();

  printf("fini. Allora! \n"); /* take this out */
  printf("Sequential Execution time = %f seconds. \n", (double)(endTime - startTime) / CLOCKS_PER_SEC);
}
