//
//  main.c
//  Projet_3E103
//
//  Created by Baldet Ryo on 07/12/2017.
//  Copyright © 2017 Team_Projet. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 50




int main(int argc, const char * argv[]) {
    
    
    double ohm = momentgeo(BmpImg, 0, 0);
    double xb = momentgeo(BmpImg, 1, 0)/ohm;
    double yb = momentgeo(BmpImg, 0, 1)/ohm;
    
    double Nabla = Mcentre(BmpImg bmpImg, int p, int q, double** VdmX, double** VdmY);
    //Calcul moments centrÈs normÈs
    
    float cpq = cpq(int p,int q);
    double Lambda = lambda(BmpImg bmpImg, int p, int q, double xb, double yb, cpq, float**a);
    
    
    
    
    
    void DetruireV(float** V, int dim){


    return 0;
}
