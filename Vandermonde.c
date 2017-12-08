#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

double** VandermondeY(int dim, int ordre, float xmoy){

  int j;
  int x;
  double** Vdm;

  
  Vdm = calloc(dim,sizeof(int));
    for( j = 0 ; j < ordre ; j++){
      VdmY[j] = calloc(ordre,sizeof(int));
    }
  
  for( x = 0 ; x < dim ; x++ ){
    for( j = 0 ; j < q ; j++){
      VdmY[x][j] = pow((x-xmoy),j);
    }
  }
  return Vdm;
  
}
void DetruireV(float** V, int dim){
  int i;
  
  for(i = 0; i < dim; i++)
    free(V[i]);
  free(V);
  V=NULL;
}
