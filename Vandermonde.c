#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

double** Vandermonde(int dim, int ordre, double xmoy){

  int j;
  int x;
  double** Vdm;

  
  Vdm = malloc(dim * sizeof(double));
    for( j = 0 ; j < dim ; j++){
      Vdm[j] = calloc(ordre+1,sizeof(double));
    }

    if(Vdm == NULL){printf("Erreur allocation");}
  
  for( x = 0 ; x < dim ; x++ ){
    for( j = 0 ; j < ordre+1 ; j++){
      Vdm[x][j] = pow((x-xmoy),j);
    }
  }
  return Vdm;
}

void DetruireV(double** V, int dim){
  int i;
  
  for(i = 0; i < dim; i++)
    free(V[i]);
  free(V);
  V=NULL;
}

//Testing functions 
// Uncomment following function if you wish to test.

/*
void afficherVdm(double** V, int ordre, int dim){
  int i,j;
  
  printf("\n");
  for( i = 0 ; i < dim ; i++){
    for( j = 0 ; j < ordre+1 ; j++){
      printf(" %lf ",V[i][j]);
    }
    printf("\n");
  }
  printf("\n");
} 

int main(){
  int p = 2;
  double xb = 3.5;
  int dimx = 9;  
  double** vdmx;
  
  vdmx = Vandermonde(dimx,p,xb);
  
  int q = 4;
  double yb = 1.22;
  int dimy = 6;
  double** vdmy;
  
  vdmy = Vandermonde(dimy,q,yb);
  
  
  afficherVdm(vdmx,p,dimx);
  printf("\n");
  afficherVdm(vdmy,q,dimy);
  

  DetruireV(vdmx,dimx);
  //DetruireV(vdmy,dimy);

  return 0;
}
*/


///Marche Testé

