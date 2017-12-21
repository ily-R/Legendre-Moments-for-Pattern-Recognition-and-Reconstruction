#include "Reconnaissance_Formes.h"

// 1.A
//free la Matrix
void freeVM(int ordre, double** VM) //DEBUGGED
{
    // Liberation
    if( VM != NULL ){
        int i;
        for( i = 0; i <= ordre; i++ )
            free( VM[i] );
        free( VM );
    }
    VM = NULL;
    printf("Matrice detruite.\n");
}


//Création de la matrice Vandermonde pour les puissances d
double** VMpuissance(int dim, int puissance, double xmoy)//DEBUGGED
{

    int j;
    int x;
    double** VM;

    VM = malloc(dim * sizeof(double*));

    for( j = 0 ; j < dim ; j++){
      VM[j] = calloc(puissance+1,sizeof(double));
    }

    if(VM == NULL){printf("Erreur allocation");}

    for( x = 0 ; x < dim ; x++ ){
        for( j = 0 ; j <= puissance ; j++){
            VM[x][j] = pow((x-xmoy),j);
        }
    }
  return VM;
}


//Moments Géométriques
double Mgeo(BmpImg bmpImg, int p, int q)//DEBUGGED
{
    unsigned char** image = bmpImg.img;
    unsigned int dimX, dimY; int x, y;
    double moment=0.0;

    dimX = bmpImg.dimX;
    dimY = bmpImg.dimY;

    double ** VdmX = VMpuissance(dimX, p, 0); //pas centré donc xb = 0
    double ** VdmY = VMpuissance(dimY, q, 0); //pas centré donc yb = 0

    for (x = 0; x < dimX; x++){
        for (y = 0; y < dimY; y++){
            if (image[x][y] != 0) //pour tout charactère différent de zéro, il faut le transformer en 1
                moment += VdmX[x][p]*VdmY[y][q]; //image[x][y]=1
        }
    }
    return moment;
}


//1.B

//Moments Centrés et normés
double Mcentre(BmpImg bmpImg, int p, int q, int beta)//DEBUGGED
{

    unsigned int dimX, dimY;
    int x, y;
    unsigned char** image = bmpImg.img;
    double somme=0.0;
    dimX = bmpImg.dimX;
    dimY = bmpImg.dimY;

    double ohm = Mgeo(bmpImg, 0, 0);
    double xb = Mgeo(bmpImg, 1, 0)/ohm;
    double yb = Mgeo(bmpImg, 0, 1)/ohm;

    double ** VdmX = VMpuissance(dimX, p, xb);
    double ** VdmY = VMpuissance(dimY, q, yb);

    for(x=0; x<dimX; x++){
        for(y=0; y<dimY; y++){

            if(image[x][y]!=0)
                somme += (VdmX[x][p]*VdmY[y][q])/pow(beta*ohm,((double)(p+q+2.))/2.);//image[x][y]=1

        }
    }
    return somme;
}

// Creer matrice Vandermonde de moments centre

double** MatMCentree(BmpImg bmpImg, int ordre, int beta)//DEBUGGED
{
    double** VM;
    int j;
    VM= malloc( (ordre+1) * sizeof(double*) );
    for( j = ordre+1; j >0; j-- )
        VM[ordre+1-j] = calloc(j, sizeof(double));

    int p,q;
    for(p=0; p <= ordre; p++){
        for(q=0; q <= ordre-p; q++){

            VM[p][q]= Mcentre(bmpImg, p, q, beta);
        }
    }
    return VM;
}

//1.C

//Calcul de Cpq

double Cpq(int p, int q)//DEBUGGED
{
    double result=(2*p+1)*(2*q+1)/4.;
    return result ;
}


double** MatCpq(int ordre)//DEBUGGED
{
    double** VM;
    int j;
    VM = malloc( (ordre+1) * sizeof(double*) );
    for( j = ordre+1; j >0; j-- )
        VM[ordre+1-j] = calloc(j, sizeof(double));

    int p,q;
    for(p=0; p <= ordre; p++){
        for(q=0; q <= ordre-p; q++){

            VM[p][q]= Cpq(p, q);
        }
    }
    return VM;
}

//Moments de Legendre

//Matrice triangulaire des coefficients de Legendre
//Renvoie la matrice triangulaire, en fonction de l'ordre NLeg défini au début du main

double** MatCoeffLeg (int ordre) //DEBUGGED
{

    //N = taille de la matrice
    int i, j;
    float n = 1.0; //parcours des coeff

    // Declaration
    double ** coeff; //matrice triangulaire coeff Legendre

    // Allocation dynamique
    coeff = malloc( (ordre+1) * sizeof(double*) ); // de la colonne for( int i = 0; i < N; i++ )
    for(j = 0; j <= ordre; j++ )
        coeff[j] = calloc( j+1, sizeof(double) ); // Tableau 1D de  → i+1 elements

    //Conditions initiales

    coeff[0][0] = 1.0; coeff[1][0] = 0.0; coeff[1][1]= 1.0;

    for(j = 2; j<= ordre; j++){ //Entre la 2e ligne et la Nème ligne

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
     //Affichage: attention aux tailles des tableaux
//    for( j = 0; j <= ordre; j++ ) {
//        printf( "N = %d : ", j);
//        for( i = 0; i <= j; i++ )
//            printf( "%lf  ", coeff[j][i] ); printf( "\n" );
//    }

    return coeff;
}

//Construction des polynômes de Legendre

double polyLeg(float x, int n, double** coeff)//DEBUGGED
{
    int i; double sum = 0;
    for(i=0; i<=n; i++)
        sum += coeff[n][i]*pow(x, i);

    return sum;
}
//Moments de Legendre

double Mlegendre(int p, int q, double Cpq, double** coeff, double** Mcentre)//DEBUGGED
{
    int i,j;
    double result=0.0;
    for(i=0;i<=p;i++){
        for(j=0;j<=q;j++){
            result+= coeff[p][i]*coeff[q][j]*Mcentre[i][j];
        }
    }
    return Cpq*result;
}


double** MatMlegendre(int ordre, double** Cpq, double** coeff, double** Mcentre)//DEBUGGED
{
    double** VM;
    int j;
    VM= malloc((ordre+1) * sizeof(double*) );
    for( j = ordre+1; j >0; j-- )
        VM[ordre+1-j] = calloc(j, sizeof(double));

    int p,q;
    for(p=0;p<=ordre;p++){
        for(q=0;q<=ordre-p;q++){

            VM[p][q]= Mlegendre(p,q,Cpq[p][q],coeff,Mcentre);
        }
    }
    return VM;
}




//1.D
//Reconstruction de l'image à partir des moments de Legendre

double pixelReconstruit(int ordre, float x, float y, double** Mlegendre, double** coeff)
{
    int p, q;
    double pixel = 0.0;

    for (p=0; p <= ordre; p++){
        for (q = 0; q <=p; q++){

            pixel += (Mlegendre[p-q][q])*polyLeg(x,p-q,coeff)*polyLeg(y,q,coeff);
        }
    }
    return pixel;
}


double** imageReconstruite(int ordre, BmpImg bmpImg, double** Mlegendre, double** coeff)
{
    int i,x,y;
    float dimX=bmpImg.dimX;
    float dimY=bmpImg.dimY;

    double** image;
    image= malloc(dimX*sizeof(double*));

    for(i=0;i<dimX;i++)
        image[i]=calloc(dimY, sizeof(double));


    for(x=0;x<dimX;x++){
        for(y=0;y<dimY;y++){

            image[x][y] = pixelReconstruit(ordre,2*x/dimX -1, 2*y/dimY -1, Mlegendre, coeff);
        }
    }
    return image;
}


double distanceEuclidienne(int ordre, double** Mlegendre1, double** Mlegendre2)//DEBUGGED
{
    int p,q;
    double somme = 0.0;

    for(p=0;p<=ordre;p++){
        for(q=0;q <= ordre-p;q++){

            somme += (Mlegendre1[p][q] - Mlegendre2[p][q]) * (Mlegendre1[p][q] - Mlegendre2[p][q]);
        }
    }
    
    return sqrt(somme);
}

double** lireMlegendre(char* Filename,int ordre)//DEBUGGED
{

    double** VM;
    int j,i;
    VM= malloc((ordre+1) * sizeof(double*) );
    for( j = ordre+1; j >0; j-- )
        VM[ordre+1-j] = calloc(j, sizeof(double));

    FILE *fTxt= fopen(Filename,"r");
    if(fTxt!= NULL)
     {
//       while(fscanf(fTxt,"%lf ",&t,&v)==1) // we read 2elements
      for(i=0;i<=ordre;i++)
        {
        for(j=0;j<=ordre-i;j++)
        {
           fscanf(fTxt,"%lf ",&VM[i][j]); //printf("%lf ",VM[i][j]);
        }
         fscanf(fTxt,"\n"); //printf("\n");
        }
     }

     fclose(fTxt);
     return VM;
}

void ecrireMlegendre(char* imageName,char* Filename,int ordre,int beta)
{
    int i,j;
    BmpImg bmpImg = readBmpImage(imageName);

    double** Mcentree= MatMCentree(bmpImg,ordre,beta);

    double** Cpq= MatCpq(ordre);

    double** coeff=  MatCoeffLeg(ordre);

    double** MatLegendre= MatMlegendre(ordre,Cpq,coeff,Mcentree);


    FILE *fTxt= fopen(Filename,"w");
    if(fTxt!= NULL)
     {
//       while(fscanf(fTxt,"%lf ",&t,&v)==1) // we read 2elements
      for(i=0;i<=ordre;i++)
        {
        for(j=0;j<=ordre-i;j++)
        {
           fprintf(fTxt,"%lf ",MatLegendre[i][j]);
        }
         fprintf(fTxt,"\n");
        }
     }

     fclose(fTxt);

    freeVM(ordre,Mcentree);
    freeVM(ordre,Cpq);
    freeVM(ordre,coeff);
    freeVM(ordre,MatLegendre);
    freeBmpImg(&bmpImg);
}

void comparaisonImages(char* imageName,int ordre,double***a,int beta,int s)
{
    int i,j,flag=0;
    double temp;
    BmpImg bmpImg = readBmpImage(imageName);

    double** Mcentree= MatMCentree(bmpImg,ordre,beta);

    double** Cpq= MatCpq(ordre);

    double** coeff=  MatCoeffLeg(ordre);

    double** MatLegendre= MatMlegendre(ordre,Cpq,coeff,Mcentree);

    double min =  distanceEuclidienne(ordre,MatLegendre, a[0]);

    for(i=1;i<s;i++)
        
    {
        temp = distanceEuclidienne(ordre,MatLegendre, a[i]);
    
        if(temp<min)
        {
            
           min=temp;
           flag=i;
        }

    }
    printf("\n%d\n",flag);


}
