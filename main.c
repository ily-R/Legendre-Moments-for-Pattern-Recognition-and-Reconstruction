#include <stdio.h>
#include <stdlib.h>

#include "src\\myBmpGris.h"
#include "src\\Reconnaissance_Formes.h"
#define ordre 25
#define size 8 //number of images in the database
#define true 1
#define false 0
int main()
{

// if you want to recreate a database uncomment the block bellow

/**
    ecrireMlegendre("..\\database\\lady.bmp","..\\LegendreMoments\\lady.txt",ordre,2);
    ecrireMlegendre("..\\database\\barre.bmp","..\\LegendreMoments\\barre.txt",ordre,2);
    ecrireMlegendre("..\\database\\carre.bmp","..\\LegendreMoments\\carre.txt",ordre,1);
    ecrireMlegendre("..\\database\\dessin2.bmp","..\\LegendreMoments\\dessin2.txt",ordre,1);
    ecrireMlegendre("..\\database\\dessin3.bmp","..\\LegendreMoments\\dessin3.txt",ordre,1);
    ecrireMlegendre("..\\database\\snow2.bmp","..\\LegendreMoments\\snow2.txt",ordre,2);
    ecrireMlegendre("..\\database\\stop.bmp","..\\LegendreMoments\\stop.txt",ordre,1);
    ecrireMlegendre("..\\database\\cercle.bmp","..\\LegendreMoments\\cercle.txt",ordre,1);
**/


    int i,j;
    double *** a= (double ***)malloc(size*sizeof(double**));

        for (i = 0; i< size; i++) {

        a[i]= malloc((ordre+1) * sizeof(double*) );
        for( j = ordre+1; j >0; j-- )
        a[i][ordre+1-j] = calloc(j, sizeof(double));
        }
    a[0]=lireMlegendre("..\\LegendreMoments\\barre.txt",ordre);
    a[1]=lireMlegendre("..\\LegendreMoments\\carre.txt",ordre);
    a[2]=lireMlegendre("..\\LegendreMoments\\cercle.txt",ordre);
    a[3]=lireMlegendre("..\\LegendreMoments\\dessin2.txt",ordre);
    a[4]=lireMlegendre("..\\LegendreMoments\\dessin3.txt",ordre);
    a[5]=lireMlegendre("..\\LegendreMoments\\lady.txt",ordre);
    a[6]=lireMlegendre("..\\LegendreMoments\\snow2.txt",ordre);
    a[7]=lireMlegendre("..\\LegendreMoments\\stop.txt",ordre);

    comparaisonImages("lady2",ordre,a,2,size,true);

    for(i=0;i<size;i++)
    {
      freeVM(ordre,a[i]);

    }


    return 0;
}
