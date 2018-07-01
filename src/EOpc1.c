#include <mpi.h>
#include <stdio.h>

//------------------------------------- EJERCICIO OPCIONAL 1    -----------------------
int main ( int argc, char *argv[] )
{
    int rank, size;
    int token = 1;
    MPI_Status status;
    //iniciar aplicacion paralela
    MPI_Init(&argc, &argv);
    
    //ID del proceso dentro de la colección de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    //Numero de procesos que participan en la app
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if( rank == 0)
    {    
        printf("Hello. World! I am %d\n", rank, size);
        MPI_Send(&token, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else
    {   
        MPI_Recv(&token, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, &status);
        printf("Hello. World! I am %d\n", rank, size);
        if( rank < size-1)
        {
            MPI_Send(&token, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        }
    }
    
    //Finaliza la app
    MPI_Finalize();
    return 0;
    
} 





































