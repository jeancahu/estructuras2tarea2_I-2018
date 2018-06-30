#define N 4
#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include<time.h>
void printMatrix(int filas, int columnas, int matriz[filas][columnas])
{
    int i, j;
    for (i = 0; i < filas; i++) 
    {
        for (j = 0; j < columnas; j++) 
        {
            printf(" %d", matriz[i][j]);
        }
        printf("\n");
    }
}

void fillMatrix(int filas, int columnas, int mat[filas][columnas])
{
    srand(time(NULL));
    int x, y;
    for(x = 0; x < filas; x++) 
    {
        for(y = 0; y < columnas; y++) 
            mat[x][y] = rand() % 10; 
    }
}


int main(int argc, char ** argv)
{
    
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int filas;
    int columnas;
    
    if ( rank == 0)
    {
        //Parametros de matriz
        filas=0;
        columnas=0;
        printf("Inserte numero de filas: ");
        fflush(stdout);
        scanf("%d", &filas);
        printf("Inserte número de columnas: ");
        fflush(stdout);
        scanf("%d", &columnas);
        
        
        MPI_Bcast(filas, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(columnas,1, MPI_INT, 0, MPI_COMM_WORLD);
    }    
    MPI_Barrier( MPI_COMM_WORLD );
    
    int vector[columnas][1];
    int matriz[filas][columnas];
    
    
    //Matriz
    if( rank == 0)
    {
        //Generación aleatoria de matriz
        fillMatrix(filas, columnas, matriz);
        //printf("Matriz: \n");
        //printMatrix(filas, columnas, matriz);
        
        //Generación del vector
        fillMatrix(columnas, 1, vector);
        printf("Vector: \n");
        printMatrix(columnas, 1, vector);
        
        //Vector resultante
        int Result[1][filas];
        
        //Enviamos matriz y vector a todos
        MPI_Bcast(matriz, filas*columnas, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(vector, columnas, MPI_INT, 0, MPI_COMM_WORLD);
        
        int contFilas=0;
        while(contFilas<filas)
        {
            //MPI_Send(matriz[contFilas], columnas, MPI_INT, contFilas, contFilas, MPI_COMM_WORLD);
        }
        
    }
    else
    {
        int i;
        //MPI_Recv(matriz[i], columnas, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        printMatrix(filas, columnas, matriz);
    }
        
        

    
    MPI_Finalize();
    return 0;    
   
}

