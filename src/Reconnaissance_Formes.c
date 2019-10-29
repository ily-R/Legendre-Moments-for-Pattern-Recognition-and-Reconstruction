#include "Reconnaissance_Formes.h"



void freeVM(int ordre, double** VM)
{
    if( VM != NULL ){
        int i;
        for( i = 0; i <= ordre; i++ )
            free( VM[i] );
        free( VM );
    }
    VM = NULL;
    printf("\nMatrice detruite.");
}


double** VMpuissance(int dim, int puissance, double xmoy)
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


double Mgeo(BmpImg bmpImg, int p, int q)
{
    unsigned char** image = bmpImg.img;
    unsigned int dimX, dimY; int x, y;
    double moment=0.0;

    dimX = bmpImg.dimX;
    dimY = bmpImg.dimY;

    double ** VdmX = VMpuissance(dimX, p, 0);
    double ** VdmY = VMpuissance(dimY, q, 0);

    for (x = 0; x < dimX; x++){
        for (y = 0; y < dimY; y++){
            if (image[x][y] != 0)
                moment += VdmX[x][p]*VdmY[y][q];
        }
    }
    return moment;
}


double Mcentre(BmpImg bmpImg, int p, int q, int beta)
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
                somme += (VdmX[x][p]*VdmY[y][q])/pow(beta*ohm,((double)(p+q+2.))/2.);

        }
    }
    return somme;
}


double** MatMCentree(BmpImg bmpImg, int ordre, int beta)
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



double Cpq(int p, int q)
{
    double result=(2*p+1)*(2*q+1)/4.;
    return result ;
}


double** MatCpq(int ordre)
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



double** MatCoeffLeg (int ordre)
{

    //N = matrix size
    int i, j;
    float n = 1.0;

    // Declaration
    double ** coeff;

    // Dynamic allocation
    coeff = malloc( (ordre+1) * sizeof(double*) );
    for(j = 0; j <= ordre; j++ )
        coeff[j] = calloc( j+1, sizeof(double) );

    //Initial conditions

    coeff[0][0] = 1.0; coeff[1][0] = 0.0; coeff[1][1]= 1.0;

    for(j = 2; j<= ordre; j++){

        for(i=0; i<= n+1; i++){

            if (i == 0){
                coeff[j][i] = (-n/(n+1))*coeff[(int)n-1][0];
                //printf("n = %f; coeff[%d][%d] : %lf \n", n, j, i, coeff[j][i]);
            }

            else if (i == n+1)
                coeff[j][i] = ((2*n+1)/(n+1))*coeff[(int)n][(int)n];

            else if (i == n)
                coeff[j][i] = 0;

            else
                coeff[j][i] = ((2*n+1)/(n+1))*coeff[(int)n][i-1] - (n/(n+1))*coeff[(int)n-1][i];
        }
        n++;
    }
     //Affichage: attention aux tailles des tableaux
//    for( j = 0; j <= ordre; j++ ) {
//        printf( "N = %d : ", j);
//        for( i = 0; i <= j; i++ )
//            printf( "%lf  ", coeff[j][i] ); printf( "\n" );
//    }

    return coeff;
}


double polyLeg(float x, int n, double** coeff)
{
    int i; double sum = 0;
    for(i=0; i<=n; i++)
        sum += coeff[n][i]*pow(x, i);

    return sum;
}

double Mlegendre(int p, int q, double Cpq, double** coeff, double** Mcentre)
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


double** MatMlegendre(int ordre, double** Cpq, double** coeff, double** Mcentre)
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





double pixelReconstruit(int ordre, float x, float y, double** Mlegendre, double** coeff)
{
    int p, q;
    double pixel = 0.0;

    for (p=0; p <= ordre; p++){
        for (q = 0; q <=ordre-p; q++){

            pixel += (Mlegendre[p][q])*polyLeg(x,p,coeff)*polyLeg(y,q,coeff);
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


double distanceEuclidienne(int ordre, double** Mlegendre1, double** Mlegendre2)
{
    int p,q;
    double somme = 0.0;

    for(p=0; p <= ordre; p++){
        for(q=0; q <= ordre-p; q++){

            somme += (Mlegendre1[p][q] - Mlegendre2[p][q]) * (Mlegendre1[p][q] - Mlegendre2[p][q]);
        }
    }

    return sqrt(somme);
}


void ecrireMlegendre(char* imageName, char* Filename, int ordre, int beta) //DEBUGGED
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
        for(i=0; i <= ordre; i++){
            for(j=0; j <= ordre-i; j++){

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

double** lireMlegendre(char* Filename, int ordre)
{
    double** VM;
    int j,i;
    VM= malloc((ordre+1) * sizeof(double*) );
    for( j = ordre+1; j >0; j-- )
        VM[ordre+1-j] = calloc(j, sizeof(double));

    FILE *fTxt= fopen(Filename,"r");

    if(fTxt!= NULL)
    {
        for(i=0; i <= ordre; i++){
            for(j=0; j <= ordre-i; j++){

                fscanf(fTxt,"%lf ",&VM[i][j]); //printf("%lf ",VM[i][j]);
            }
        fscanf(fTxt,"\n"); //printf("\n");
        }
    }

    fclose(fTxt);
    return VM;
}


void comparaisonImages(char* imageName, char* reconstructName,  int ordre, double*** a, int beta, int s, int reconstruit)
{
    int i,j,flag = 0;
    double temp;

    BmpImg bmpImg = readBmpImage(imageName);
    double** Mcentree= MatMCentree(bmpImg,ordre,beta);
    double** Cpq= MatCpq(ordre);
    double** coeff=  MatCoeffLeg(ordre);
    double** MatLegendre= MatMlegendre(ordre,Cpq,coeff,Mcentree);

    double min =  distanceEuclidienne(ordre,MatLegendre, a[0]);

    for(i=1; i < s; i++){

        temp = distanceEuclidienne(ordre, MatLegendre, a[i]);

        if(temp < min)
        {
           min = temp;
           flag = i;
        }
    }
    imageChoisie(flag);

    if(reconstruit==1)
    {
        printf("\nreconstructing the image, it will take some time...");
        double** image= imageReconstruite(ordre,bmpImg,MatLegendre,coeff);
 
        FILE *fp= fopen(reconstructName,"w");

        if(fp!= NULL)
           {
            for(i=0; i < bmpImg.dimX; i++)
            {
                for(j=0; j <bmpImg.dimY; j++)
                {

                    fprintf(fp,"%lf ",image[i][j]);
                }
                fprintf(fp,"\n");
            }
    }

    fclose(fp);
    freeVM(ordre,image);
    }


    freeVM(ordre,Mcentree);
    freeVM(ordre,Cpq);
    freeVM(ordre,coeff);
    freeVM(ordre,MatLegendre);
    freeBmpImg(&bmpImg);

}
void imageChoisie(int flag)
{
      switch (flag)
      {
    case 0:
        printf("\nL'image la plus proche est l'image \"barre.bmp\"");
        break;
    case 1:
        printf("\nL'image la plus proche est l'image \"carre.bmp\"");
        break;
    case 2:
        printf("\nL'image la plus proche est l'image \"cercle.bmp\"");
        break;
    case 3:
        printf("\nL'image la plus proche est l'image \"dessin2.bmp\"");
        break;
    case 4:
        printf("\nL'image la plus proche est l'image \"dessin3.bmp\"");
        break;
    case 5:
        printf("\nL'image la plus proche est l'image \"lady.bmp\"");
        break;
    case 6:
        printf("\nL'image la plus proche est l'image \"snow2.bmp\"");
        break;
    case 7:
        printf("\nL'image la plus proche est l'image \"stop.bmp\"");
        break;
      }
}
