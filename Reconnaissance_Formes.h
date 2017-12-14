//
//  Reconnaissance_Formes.h
//  Projet_3E103
//
//  Created by Baldet Ryo on 08/12/2017.
//  Copyright © 2017 Team_Projet. All rights reserved.
//

#ifndef Reconnaissance_Formes_h
#define Reconnaissance_Formes_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// 1.A

//Moments Géométriques
double momentgeo(BmpImg bmpImg, int p, int q);


//1.B

//Moments Centrés et normés
double Mcentre(BmpImg bmpImg, int p, int q, double ohm, double** VdmX, double** VdmY);

//Création de la matrice Vandermonde pour les puissances d
double** Vandermonde(int dim, int p, float xmoy);

//Destruction des matrices de Vandermonde
void DetruireV(float** V, int dim);


//1.C

//Calcul de Cpq
float cpq(int p,int q);
    
//Moments de Legendre
double lambda(BmpImg bmpImg, int p, int q, double xb, double yb, float c, float**a);

//Matrice triangulaire des coefficients de Legendre
double** coeffLeg (); //Renvoie la matrice triangulaire, en fonction de l'ordre NLeg défini au début du main
    
//Destruction de la matrice
void freeLeg(double** a);

//Construction des polynômes de Legendre
double polyLeg(int x, int n, double** a);


//1.D

//Reconstruction de l'image à partir des moments de Legendre
double** ImageMomLeg(int x, int y, double** a);




#endif /* Reconnaissance_Formes_h */
