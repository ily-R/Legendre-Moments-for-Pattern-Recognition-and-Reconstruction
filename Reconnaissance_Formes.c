#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// 1.A

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
//Moments Géométriques
double momentgeo(BmpImg bmpImg, int p, int q)
{
    //pas encore testé //structure de l'image en entrée ainsi que les coeff p et q

    unsigned char** image = bmpImg.img;
    int dimX, dimY; int x, y;
    double moment=0.0;

    dimX = bmpImg.dimX;
    dimY = bmpImg.dimY;

    double ** VdmX = Vandermonde(dimX, p, 0); //pas centré donc xb = 0
    double ** VdmY = Vandermonde(dimY, q, 0); //pas centré donc yb = 0


    for (x = 0; x < dimX; x++)
    {
        for (y = 0; y < dimY; y++)
        {
            if (image[x][y] != 0) //pour tout charactère différent de zéro, il faut le transformer en 1
                moment += VdmX[x][p]*VdmY[y][q]; //no need to multiply by image[x][y] as it's a 1
        }
    }

    return moment;
}


//1.B

//Moments Centrés et normés
double Mcentre(BmpImg bmpImg, int p, int q, double ohm, double xb, double yb){

    int dimX, dimY;

    unsigned char** image = bmpImg.img;
    double som=0.0;
    int x, y;
    dimX = bmpImg.dimX;
    dimY = bmpImg.dimY;

    double ** VdmX = Vandermonde(dimX, p, xb);
    double ** VdmY = Vandermonde(dimY, q, yb);

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
// Creer matrice Vandermonde de moments centre
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

//Création de la matrice Vandermonde pour les puissances d

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

//1.C

//Calcul de Cpq
//Calcul de Cpq
float Cpq(int p,int q){
    return (2*p+1)*(2*q+1)/4;
}

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

//Moments de Legendre

//Matrice triangulaire des coefficients de Legendre
//Renvoie la matrice triangulaire, en fonction de l'ordre NLeg défini au début du main
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

//Moments de Legendre

double lambda(int p, int q, double Cpq, double** coeff, double** Mcentree)
{
    int i,j;
    double result=0;
    for(i=0;i<p;i++)
        for(j=0;j<q;j++)
        result+= coeff[p][i]*coeff[q][j]*Mcentree[i][j];

    return Cpq*result;
}

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

//Construction des polynômes de Legendre
double polyLeg(int x, int n, double** a){

    int i; double sum = 0;
    for(i=0; i<=n; i++){
        sum += a[n][i]*pow(x, i);
    }
    return sum;
}
//1.D

double* creerVectPolyLeg(int n)
{
    double* vect= malloc(n+1,sizeof(double));
    for(i=0;i<n+1;i++)
    {
        vect[i]=polyLeg(int x, int n, double** a);
    }
    return vect;
}

//Reconstruction de l'image à partir des moments de Legendre
double** ImageMomLeg(int x, int y, double** a)
{

    int p, q;
    double sum = 0;
    for (p=0; p <= N; p++)
        for (q = 0; q <= N - p; q++)

            sum += lambda()*polyLeg(x)*polyLeg(y);


    return sum;
}
