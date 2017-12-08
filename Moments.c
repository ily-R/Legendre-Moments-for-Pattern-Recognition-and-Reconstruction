//
//  Moments.c
//  Projet_3E103
//
//  Created by Baldet Ryo on 07/12/2017.
//  Copyright © 2017 Team_Projet. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//Moments Géométriques
double momentgeo(BmpImg bmpImg, int p, int q){
    //pas encore testé //structure de l'image en entrée ainsi que les coeff p et q
    
    unsigned char** image = bmpImg.img;
    int dimX, dimY; int x, y;
    double moment=0.0;
    
    dimX = bmpImg.dimX;
    dimY = bmpImg.dimY;
    
    for (x = 0; x < dimX; x++)
    {
        for (y = 0; y < dimY; y++)
        {
            if (image[x][y] != 0) //pour tout charactère différent de zéro, il faut le transformer en 1                     
                moment += pow(x, p)*pow(y, q); //no need to multiply by image[x][y] as it's a 1         
        }
    }
    
    return moment;
}

//Moments Centrés et normés
double Mcentre(BmpImg bmpImg, int p, int q, double ohm, double** VdmX, double** VdmY){
    
    int dimX, dimY;

    unsigned char** image = bmpImg.img;
    double som=0.0;
    int x, y;
    dimX = bmpImg.dimX;
    dimY = bmpImg.dimY;
    
    // VandermondeX(dimX, p, xb);
    //VandermondeY(dimY, q, yb);
    
    for(x=0; x<dimX; x++)
    {
        for(y=0; y<dimY; y++)
        {
            if(image[x][y]!=0)
                som += VdmX[x][p]*VdmY[y][q]/(float)(pow(ohm,(float)(p+q+2)/2));//no need to multiply by image[x][y] as it's a 1     
            
        }
    }
    return som;
}

//Calcul de Cpq
float Cpq(int p,int q){
    return (2*p+1)*(2*q+1)/4; 
}


//Moments de Legendre
double lambda(BmpImg bmpImg, int p, int q, double xb, double yb, float**a){
    int i,j;
    double som, nabla;
    double lambda=0;
    float Cpq= Cpq(p,q);
    //float** x,y;
    //double Mc;
    //x=VandermondeX(dimX,p,xb);
    //y=VandermondeY(dimY,q,yb);
    
    
    for(i=0;i<=p;i++){
        for(j=0;j<=q;j++){
            //VandermondeX(dimX,i,xb);
            //VandermondeY(dimX,j,xb);
            nabla = Mcentre(bmpImg,i,j);
            som += (a[p][i])*(a[q][j])*nabla;
        }
    }
    lambda=Cpq*som;
    return lambda;
}

