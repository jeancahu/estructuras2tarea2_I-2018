/*
 * Ejercicio 2: Cálculo de la distancia más corta
 * 
 * Se hace uso de la función newComb para la generación de todas las posibles permutaciones entre los elementos del vector que contiene todas las ciudades menos la origen.
 * 
 * Las ciudades se representan como sigue: San José: 0, Limón: 1, San Franciso: 2, Alajuela: 3, Liberia: 4, Paraíso: 5, Puntarenas: 6, San Isidro: 7 
 * 
 *  
 */ 
#include <stdio.h>
#include <mpi.h>


#define NUM_CITIES 8   
#define TOT_COMBINATIONS 5040 //7!
#define COMB_SIZE 8
 
 
 //Swap entre dos elementos del array para generar combinaciones
void swap (int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


//Una vez alcanzada una nueva combinación, concatena los elementos del array a[] para generar un nuevo elemento 
//que agrega al vector de todas las combinaciones vectorComb, del cual recibe el puntero. 
//El parámetro tot determina la posición de vectorComb en la que escribirá, y n el tamaño del array a

void fillArray(int a[],int n, int* vectorComb, int* tot)
{
    int comb=0;
    for (int i=0; i<n; i++)
    {
        comb = 10*comb + a[i];
    }
    vectorComb[*tot]=comb;
    *tot = *tot + 1;
}


//Generación de combinaciones
//Recibe el tamaño del número a generar, un array con los elementos a permutar, el puntero al vectorComb que contendrá
//los resultados, y el valor tot que indicará a la función fillArray en qué posición del arreglo escribir

void newComb(int size, int posComb[], int* vectorComb, int* tot)
{
    if (size == 1)
    {
        fillArray(posComb,COMB_SIZE, vectorComb, tot);
        return;
    }
 
    for (int i=0; i<size; i++)
    {
        newComb(size-1, posComb, vectorComb, tot); //Llamado recursivo hasta llegar a condicion límite
        if (size%2==1)
            swap(&posComb[0], &posComb[size-1]);
        else
            swap(&posComb[i], &posComb[size-1]);
    }
}
 
int main(int argc, char** argv) 
{
    int rank, size;
    int counterTotal=0;
    int counterPrimProc;
    int vectorComb[TOT_COMBINATIONS];
    int tot=0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    
    int localMin=10000;
    int totalMin=10000;
    
    //Matriz de adyacencia
    int AdjMatrix[NUM_CITIES][NUM_CITIES]  = { 
                 {0,115,8,17,167,26,83,75},
                 {115,0,120,129,272,92,197,100},
                 {8,120,0,9,160,34,78,83},
                 {17,129,9,0,151,43,69,91},
                 {167,272,160,151,0,193,98,236},
                 {26,92,34,43,193,0,108,55},
                 {83,197,78,69,98,108,0,141},
                 {75,100,83,91,236,55,141,0}};
    
    //Todas las ciudades sin contar el origen
    int posComb[] = {1, 2, 3, 4, 5, 6, 7};
    int tam = NUM_CITIES -1;
    
    //Generamos todas las posibles rutas
    newComb(tam, posComb, vectorComb, &tot); 
    
    if( rank == 0)
    {
        
        int stCity, endCity;
        int contInt = 0;
        int tempSum = 0;
        int tempValue;
        int shortestPath;

        while(contInt < TOT_COMBINATIONS)
        {
            tempValue=vectorComb[contInt];
            for(int i = 0; i < COMB_SIZE; i++)
            {
                stCity = vectorComb[contInt] % 10;
                endCity = (vectorComb[contInt] /10) % 10;
                vectorComb[contInt] = vectorComb[contInt] / 10;
                tempSum=tempSum+AdjMatrix[stCity][endCity];
            }
            contInt += size;
            
            if(tempSum< localMin)
            {
                localMin = tempSum;
                shortestPath = tempValue;
            }
            tempSum=0;
        }
        printf("Camino mas corto encontrado por %d: %d, con una distancia de %d\n" , rank,shortestPath, localMin);
        MPI_Reduce(&localMin,&totalMin, 1,MPI_INT,MPI_MIN, 0, MPI_COMM_WORLD);
        printf("San José: 0, Limón: 1, San Franciso: 2, Alajuela: 3, Liberia: 4, Paraíso: 5, Puntarenas: 6, San Isidro: 7 \n");
        printf("Total min: %d", totalMin);
    }
    else
    {
        int stCity, endCity;
        int contInt = rank;
        int tempSum = 0;
        int tempValue;
        int shortestPath;
        while(contInt < TOT_COMBINATIONS)
        {
            tempValue=vectorComb[contInt];
            for(int i = 0; i < COMB_SIZE; i++)
            {
                stCity = vectorComb[contInt] % 10;
                endCity = (vectorComb[contInt] /10) % 10;
                vectorComb[contInt] = vectorComb[contInt] / 10;
                tempSum=tempSum+AdjMatrix[stCity][endCity];
            }
            contInt += size;
            if(tempSum< localMin)
            {
                localMin = tempSum;
                shortestPath = tempValue;
            }
            tempSum=0;
        } 
        printf("Camino mas corto encontrado por %d: %d, con una distancia de %d\n" , rank,shortestPath, localMin);
        MPI_Reduce(&localMin,&totalMin, 1,MPI_INT,MPI_MIN, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
    
} 


