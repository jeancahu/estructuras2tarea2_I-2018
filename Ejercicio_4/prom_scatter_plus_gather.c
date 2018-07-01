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
  y = y / (filas * 2);

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
  int tam = 0;
  int local_tam;

  // Elementos sobrantes
  // Se almacenan en el total del proceso root

  // Total del promedio por proceso
  int total = 0;
  int* total_buf;

  // Pointer to vector
  int* vector;

  // Root process
  if( rank == root ) {
    //Generación aleatoria de matriz
    printf("\nInserte numero de elementos: ");
    fflush(stdout);
    scanf("%d", &tam);

    if ( tam < size ) {
      printf("\nError: El valor es demasiado pequeño\n");
      printf("Valor mínimo permitido es %d\n", size);
      tam = 0;
    }
    else if ( tam > 200000 ) {
      printf("\nError: El valor es demasiado grande\n");
      printf("Valor máximo permitido es 200000\n");
      tam = 0;
    } else {
      // printf("\n%d\n", tam%size);
      total_buf = malloc( size * sizeof(int));
      vector = malloc( tam * sizeof(int));
      fillVector(tam, vector);

      printf("\nElementos del vector:\n\n");
      for (i = 0; i < tam; i++) {
	printf("%d\n", vector[i]);
      }

      // printf("\n%d\n", vector);
      // Operar elementos extras:
      for (i = 0; i < tam%size; i++){
	total = total + vector[i];
      }
      vector = &vector[(tam%size)];
      // tam = tam - (tam%size);
      // printf("\n%d\n", vector);
    }
  }

  MPI_Bcast( &tam, 1, MPI_INT, root, MPI_COMM_WORLD);

  if ( tam ) {
    if ( rank != root ) {
      vector = malloc( (tam/size) * sizeof(int));
    }
  } else {
    MPI_Finalize();
    return 0;
  }

  // printf("%d %d %d\n", total, tam, size);

  // Tamaños de los buffers locales
  local_tam = (tam/size);

  // Se divide el vector de datos para otorgar un segmento a cada
  // proceso hijo y un arreglo al proceso matriz
  MPI_Scatter(vector, local_tam, MPI_INT,
	      vector, local_tam, MPI_INT, root,
	      MPI_COMM_WORLD);

  for (i = 0; i < local_tam; i++) {
    // printf("%d %d\n", rank, vector[i]);
    total = total + vector[i];
  }

  if ( rank == root ) {
    // Se divide tomando en cuenta los elementos sobrantes
    total = total / ( local_tam + tam%size ) ;
  } else {
    // Se divide tomando en cuenta los elementos locales
    total = total / local_tam;
  }

  // printf("%d %d %d\n", total, tam, size);

  MPI_Gather( &total, 1, MPI_INT,
  	      total_buf, 1, MPI_INT, root,
  	      MPI_COMM_WORLD);

  if ( rank == root ) {
    total = 0;
    for (i = 0; i < size; i++) {
      // printf("TODO: %d\n", total_buf[i]);
      total = total + total_buf[i];  
    }
    total = total / size;

    printf("\nEl promedio es: %d\n\n", total);

  }
  MPI_Finalize();
  return 0;    
}
