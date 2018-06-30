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
    
    int i, j, k, rank, size;//tag = 99, sum = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        
    
    //Matriz
    if( rank == 0)
    {
        //Generación aleatoria de matriz
        int filas=0, columnas=0;
        printf("Inserte numero de filas: ");
        fflush(stdout);
        scanf("%d", &filas);
        printf("Inserte número de columnas: ");
        fflush(stdout);
        scanf("%d", &columnas);
        int matriz[filas][columnas];
        fillMatrix(filas, columnas, matriz);
        printf("Matriz: \n");
        printMatrix(filas, columnas, matriz);
        
        //Generación del vector
        int vector[columnas][1];
        fillMatrix(columnas, 1, vector);
        printf("Vector: \n");
        printMatrix(columnas, 1, vector);
        
        //Vector resultante
        int Result[1][filas];
        
        //Receive buffer
        int recBuff[columnas];
        //Usamos Scatter para enviar filas de la matriz a cada proce
        MPI_Scatter(matriz, columnas, MPI_INT, recBuff, columnas, MPI_INT,0,MPI_COMM_WORLD);

    }

    MPI_Barrier(MPI_COMM_WORLD);  
    MPI_Finalize();
    return 0;    
   
}

