#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define DIMX 10
#define DIMY 10
#define p 5
#define q 5
#define P 50
#define Q 50


int main ()
{
    int i;
    int j;
    double**  wanderx;
    ** wanderx = malloc( DIMX * sizeof(double* ) );
    for( i = 0; i < DIMX; i++ )
    {
        wanderx[i] = calloc( P, sizeof(double) );

    }

    for (j=0; j< DIMX; j++){
        for(i=0; i< P; i++ ){
            wanderx[i][j]=pow(j+1,i);
        }


    }


}

