#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <time.h>

void fillVector(int filas, int *mat)
{
    srand(time(NULL));
    int x;
    unsigned int y = 0;
    y = y - 1;
    y = y / filas;

    for(x = 0; x < filas; x++) 
    {
      mat[x] = rand() % y;
    }
}


int main(int argc, char ** argv)
{
    
    int i, j, k, rank, size;//tag = 99, sum = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
    
    // Root process
    if( rank == 0) {
        //Generación aleatoria de matriz
      int tam;
      printf("Inserte numero de elementos: ");
      fflush(stdout);
      scanf("%d", &tam);

      int* vector = malloc(tam * sizeof(int));
      fillVector(tam, vector);

      for (i = 0; i < tam; i++) {
	printf("%d\n", vector[i]);
      }
    } else {
      printf("Hola\n");
    }

    MPI_Finalize();

    return 0;    
}

