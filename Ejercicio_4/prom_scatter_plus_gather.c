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

  int root = 0;
  int i, j, k, rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  // Cantidad de datos
  int tam;
  // Cantidad de datos en procesos hijos
  int local_tam;
  
  // Total del promedio por proceso
  int total = 0;
  
  // Pointer to vector
  int* vector;
  int* sub_vector;
    
  // Root process
  if( rank == root ) {
    //Generación aleatoria de matriz
    printf("Inserte numero de elementos: ");
    fflush(stdout);
    scanf("%d", &tam);

    vector = malloc(tam * sizeof(int));
    fillVector(tam, vector);
    
    for (i = 0; i < tam; i++) {
      printf("%d\n", vector[i]);
    }
  }

  sub_vector = malloc( (tam/size) * sizeof(int));
  MPI_Scatter( &tam, 1, MPI_INT, &local_tam, 1, MPI_INT, root, MPI_COMM_WORLD);
  MPI_Scatter(vector, tam/size, MPI_INT, sub_vector, tam/size, MPI_INT, root, MPI_COMM_WORLD);

  
  
  for (i = 0; i < local_tam/size; i++) {
    printf("%d %d\n", rank, sub_vector[i]);
    total = total + sub_vector[i];
  }

  total = total / local_tam;

  printf("%d\n", total);

  MPI_Finalize();

  return 0;    
}
