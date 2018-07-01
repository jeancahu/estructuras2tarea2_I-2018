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
  
  // Total del promedio por proceso
  int total = 0;
  int* total_buf;
  total_buf = malloc( size * sizeof(int));
  // Pointer to vector
  int* vector;
    
  // Root process
  if( rank == root ) {
    //Generación aleatoria de matriz
    printf("Inserte numero de elementos: ");
    fflush(stdout);
    scanf("%d", &tam);

    vector = malloc( tam * sizeof(int));
    fillVector(tam, vector);

    printf("\n\nElementos del vector:\n\n");
    for (i = 0; i < tam; i++) {
      printf("%d\n", vector[i]);
    }
    printf("\n\n");
  } else {
    vector = malloc( (tam/size) * sizeof(int));
  }
  
  MPI_Bcast( &tam, 1, MPI_INT, root, MPI_COMM_WORLD);

  // printf("%d %d %d\n", total, tam, size);
  
  MPI_Scatter(vector, tam/size, MPI_INT,
	      vector, tam/size, MPI_INT, root,
	      MPI_COMM_WORLD);
  
  for (i = 0; i < tam/size; i++) {
    // printf("%d %d\n", rank, vector[i]);
    total = total + vector[i];
  }

  // printf("%d %d %d\n", total, tam, size);
  total = total / ( tam / size );

  printf("Total individual: %d\n", total);
  
  MPI_Gather( &total, 1, MPI_INT,
  	      total_buf, 1, MPI_INT, root,
  	      MPI_COMM_WORLD);

  if ( rank == root ) {
    printf("\n\n");
    total = 0;
    for (i = 0; i < size; i++) {
      //printf("%d\n", total_buf[i]);
      total = total + total_buf[i];  
    }

    printf("El promedio es: %d\n", total);
    
  }
  MPI_Finalize();

  return 0;    
}
