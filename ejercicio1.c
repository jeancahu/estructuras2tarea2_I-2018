#include <mpi.h>
#include <stdio.h>

//------------------------------------- EJERCICIO 1    -----------------------
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


/*-----------------------------------------------------------------------
 * Create child processes, each of which has its own variables
 * From this point on, every process executes a separate copy
 * of this program. Each process has a different process ID,
 * ranging from 0 to num_procs minus 1, and COPIES of all
 * variables defined in the program. No variables are shared.
 
    
   
int main( int argc, char **argv)
{
    int rank, root_process, ierr, size;
    MPI_Status status;
    


    ierr = MPI_Init(&argc, &argv);
    
   
     // Find out MY process ID and how many processes were started
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &size);

    if( rank % 2 == 0) {
        printf("Hello! My ID is an even number. I am %d\n", rank, size);
    }
    else{
        printf("Hello! My ID is an odd number. I am %d\n", rank, size);
    }
    
    //Stop this process
    ierr = MPI_Finalize();
    return 0;
    
}

*/


/*-----------------------------------------------------------------------
 * Intercambio de datos y sincronización entre procesos
 * MPI_Send: enviar mensajes a otros procesos
 * MPI_Recv: recibir mensajes de otros procesos
 */

//Distribute portions of array1 to slaves

//for( an_id = 1; an_id < num_procs; an_id++){
//    start_row = an_id*num_rows
    
//}


//-------------------------------        EJERCICIO 2        ------------------------------------
/*
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) 
{ 
    const int STOP_VALUE = 5;
    int send_value = 0;

    // Inicializacion
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Check si hay dos proces
    if (size != 2) 
    {

        fprintf(stderr, "Not 2 processors", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    /*Proce 0 inicia movimiento
    if( rank == 0 )
    {
        MPI_Send(&send_value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("%d envía %d a %d. ", rank, send_value, rank^1  );
        send_value++;
    }
    
    
    while( send_value < STOP_VALUE )
    {
        MPI_Send(&send_value, 1, MPI_INT, rank^1 , 0, MPI_COMM_WORLD);
        printf("%d recibe %d de %d\n", rank, send_value, rank^1);
        MPI_Recv(&send_value, 1, MPI_INT, rank^1 , 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 
        printf("%d envía %d a %d. ", rank, send_value, rank^1);
        send_value++;
    }
    
    
    MPI_Finalize();
}


*/




































