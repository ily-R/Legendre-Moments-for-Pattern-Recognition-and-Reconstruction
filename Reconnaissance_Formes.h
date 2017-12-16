//
//  Reconnaissance_Formes.h
//  Projet_3E103
//
//  Created by Baldet Ryo and ilyas Aroui on 14/12/2017.
//  Copyright © 2017 Team_Projet. All rights reserved.
//

#ifndef RECONNAISSANCE_FORMES_H_INCLUDED
#define RECONNAISSANCE_FORMES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "myBmpGris.h"

#define N_ordre 10


// 1.A
//free la Matrix
void freeVM(int N, double** VM);

//CrÈation de la matrice Vandermonde pour les puissances d
double** Vandermonde(int dim, int ordre, double xmoy);

//Moments GÈomÈtriques
double Mgeo(BmpImg bmpImg, int p, int q);

//1.B
//Moments CentrÈs et normÈs
double Mcentre(BmpImg bmpImg, int p, int q);

// Creer matrice Vandermonde de moments centre
double** creerMCentree(BmpImg bmpImg,int N);

//1.C
//Calcul de Cpq
double Cpq(int p,int q);

double** creerCpq(int N);

//Moments de Legendre
//Matrice triangulaire des coefficients de Legendre
//Renvoie la matrice triangulaire, en fonction de l'ordre NLeg dÈfini au dÈbut du main
double** coeffLeg (int Nleg);

//Moments de Legendre
double Mlegendre(int p, int q, double Cpq, double** coeff, double** Mcentre);

//Construction des polynÙmes de Legendre

double polyLeg(int x, int n, double** coeff);
//1.D
//Reconstruction de l'image ‡ partir des moments de Legendre

double ImageMomLeg(int N, int x, int y,double** Mlegendre,double** coeff);

double** imageReconstruite(int N, BmpImg bmpimg,double** Mlegendre, double** coeff);

double distanceEuclidienne(int N, double** Mlegendre1, double** Mlegendre2);

#endif // RECONNAISSANCE_FORMES_H_INCLUDED
