//
//  VandMoment.c
//  Projet_3E103
//
//  Created by ilyas Aroui on 09/12/2017.
//  Copyright © 2017 Team_Projet. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N=10

double** creerVM(int N)
{
    double** result;
    int j;
    result= malloc( (N+1) * sizeof(double*) );
    for( j = N+1; j >0; j-- )
        result[N+1-j] = calloc(j, sizeof(double));

    return result;
}

//free la Matrix
void freeVM(double** a) {

    int j;
    // Liberation
    for( j = 0; j <= N; j++ )
        free( a[j] );
    free( a );
}

// a est une matrix VM
double** creerMCentree(double** a,BmpImg bmpImg,double ohm,double** VdmX, double** VdmY)
{
    int p,q;
    for(p=0;p<N+1;p++)
        for(q=0;q<N+1-p;q++)
    {
        a[p][q]= Mcentre(bmpImg,p,q,ohm,VdmX,VdmY);
    }
    return a;
}


// a est une matrix VM
double** creerCpq(double** a)
{
    int p,q;
     for(p=0;p<N+1;p++)
        for(q=0;q<N+1-p;q++)
    {
        a[p][q]= Cpq(int p,int q);
    }
    return a
}


double lambda(int p, int q, double Cpq, double** coeff, double** Mcentree)
{
    int i,j;
    double result=0;
    for(i=0;i<p;i++)
        for(j=0;j<q;j++)
        result+= coeff[p][i]*coeff[q][j]*Mcentree[i][j];

    return Cpq*result;
}


// a est une matrix VM
double** creerLambda(double** a,double** Cpq,double** coeff,double** Mcentre)
{
    int p,q;
    for(p=0;p<N+1;p++)
        for(q=0;q<N+1-p;q++)
    {
        a[p][q]= lambda(p,q,Cpq[p][q],coeff,Mcentree);
    }
    return a;
}
