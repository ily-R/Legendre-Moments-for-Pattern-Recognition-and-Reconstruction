#include <stdio.h>
#include <stdlib.h>

#include "myBmpGris.h"
#include "Reconnaissance_Formes.h"

#define ordre 45
int main()
{
    int i,j;
    BmpImg bmpImg = readBmpImage("lady.bmp");
    double** Mcentree= MatMCentree(bmpImg,ordre,2);

    double** Cpq= MatCpq(ordre);

    double** coeff=  MatCoeffLeg(ordre);

    double** MatLegendre= MatMlegendre(ordre,Cpq,coeff,Mcentree);

    //Calcul de la matrice des moments de Legendre (vérifié et comparé avec le fichier de Dietenbeck)

    //Reconstruction de l'image à partir des moments (à ne pas faire parce que le temps de compilation est énorme
    //                                                et les résultats ne donnent rien).

//    double** image= imageReconstruite(ordre,bmpImg,MatLegendre,coeff);

    //Affichage de la matrice des moments de Legendre, ou de n'importe laquelle en remplacant par le nom correspondant

    for(i=0;i<=ordre;i++)
    {
        for(j=0;j<=ordre-i;j++)
        {
            printf("%lf ",MatLegendre[i][j]);
        }
        printf("\n");
    }

    //Libération des matrices et de la structure image

    freeVM(ordre,Mcentree);
    freeVM(ordre,Cpq);
    freeVM(ordre,coeff);
    freeVM(ordre,MatLegendre);
//    freeVM(ordre,image);
    freeBmpImg(&bmpImg);

    return 0;
}
