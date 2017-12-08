#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#define max1 4
#define max2 4



float distanceeuclidienne(int p, int q,float m1[max1][max1],float m2[max1][max1])
{

    int i,j;
    double distance=0,moment1=0,moment2=0;

    for (i=0; i<p; i++)
    {
        for (j=0; j<q; j++)
        {
            moment1=m1[i][j];
            moment2=m2[i][j];
            distance+=pow((moment1-moment2),2);
        }
    }
    return sqrt(distance);
}

/* fonction test
int main()
{
    int i,j;
    float t1[max1][max1],t2[max2][max2];
    float c;
    srand(time(NULL));



//======== Affichage de la matrice ========
    printf("- Matrice unite1 :\n");
    for(i=0; i < max1; i++)
    {
        for(j=0; j < max1; j++)
        {
            t1[i][j]=1;
            //t2[i][j]=1;
            //printf("%lf ",t1[i][j]);
            printf("%lf ",t1[i][j]);
        }
        printf("\n");
    }
    printf("- Matrice unite2 :\n");
    for(i=0; i < max2; i++)
    {
        for(j=0; j < max2; j++)
        {
            t2[i][j]=1;
            //t2[i][j]=1;
            //printf("%lf ",t1[i][j]);
            printf("%lf ",t2[i][j]);
        }
        printf("\n");
    }
    c = distanceeuclidienne(max1,max2,t1,t2);
    printf("\n%f",c);
    return 0;
}*/

