#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

// Setting up number of rows + columns in the matrix
#define multiplier 20
#define columnsA 20
#define columnsB 10
#define rowsA 70

int main (int argc, char *argv[]) {
  double begin = omp_get_wtime();
  omp_set_num_threads(4);
  int threadID, numThreads;
  int chunkSize = 10;
  int i, j, k;

  // Matrix product + the result matrix
  double a[rowsA][columnsA], b[columnsA][columnsB], c[rowsA][columnsB];

  #pragma omp parallel shared(a, b, c, numThreads, chunkSize) private(threadID, i, j, k)
  {
    threadID = omp_get_thread_num();
    if (threadID == 0) /* master thread */
    {
      numThreads = omp_get_num_threads();
      printf("Matrix product using %d threads\n", numThreads);
    }

  #pragma omp for schedule (static, chunkSize)
  for (i = 0; i < rowsA; i++)
    for (j = 0; j < columnsA; j++)
      a[i][j] = i + j;
  #pragma omp for schedule (static, chunkSize)
  for (i = 0; i < columnsA; i++)
    for (j = 0; j < columnsB; j++)
      b[i][j] = i * j;
  #pragma omp for schedule (static, chunkSize)
  for (i = 0; i < rowsA; i++)
    for (j = 0; j < columnsB; j++)
      c[i][j] = 0;

  #pragma omp for schedule (static, chunkSize)
  for (i = 0; i < rowsA; i++)
  {
    //printf("Thread = %d did row %d\n", threadID, i);
    for (j = 0; j < columnsB; j++)
      for (k = 0; k < columnsA; k++)
        c[i][j] += (a[i][k] * b[k][j]);

  }
  }
double end = omp_get_wtime();
  /* results */
printf("Final Matrix: \n");
for (i = 0; i < rowsA; i++)
{
  for (j = 0; j < columnsB; j++)
    printf("%5f  ", c[i][j]);
  printf("\n");
}

printf("fini. Alloraaaa!\n"); /* can take this out */
printf("Parallel Execution time = %f seconds.\n", (end-begin));
}
