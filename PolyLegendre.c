//
//  CoeffLegendre.c
//  Projet_3E103
//
//  Created by Baldet Ryo on 07/12/2017.
//  Copyright © 2017 Team_Projet. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NLeg 50

double** coeffLeg () {
    
    //N = taille de la matrice
    
    int i, j;
    float n = 1.0; //parcours des coeff
    
    // Declaration
    double ** a; //matrice triangulaire coeff Legendre
    
    // Allocation dynamique
    a = malloc( (NLeg+1) * sizeof(double*) ); // de la colonne for( int i = 0; i < N; i++ )
    for( int j = 0; j <= NLeg; j++ )
        a[j] = calloc( j+1, sizeof(double) ); // Tableau 1D de  → i+1 elements
    
    //Conditions initiales
    
    a[0][0] = 1.0; a[1][0] = 0.0; a[1][1]= 1.0;
    
    for(j = 2; j<= NLeg; j++){ //Entre la 2e ligne et la Nème ligne
        
        for(i=0; i<= n+1; i++){ //Parcours de a entre 0 et n+1
            
            if (i == 0){  //Condition sur la première colonne
                a[j][i] = (-n/(n+1))*a[(int)n-1][0];
                //printf("n = %f; a[%d][%d] : %lf \n", n, j, i, a[j][i]);
            }
            
            else if (i == n+1) //Condition sur la dernière diagonale
                a[j][i] = ((2*n+1)/(n+1))*a[(int)n][(int)n];
            
            else if (i == n) //Condition sur l'avant dernière diagonale
                a[j][i] = 0;
            
            else //Autres
                a[j][i] = ((2*n+1)/(n+1))*a[(int)n][i-1] - (n/(n+1))*a[(int)n-1][i];
        }
        n++; //Incrémentation de n
    }
    
    
    // Affichage: attention aux tailles des tableaux
    for( j = 0; j <= NLeg; j++ ) {
        printf( "N = %d : ", j);
        for( i = 0; i <= j; i++ )
            printf( "%lf  ", a[j][i] ); printf( "\n" );
    }
    
    
    return a;
}

void freeLeg(double** a) {
    
    
    // Liberation
    for( int j = 0; j <= NLeg; j++ )
        free( a[j] ); // des lignes
    free( a ); // de la colonne
}

double polyLeg(int x, int n, double** a){
    
    int i; double sum = 0;
    for(i=0; i<=n; i++){
        sum += a[n][i]*pow(x, i);
    }
    return sum;
}


** double ImageMomLeg(int x, int y, double** a){
    
    int p, q;
    double sum = 0;
    for (p=0; p <= N; p++)
        for (q = 0; q <= N - p; q++)
            
            sum += lambda()*polyLeg(x)*polyLeg(y);

    
    return sum;
}

