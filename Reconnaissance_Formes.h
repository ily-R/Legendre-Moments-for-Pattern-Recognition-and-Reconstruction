//
//  Reconnaissance_Formes.h
//  Projet_3E103
//
//  Created by Baldet Ryo and ilyas Aroui on 14/12/2017.
//  Copyright © 2017 Team_Projet. All rights reserved.
//

#ifndef Reconnaissance_Formes_h
#define Reconnaissance_Formes_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


// 1.A
//free la Matrix
void freeVM(double** VM);

//Création de la matrice Vandermonde pour les puissances d
double** Vandermonde(int dim, int ordre, double xmoy);

//Moments Géométriques
double Mgeo(BmpImg bmpImg, int p, int q);

//1.B
//Moments Centrés et normés
double Mcentre(BmpImg bmpImg, int p, int q);

// Creer matrice Vandermonde de moments centre
double** creerMCentree(BmpImg bmpImg,int N);

//1.C
//Calcul de Cpq
double Cpq(int p,int q);

double** creerCpq(int N);

//Moments de Legendre
//Matrice triangulaire des coefficients de Legendre
//Renvoie la matrice triangulaire, en fonction de l'ordre NLeg défini au début du main
double** coeffLeg (int Nleg);

//Moments de Legendre
double Mlegendre(int p, int q, double Cpq, double** coeff, double** Mcentre);

//Construction des polynômes de Legendre

double polyLeg(int x, int n, double** coeff);
//1.D
//Reconstruction de l'image à partir des moments de Legendre

double ImageMomLeg(int x, int y,double** Mlegendre,double** coeff);

double** imageReconstruite(BmpImg bmpimg,double** Mlegendre, double** coeff);

double distanceEuclidienne(double** Mlegendre1, double** Mlegendre2);

#endif /* Reconnaissance_Formes_h */
