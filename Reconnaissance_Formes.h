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




// 1.A
//free la Matrix
void freeVM(int ordre, double** VM);//DEBUGGED

//CrÈation de la matrice Vandermonde pour les puissances d
double** VMpuissance(int dim, int ordre, double xmoy);//DEBUGGED

//Moments GÈomÈtriques
double Mgeo(BmpImg bmpImg, int p, int q);//DEBUGGED

//1.B
//Moments CentrÈs et normÈs
double Mcentre(BmpImg bmpImg, int p, int q,int beta);//DEBUGGED

// Creer matrice Vandermonde de moments centre
double** MatMCentree(BmpImg bmpImg,int N,int beta);//DEBUGGED

//1.C
//Calcul de Cpq
double Cpq(int p,int q);//DEBUGGED

double** MatCpq(int ordre);//DEBUGGED

//Moments de Legendre
//Matrice triangulaire des coefficients de Legendre
//Renvoie la matrice triangulaire, en fonction de l'ordre NLeg dÈfini au dÈbut du main
double** MatCoeffLeg (int ordre);//DEBUGGED

//Construction des polynÙmes de Legendre

double polyLeg(int x, int n, double** coeff);//DEBUGGED
//Moments de Legendre
double Mlegendre(int p, int q, double Cpq, double** coeff, double** Mcentre);//DEBUGGED

//matrice de moments de Legendre
double** MatMlegendre(int ordre, double** Cpq, double** coeff, double** Mcentre);//DEBUGGED


//1.D
//Reconstruction de l'image ‡ partir des moments de Legendre

double pixelReconstruit(int ordre, int x, int y,double** Mlegendre,double** coeff);

double** imageReconstruite(int ordre, BmpImg bmpImg,double** Mlegendre, double** coeff);

double distanceEuclidienne(int ordre, double** Mlegendre1, double** Mlegendre2);//DEBUGGED

#endif // RECONNAISSANCE_FORMES_H_INCLUDED
