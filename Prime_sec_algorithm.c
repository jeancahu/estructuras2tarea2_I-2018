#include <stdio.h>

<<<<<<< HEAD
#define TOP_COUNT_VALUE 500000
=======
#define TOP_COUNT_VALUE=500000;
>>>>>>> 4bf28e0... add: Generador de primos secuencial

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

int main()
{
    int counter=1;//Ya tenemos a 2
    int testValue=3;
    while (counter<TOP_COUNT_VALUE)
    {
        if(prime(testValue)==1)
        {
            counter++;
            printf("%d\n",testValue);
        }
        testValue+=2;    
    }
}

  
