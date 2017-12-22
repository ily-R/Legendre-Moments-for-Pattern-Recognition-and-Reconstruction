#include "Reconnaissance_Formes.h"

// 1.A

//Libération de matrices
void freeVM(int ordre, double** VM) //DEBUGGED
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


//Création de la matrice Vandermonde des puissances de x
double** VMpuissance(int dim, int puissance, double xmoy) //DEBUGGED
{
    int j, x;
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


// Calcul des moments géométriques
double Mgeo(BmpImg bmpImg, int p, int q) //DEBUGGED
{
    unsigned char** image = bmpImg.img; //matrice image (pixels)
    unsigned int dimX, dimY; int x, y;
    double moment=0.0;

    dimX = bmpImg.dimX; //dimention de l'image
    dimY = bmpImg.dimY;

    double ** VdmX = VMpuissance(dimX, p, 0); //non centré donc xb = 0
    double ** VdmY = VMpuissance(dimY, q, 0); //non centré donc yb = 0

    for (x = 0; x < dimX; x++){
        for (y = 0; y < dimY; y++){
            if (image[x][y] != 0) //pour tout charactère différent de zéro (donc multiplie par 1)
                moment += VdmX[x][p]*VdmY[y][q]; //image[x][y] = 1
        }
    }
    return moment;
}


//1.B

//Calcul des moments centrés et normés
double Mcentre(BmpImg bmpImg, int p, int q, int beta) //DEBUGGED
{
    unsigned char** image = bmpImg.img; //matrice image (pixels)
    unsigned int dimX, dimY; int x, y;
    double somme = 0.0;
    dimX = bmpImg.dimX; //dimention de l'image
    dimY = bmpImg.dimY;

    double ohm = Mgeo(bmpImg, 0, 0);
    double xb = Mgeo(bmpImg, 1, 0)/ohm;
    double yb = Mgeo(bmpImg, 0, 1)/ohm;

    double ** VdmX = VMpuissance(dimX, p, xb); //création des matrices de VdM des puissances de x
    double ** VdmY = VMpuissance(dimY, q, yb);

    for(x=0; x<dimX; x++){
        for(y=0; y<dimY; y++){

            if(image[x][y]!=0)
                somme += (VdmX[x][p]*VdmY[y][q])/pow(beta*ohm,((double)(p+q+2.))/2.);//image[x][y]=1
        }
    }
    return somme;
}

// Creation de la matrice VanderMonde des moments centrés et normés
double** MatMCentree(BmpImg bmpImg, int ordre, int beta)//DEBUGGED
{
    //Création de la matrice
    double** VM; int j;
    VM = malloc( (ordre + 1) * sizeof(double*) );
    for( j = ordre+1; j>0; j--)
        VM[ordre+1 - j] = calloc(j, sizeof(double)); //matrice triangulaire inversée

    //Remplissage
    int p,q;
    for(p=0; p <= ordre; p++){
        for(q=0; q <= ordre - p; q++){ //matrice triangulaire inversée

            VM[p][q]= Mcentre(bmpImg, p, q, beta);
        }
    }
    return VM;
}


//1.C

//Calcul de Cpq, coefficient de normalisation
double Cpq(int p, int q) //DEBUGGED
{
    double result = (2*p+1)*(2*q+1)/4.;
    return result ;
}

// Creation de la matrice VanderMonde des coefficients Cpq
double** MatCpq(int ordre) //DEBUGGED
{
    //Création de la matrice
    double** VM; int j;
    VM = malloc( (ordre+1) * sizeof(double*) );
    for( j = ordre+1; j >0; j-- )
        VM[ordre+1-j] = calloc(j, sizeof(double)); //matrice triangulaire inversée

    //Remplissage
    int p,q;
    for(p=0; p <= ordre; p++){
        for(q=0; q <= ordre-p; q++){ //matrice triangulaire inversée

            VM[p][q]= Cpq(p, q);
        }
    }
    return VM;
}

//Création de la matrice triangulaire des coefficients de Legendre
double** MatCoeffLeg (int ordre) //DEBUGGED
{
    int i, j;
    float n = 1.0; //parcours des coeff

    // Création de la matrice
    double ** coeff;
    coeff = malloc( (ordre+1) * sizeof(double*) ); // de la colonne for( int i = 0; i < N; i++ )
    for(j = 0; j <= ordre; j++ )
        coeff[j] = calloc( j+1, sizeof(double) ); // Tableau 1D de  → i+1 elements

    //Conditions initiales
    coeff[0][0] = 1.0; coeff[1][0] = 0.0; coeff[1][1]= 1.0;

    //Remplissage
    for(j = 2; j<= ordre; j++){ //Entre la 2e ligne et la Nème ligne

        for(i=0; i<= n+1; i++){ //Parcours de a entre 0 et n+1

            if (i == 0){  //Condition sur la première colonne
                coeff[j][i] = (-n/(n+1))*coeff[(int)n-1][0]; }

            else if (i == n+1) //Condition sur la dernière diagonale
                coeff[j][i] = ((2*n+1)/(n+1)) * coeff[(int)n][(int)n];

            else if (i == n) //Condition sur l'avant dernière diagonale
                coeff[j][i] = 0;

            else //Autres
                coeff[j][i] = ((2*n+1)/(n+1)) * coeff[(int)n][i-1] - (n/(n+1)) * coeff[(int)n-1][i];
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
double polyLeg(float x, int n, double** coeff ) //DEBUGGED
{
    int i; double sum = 0;
    for(i=0; i <= n; i++)
        sum += coeff[n][i] * pow(x, i);
    return sum;
}

//Calcul des moments de Legendre
double Mlegendre(int p, int q, double Cpq, double** coeff, double** Mcentre) //DEBUGGED
{
    int i,j;
    double result = 0.0;
    for(i=0; i <= p; i++){
        for(j=0; j <= q; j++){
            result += coeff[p][i] * coeff[q][j] * Mcentre[i][j];
        }
    }
    return Cpq * result;
}

//Création de la matrice de Vandermonde des moments de Legendre
double** MatMlegendre(int ordre, double** Cpq, double** coeff, double** Mcentre) //DEBUGGED
{
    //Création de la matrice
    double** VM; int j;
    VM= malloc((ordre+1) * sizeof(double*) );
    for( j = ordre+1; j > 0; j-- )
        VM[ordre+1 -j] = calloc(j, sizeof(double));
    
    //Remplissage
    int p,q;
    for(p = 0; p <= ordre; p++){
        for(q = 0; q <= ordre-p; q++){

            VM[p][q]= Mlegendre(p,q,Cpq[p][q],coeff,Mcentre);
        }
    }
    return VM;
}


//1.D

//Reconstruction d'un pixel (normalisé) de l'image à partir des moments de Legendre
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

//Reconstruction de l'image entière à partir des moments de Legendre
double** imageReconstruite(int ordre, BmpImg bmpImg, double** Mlegendre, double** coeff)
{
    int i, x, y;
    float dimX = bmpImg.dimX; //dimention de l'image
    float dimY = bmpImg.dimY;

    //Création de la matrice image
    double** image;
    image= malloc(dimX*sizeof(double*));
    for(i = 0; i < dimX; i++)
        image[i] = calloc(dimY, sizeof(double));

    //Remplissage
    for(x = 0; x < dimX; x++){
        for(y = 0; y < dimY; y++){

            image[x][y] = pixelReconstruit(ordre, 2*x/dimX -1, 2*y/dimY -1, Mlegendre, coeff); //normalisation de x et y
        }
    }
    return image;
}


//2.A

//Calcul de la distance Euclidienne entre 2 matrices de moments de Legendre
double distanceEuclidienne(int ordre, double** Mlegendre1, double** Mlegendre2) //DEBUGGED
{
    int p,q;
    double somme = 0.0;

    for(p=0; p <= ordre; p++){
        for(q=0; q <= ordre-p; q++){ //parcours de matrices triangulaires inversées

            somme += (Mlegendre1[p][q] - Mlegendre2[p][q]) * (Mlegendre1[p][q] - Mlegendre2[p][q]); //on évite d'utiliser pow
        }
    }
    return sqrt(somme);
}


//2.B

//Création d'un fichier .txt contenant la matrice de moments de Legendre d'une image
void ecrireMlegendre(char* imageName, char* Filename, int ordre, int beta) //DEBUGGED
{
    //Calcul des matrices de moments de Legendre
    int i,j;
    BmpImg bmpImg = readBmpImage(imageName);
    double** Mcentree= MatMCentree(bmpImg,ordre,beta);
    double** Cpq= MatCpq(ordre);
    double** coeff= MatCoeffLeg(ordre);
    double** MatLegendre= MatMlegendre(ordre,Cpq,coeff,Mcentree);

    //Stockage dans un fichier .txt
    FILE *fTxt= fopen(Filename,"w"); //Création du fichier

    if(fTxt!= NULL)
    {
        for(i=0; i <= ordre; i++){
            for(j=0; j <= ordre-i; j++){

                fprintf(fTxt,"%lf ", MatLegendre[i][j]);
            }
        fprintf(fTxt,"\n");
        }
    } //if

    fclose(fTxt); //Fermeture du fichier
    
    //Libération de toutes les matrices utilisées
    freeVM(ordre, Mcentree);
    freeVM(ordre, Cpq);
    freeVM(ordre, coeff);
    freeVM(ordre, MatLegendre);
    freeBmpImg(&bmpImg);
}

//Lecture et stockage dans une variable du fichier .txt contenant la matrice de moments de Legendre d'une image
double** lireMlegendre(char* Filename, int ordre) //DEBUGGED
{
    //Création de la matrice
    double** VM; int j,i;
    VM = malloc((ordre+1) * sizeof(double*) );
    for( j = ordre+1; j >0; j-- )
        VM[ordre+1-j] = calloc(j, sizeof(double));

    //Lecture du fichier et stockage dans la matrice
    FILE *fTxt= fopen(Filename,"r");

    if(fTxt!= NULL)
    {
        for(i=0; i <= ordre; i++){
            for(j=0; j <= ordre-i; j++){

                fscanf(fTxt,"%lf ",&VM[i][j]); //printf("%lf ", VM[i][j]);
            }
        fscanf(fTxt,"\n"); //printf("\n");
        }
    } //if
    
    fclose(fTxt); //Fermeture du fichier
    return VM;
}

//Comparaison d'une image avec la base de donnée
void comparaisonImages(char* imageName, int ordre, double*** a, int beta, int s, int reconstruit) //DEBUGGED
{
    int i, j;
    double temp;
    char str[20] = "";
    strcpy(str, imageName);

    //Matrice des moments de Legendre de l'image à comparer
    BmpImg bmpImg = readBmpImage(strcat(str,".bmp"));
    double** Mcentree = MatMCentree(bmpImg,ordre,beta);
    double** Cpq = MatCpq(ordre);
    double** coeff =  MatCoeffLeg(ordre);
    double** MatLegendre = MatMlegendre(ordre,Cpq,coeff,Mcentree);

    //Comparaison
    int flag = 0; //numéro de l'image dont la distance est la plus petite
    double min =  distanceEuclidienne(ordre, MatLegendre, a[0]); //valeur initiale de la distance minimum
    
    for(i = 1; i < s; i++){
        
        temp = distanceEuclidienne(ordre, MatLegendre, a[i]); //calcul de la distance

        if(temp < min)
        {
           min = temp; //distance minimum stockée
           flag = i; //numéro de l'image de la base de données associée stockée
        }
    }
    
    imageChoisie(flag); //numéro de l'image de la base de données la plus proche de l'image rentrée

    
    // RECONSTRUCTION DE L'IMAGE
    if(reconstruit == 1) //condition en entrée
    {
        printf("\nReconstruction de l'image en cours..."); 
        double** image = imageReconstruite(ordre, bmpImg, MatLegendre, coeff); //Création de l'image reconstruite
        
        //Stockage dans un fichier .txt
        FILE *fp= fopen(strcat(str,".txt"),"w"); //Création du fichier .txt
        
        if(fp!= NULL) //Remplissage
        {
            for(i = 0; i < bmpImg.dimX; i++){
                for(j = 0; j < bmpImg.dimY; j++){

                    fprintf(fp, "%lf ", image[i][j]);
                }
                fprintf(fp, "\n");
            }
        } //if remplissage

        fclose(fp); //Fermeture du fichier
        freeVM(ordre, image); //libération de l'image reconstruite
    } //if reconstruit

    //libération de toutes les matrices utilisées
    freeVM(ordre, Mcentree);
    freeVM(ordre, Cpq);
    freeVM(ordre, coeff);
    freeVM(ordre, MatLegendre);
    freeBmpImg(&bmpImg);

}

//Affichage du nom de l'image de la base de donnée la plus proche
void imageChoisie(int flag) //DEBUGGED
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
