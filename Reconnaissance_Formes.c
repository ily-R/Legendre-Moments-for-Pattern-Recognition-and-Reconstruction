#include "Reconnaissance_Formes.h"

// 1.A
//free la Matrix
void freeVM(int N, double** VM)
{
    int j;
    // Liberation
    for( j = 0; j <= N; j++ )
        free( VM[j] );
    free( VM );
}


//Création de la matrice Vandermonde pour les puissances d

double** Vandermonde(int dim, int ordre, double xmoy){

    int j;
    int x;
    double** Vdm;

    Vdm = malloc(dim * sizeof(double*));
    
    for( j = 0 ; j < dim ; j++){
      Vdm[j] = calloc(ordre+1,sizeof(double));
    }

    if(Vdm == NULL){printf("Erreur allocation");}

    for( x = 0 ; x < dim ; x++ ){
        for( j = 0 ; j <= ordre ; j++){
            Vdm[x][j] = pow((x-xmoy),j);
        }
    }
  return Vdm;
}


//Moments Géométriques
double Mgeo(BmpImg bmpImg, int p, int q)
{
    unsigned char** image = bmpImg.img;
    int dimX, dimY; int x, y;
    double moment=0.0;

    dimX = bmpImg.dimX;
    dimY = bmpImg.dimY;

    double ** VdmX = Vandermonde(dimX, p, 0); //pas centré donc xb = 0
    double ** VdmY = Vandermonde(dimY, q, 0); //pas centré donc yb = 0

    for (x = 0; x < dimX; x++){
        for (y = 0; y < dimY; y++){
            
            if (image[x][y] != 0) //pour tout charactère différent de zéro, il faut le transformer en 1
                moment += VdmX[x][p]*VdmY[y][q]; //no need to multiply by image[x][y] as it's a 1
        }
    }
    return moment;
}


//1.B

//Moments Centrés et normés
double Mcentre(BmpImg bmpImg, int p, int q){

    int dimX, dimY;

    unsigned char** image = bmpImg.img;
    double somme=0.0;
    int x, y;
    dimX = bmpImg.dimX;
    dimY = bmpImg.dimY;

    double ohm = Mgeo(bmpImg, 0, 0);
    double xb = Mgeo(bmpImg, 1, 0)/ohm;
    double yb = Mgeo(bmpImg, 0, 1)/ohm;

    double ** VdmX = Vandermonde(dimX, p, xb);
    double ** VdmY = Vandermonde(dimY, q, yb);

    for(x=0; x<dimX; x++){
        for(y=0; y<dimY; y++){
            
            if(image[x][y]!=0)
                somme += VdmX[x][p]*VdmY[y][q];//no need to multiply by image[x][y] as it's a 1

        }
    }
    return somme/(float)(pow(ohm,(float)(p+q+2)/2));
}

// Creer matrice Vandermonde de moments centre

double** creerMCentree(BmpImg bmpImg, int N)
{
    double** VM;
    int j;
    VM= malloc( (N+1) * sizeof(double*) );
    for( j = N+1; j >0; j-- )
        VM[N+1-j] = calloc(j, sizeof(double));

    int p,q;
    for(p=0;p<=N;p++){
        for(q=0;q<=N-p;q++){
    
            VM[p][q]= Mcentre(bmpImg,p,q);
        }
    }
    return VM;
}

//1.C

//Calcul de Cpq

double Cpq(int p, int q)
{
    double result=(2*p+1)*(2*q+1)/4;
    return result ;
}


double** creerCpq(int N)
{
    double** VM;
    int j;
    VM= malloc( (N+1) * sizeof(double*) );
    for( j = N+1; j >0; j-- )
        VM[N+1-j] = calloc(j, sizeof(double));

    int p,q;
    for(p=0;p<=N;p++){
        for(q=0;q<=N-p;q++){
            
            VM[p][q]= Cpq(p, q);
        }
    }
    return VM;
}

//Moments de Legendre

//Matrice triangulaire des coefficients de Legendre
//Renvoie la matrice triangulaire, en fonction de l'ordre NLeg défini au début du main

double** coeffLeg (int Nleg) {

    //N = taille de la matrice
    int i, j;
    float n = 1.0; //parcours des coeff

    // Declaration
    double ** coeff; //matrice triangulaire coeff Legendre

    // Allocation dynamique
    coeff = malloc( (Nleg+1) * sizeof(double*) ); // de la colonne for( int i = 0; i < N; i++ )
    for( int j = 0; j <= Nleg; j++ )
        coeff[j] = calloc( j+1, sizeof(double) ); // Tableau 1D de  → i+1 elements

    //Conditions initiales

    coeff[0][0] = 1.0; coeff[1][0] = 0.0; coeff[1][1]= 1.0;

    for(j = 2; j<= Nleg; j++){ //Entre la 2e ligne et la Nème ligne

        for(i=0; i<= n+1; i++){ //Parcours de a entre 0 et n+1

            if (i == 0){  //Condition sur la première colonne
                coeff[j][i] = (-n/(n+1))*coeff[(int)n-1][0];
                //printf("n = %f; coeff[%d][%d] : %lf \n", n, j, i, coeff[j][i]);
            }

            else if (i == n+1) //Condition sur la dernière diagonale
                coeff[j][i] = ((2*n+1)/(n+1))*coeff[(int)n][(int)n];

            else if (i == n) //Condition sur l'avant dernière diagonale
                coeff[j][i] = 0;

            else //Autres
                coeff[j][i] = ((2*n+1)/(n+1))*coeff[(int)n][i-1] - (n/(n+1))*coeff[(int)n-1][i];
        }
        n++; //Incrémentation de n
    }
    /*/ Affichage: attention aux tailles des tableaux
    for( j = 0; j <= NLeg; j++ ) {
        printf( "N = %d : ", j);
        for( i = 0; i <= j; i++ )
            printf( "%lf  ", coeff[j][i] ); printf( "\n" );
    }*/

    return coeff;
}


//Moments de Legendre

double Mlegendre(int p, int q, double Cpq, double** coeff, double** Mcentre)
{
    int i,j;
    double result=0;
    for(i=0;i<p;i++){
        for(j=0;j<q;j++){
            result+= coeff[p][i]*coeff[q][j]*Mcentre[i][j];
        }
    }
    return Cpq*result;
}


double** creerMlegendre(int N, double** Cpq, double** coeff, double** Mcentre)
{
    double** VM;
    int j;
    VM= malloc( (N+1) * sizeof(double*) );
    for( j = N+1; j >0; j-- )
        VM[N+1-j] = calloc(j, sizeof(double));

    int p,q;
    for(p=0;p<N+1;p++){
        for(q=0;q<N+1-p;q++){
            
            VM[p][q]= Mlegendre(p,q,Cpq[p][q],coeff,Mcentre);
        }
    }
    return VM;
}

//Construction des polynômes de Legendre

double polyLeg(int x, int n, double** coeff)
{
    int i; double sum = 0;
    for(i=0; i<=n; i++)
        sum += coeff[n][i]*pow(x, i);
    
    return sum;
}


//1.D
//Reconstruction de l'image à partir des moments de Legendre

double ImageMomLeg(int N, int x, int y, double** Mlegendre, double** coeff)
{
    int p, q;
    double pixel = 0.0;
    
    for (p=0; p <= N; p++){
        for (q = 0; q <= N-p; q++){

            pixel += (Mlegendre[p][q])*polyLeg(x,N,coeff)*polyLeg(y,N,coeff);
        }
    }
    return pixel;
}


double** imageReconstruite(int N, BmpImg bmpimg, double** Mlegendre, double** coeff)
{
    int i,x,y;
    int dimX=bmpimg.dimX;
    int dimY=bmpimg.dimY;
    
    double** image;
    image= malloc(dimX*sizeof(double*));
    
    for(i=0;i<dimX;i++)
    
        image[i]=calloc(dimY, sizeof(double));
    
    
    for(x=0;x<dimX;x++){
        for(y=0;y<dimY;y++){
            
            image[x][y] = ImageMomLeg(N, x, y, Mlegendre, coeff);
        }
    }
    return image;
}


double distanceEuclidienne(int N, double** Mlegendre1, double** Mlegendre2)
{
    int p,q;
    double somme = 0.0;
    
    for(p=0;p<=N;p++){
        for(q=0;q <= N-p;q++){
    
            somme += (Mlegendre1[p][q] - Mlegendre2[p][q]) * (Mlegendre1[p][q] - Mlegendre2[p][q]);
        }
    }
    return sqrt(somme);
}
