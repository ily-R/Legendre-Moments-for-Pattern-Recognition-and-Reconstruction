#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 10
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

float momentgeo(BmpImg bmpImg, int p, int q){ //pas encore testé //structure de l'image en entrée ainsi que les coeff p et q

    unsigned char** image = bmpImg.img;
    int x, y; float moment;

    for (x = 0; x < BmpImg.dimX; x++)
        for (y = 0; y < BmpImg.dimY; y++)
            if (image[x][y] != 0) //pour tout charactère différent de zéro, il faut le transformer en 1
                image[x][y] = 1;
            moment += pow(x, p)*pow(y, q)*image[x][y]; //formule

    return moment;
}

double Mcentre(BmpImg bmpImg, int p,int q){


    int x,y;
    float ohm = momentgeo(BmpImg, 0, 0);
    float xb = momentgeo(BmpImg, 1, 0)/ohm;
    float yb = momentgeo(BmpImg, 0, 1)/ohm;
unsigned char** image = bmpImg.img;
    double som=0;
    for(x=0; x<BmpImg.dimX; x++)
    {
        for(y=0; y<BmpImg.dimY; y++)
        {
            som += (float)(pow(abs(x-xb),p)*pow(abs(y-yb),q))/(float)(pow(ohm,(float)(p+q+2)/2))*image[x][y];
            printf("%fl\n",som);
        }

    }
return som;
}
