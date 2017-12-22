#include <stdio.h>
#include <stdlib.h>

#include "myBmpGris.h"
#include "Reconnaissance_Formes.h"
#define ordre 25
#define size 8 //la taille de notre base de données pour un ordre choisi
#define true 1
#define false 0
int main()
{

// Si vous voulez recrire la base de données pour un autre ordre decommentez ce qui est en dessous.

//ecrireMlegendre("..\\lady.bmp","..\\lady.txt",ordre,2);
//ecrireMlegendre("..\\barre.bmp","..\\barre.txt",ordre,2);
//ecrireMlegendre("..\\carre.bmp","..\\carre.txt",ordre,1);
//ecrireMlegendre("..\\dessin2.bmp","..\\dessin2.txt",ordre,1);
//ecrireMlegendre("..\\dessin3.bmp","..\\dessin3.txt",ordre,1);
//ecrireMlegendre("..\\snow2.bmp","..\\snow2.txt",ordre,2);
//ecrireMlegendre("..\\stop.bmp","..\\stop.txt",ordre,1);
//ecrireMlegendre("..\\cercle.bmp","..\\cercle.txt",ordre,1);


    int i,j;
    double *** a= (double ***)malloc(size*sizeof(double**));

        for (i = 0; i< size; i++) {

        a[i]= malloc((ordre+1) * sizeof(double*) );
        for( j = ordre+1; j >0; j-- )
        a[i][ordre+1-j] = calloc(j, sizeof(double));
        }
    a[0]=lireMlegendre("..\\barre.txt",ordre);
    a[1]=lireMlegendre("..\\carre.txt",ordre);
    a[2]=lireMlegendre("..\\cercle.txt",ordre);
    a[3]=lireMlegendre("..\\dessin2.txt",ordre);
    a[4]=lireMlegendre("..\\dessin3.txt",ordre);
    a[5]=lireMlegendre("..\\lady.txt",ordre);
    a[6]=lireMlegendre("..\\snow2.txt",ordre);
    a[7]=lireMlegendre("..\\stop.txt",ordre);

    comparaisonImages("lady2",ordre,a,2,size,true);

    for(i=0;i<size;i++)
    {
      freeVM(ordre,a[i]);

    }


    return 0;
}
