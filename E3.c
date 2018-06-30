/*
 * Ejercicio 3: Generación de los primeros 500000 números primos
 * 
 * TOP_COUNT_VALUE: número de primos a encontrar
 * 
 * INTERVAL_SIZE: a cada proce se le asigna un intervalo sobre el cual debe buscar INTERVAL_SIZE veces. Este intervalo se asigna dependiendo del rank y el número de proces que participen, avanzando 2*size números dentro del rango para evitar que colisionen. El 2 sale de la omisión de números pares.
 *
 * 
 * Para la comunicación se utiliza MPI_Reduce, para que una vez que cada proce recorre su intervalo, notifique al master cuántos números primos encontró.
 * 
 * 
 * testValue determina el inicio del búsqueda de cada proce, siendo este ((rank+1)*2+1) para cada uno. Nuevamente, se determina de manera tal que cada proce inicie en números impares
 */
#include <stdio.h>
#include <mpi.h>

#define TOP_COUNT_VALUE 500000

#define INTERVAL_SIZE 920000

/*
 * Recibe un valor, retorna 1 si es primo, 0 si no.
 */
int prime(int testValue)
{
    int isPrime = 1;
    for(int i=3; (i*i)<=testValue;i+=2)
    {
        if(testValue%i==0)
        {
            isPrime = 0;
        }   
    }  
    return isPrime;
}  


/*
 * runInterval: Cada proce recorre su intervalo, realizando saltos de 2*size para no chocar con otros proces, saltándose los números pares 
 */
int runInterval(int startValue, int size)
{
    int counterInterval=0;
    int counterPrimProc=0;  
    int testValue=startValue;
    while (counterInterval<INTERVAL_SIZE)
    {
        if(prime(testValue)==1)
        {
            counterPrimProc++;
            //printf("%d\n", testValue);
        }
        counterInterval+=1;
        testValue+=2*size;    
    }
    return counterPrimProc;
}

/*
 * runFinalInterval (sólo para el master): Una vez recorrido el máximo intervalo de cada proce, si aún no se tienen la cantidad requerida de primos, el master recorre el intervalo final hasta alcanzarlo. Lo realiza únicamente un proce para evitar los retardos que conllevarían las múltiples comunicaciones.
 */
int runFinalInterval(int startValue, int size, int topCount)
{
    int counterPrimProc=0;
    int testValue=startValue;
    while (counterPrimProc<topCount)
    {
        if(prime(testValue)==1)
        {
            counterPrimProc++;
            //printf("%d\n", testValue);
        }
        testValue+=2;    
    }
    return counterPrimProc;
}

int main(int argc, char** argv) 
{
    //Inicialización
    MPI_Init(&argc, &argv);
    int rank, size;
    int counterTotal=0; //Total de primos encontrados
    int counterPrimProc;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //Valor de inicio. Se empieza desde el 3, por lo que el 2 lo imprime MASTER. Se inicia sólo en números impares
    int testValue=((rank+1)*2+1);
        
    //Master
    if( rank == 0)
    {    
        counterPrimProc= runInterval(testValue, size) + 1; //Porque incluye el 2
        //printf("2\n");
        MPI_Reduce(&counterPrimProc,&counterTotal, 1,MPI_INT,MPI_SUM, 0, MPI_COMM_WORLD);
         if(counterTotal<TOP_COUNT_VALUE) //Si no se alcanzó el valor requerido, master busca los que faltan
         {
             counterTotal = counterTotal + runFinalInterval(INTERVAL_SIZE*2*size-1, size, (TOP_COUNT_VALUE-counterTotal)); 
         }
        printf("Total de primos encontrados: %d \n", counterTotal);
    }
    else
    { 
        counterPrimProc = runInterval(testValue, size);
        MPI_Reduce(&counterPrimProc,&counterTotal, 1,MPI_INT,MPI_SUM, 0, MPI_COMM_WORLD);
    }
    
    //Finaliza la app
    MPI_Finalize();
    return 0;
    
} 


