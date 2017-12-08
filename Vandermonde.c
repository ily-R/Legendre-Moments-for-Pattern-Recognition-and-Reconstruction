#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


double** VandermondeX(int dimX, int p, float xb){

  int j;
  float x;
  double** VdmX;

  VdmX = calloc(dimX,sizeof(int));
    for( j = 0 ; j < p ; j++){
      VdmX[j] = calloc(p,sizeof(int));
    }
  
  for( x = 0 ; x < dimX ; x++ ){
    for( j = 0 ; j < p ; j++){
      VdmX[(int)x][j] = pow((x-xb),j);
    }
  }
  return VdmX;
}

double** VandermondeY(int dimY, int q, float yb){

  int j;
  float y;
  double** VdmY;

  
  VdmY = calloc(dimY,sizeof(int));
    for( j = 0 ; j < q ; j++){
      VdmY[j] = calloc(q,sizeof(int));
    }
  
  for( y = 0 ; y < dimY ; y++ ){
    for( j = 0 ; j < q ; j++){
      VdmY[(int)y][j] = pow((y-yb),j);
    }
  }
  return VdmY;
}




void DetruireV(float** V, int dim){
  int i;
  
  for(i = 0; i < dim; i++)
    free(V[i]);
  free(V);
  V=NULL;
}
