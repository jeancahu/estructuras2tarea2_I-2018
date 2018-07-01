#include <stdio.h>
#include "mpi.h"

int main(int argc, char ** argv)
{
    int rank, size, token;
    
    
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    

    if(rank == 0)
    {
        printf(" Ejercicio 1.3: p0-p1-p2-p3-p0. \n");
        MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf(" Nodo %d envía a nodo %d el valor %d. \n", rank, next,token);
        MPI_Recv(&token, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, &status);
        printf(" Nodo %d recibe de nodo %d el valor %d.\n", rank, size-1,token);
    }
    else{
        MPI_Recv(&token, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        printf(" Nodo %d recibe de nodo %d el valor %d.\n", rank, rank-1,token);
        MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        printf(" Nodo %d envía a nodo %d el valor %d. \n", rank, next,token);

    }
    MPI_Finalize();
    return 0;


}
 
