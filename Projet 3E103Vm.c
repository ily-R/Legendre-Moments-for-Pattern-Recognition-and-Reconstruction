#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

float momentgeo(BmpImg bmpImg, int p, int q){ //pas encore testé //structure de l'image en entrée ainsi que les coeff p et q

    unsigned char** image = bmpImg.img;
    int dimX, dimY;
    float moment;

    dimX = BmpImg.dimX;
    dimY = BmpImg.dimY;
    
    for (x = 0; x < dimX; x++)
        for (y = 0; y < dimY; y++)
            if (image[x][y] != 0) //pour tout charactère différent de zéro, il faut le transformer en 1
                image[x][y] = 1;
            moment += pow(x, p)*pow(y, q)*image[x][y]; //formule

    return moment;
}

void VandermondeX(int dimX, int p, float xb){

  int j;
  float x;
  float** VdmX;

  VdmX = calloc(dimX,sizeof(int));
    for( j = 0 ; j < p ; j++){
      VdmX[j] = calloc(p,sizeof(int));
    }
  
  for( x = 0 ; x < dimX ; x++ ){
    for( j = 0 ; j < p ; j++){
      VdmX[x][j] = pow((x-xb),p);
    }
  }
}}

void VandermondeY(int dimY, int q, float yb){

  int j;
  float y;
  float** VdmY;

  
  VdmY = calloc(dimY,sizeof(int));
    for( j = 0 ; j < q ; j++){
      VdmY[j] = calloc(q,sizeof(int));
    }
  
  for( y = 0 ; y < dimY ; y++ ){
    for( j = 0 ; j < q ; j++){
      VdmX[y][j] = pow((y-yb),q);
    }
  }
}


double Mcentre(BmpImg bmpImg){

    int dimX, dimY;
    float ohm = momentgeo(BmpImg, 0, 0);
    float xb = momentgeo(BmpImg, 1, 0)/ohm;
    float yb = momentgeo(BmpImg, 0, 1)/ohm;
    unsigned char** image = bmpImg.img;
    double som=0;
		 
    dimX = BmpImg.dimX;
    dimY = BmpImg.dimY;

    VandermondeX(dimX, p, xb);
    VandermondeY(dimY, q, yb);
    
    for(x=0; x<dimX; x++)
    {
        for(y=0; y<dimY; y++)
        {
            som += VdmX[x][y]*VdmY[x][y]/(float)(pow(ohm,(float)(p+q+2)/2))*image[x][y];
            printf("%fl\n",som);
        }

    }
return som;
}

//Pas Calcul avec Vdm pas fini
