#include <stdio.h>
#include "mpi.h"

int main(int argc, char ** argv)
{
    int rank, size, token, max;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    token = -1;
    max = 7;
    if( size > 2)
    {
        printf("Debe ser entre 2 proces.");
    }
    else
    {
        while(token < max-1)
        {
            if(rank == 0)
            {
                token++;
                MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
                printf(" Nodo %d envía a nodo %d el valor %d. ", rank, 1,token);
                MPI_Recv(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
                printf(" Nodo %d recibe de nodo %d el valor %d.\n", rank, size-1,token);

            }
            else{
                MPI_Recv(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
                //printf(" Nodo %d recibe de nodo %d el valor %d.\n", rank, rank-1,token);
                if(token<max)
                {
                    token++;
                    MPI_Send(&token, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
                    //printf(" Nodo %d envía a nodo %d el valor %d. ", rank, rank|1,token);
                }    
            }
        }
    }

    MPI_Finalize();
    return 0;


}



