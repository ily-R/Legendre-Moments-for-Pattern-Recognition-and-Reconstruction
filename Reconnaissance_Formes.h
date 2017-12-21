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

/** Fonction permettant de libérer une matrice d'ordre N+1  
* @param ordre : ordre de la matrice  
* @param VM : matrice à libérer 
*/
void freeVM(int ordre, double** VM); //DEBUGGED

/** Fonction permettant créer la matrice de Vandermonde des puissances de x 
* @param dim : dimension en x de la matrice  
* @param puissance : dimension en puissances de la matrice
* @param xmoy : valeur de x centré (utilisé dans les moments centrés)
* @return la matrice de Vandermonde des puissances de x (carrée)
*/
double** VMpuissance(int dim, int puissance, double xmoy); //DEBUGGED

/** Fonction permettant de calculer les moment géométriques de l'image
* @param bmpImg : structure de l'image dont les moments sont à calculer  
* @param p : ordre p (tel que p + q ≤ N)
* @param q : ordre q
* @return les moments géométriques de l'image
*/
double Mgeo(BmpImg bmpImg, int p, int q); //DEBUGGED


//1.B

/** Fonction permettant de calculer les moments centrés et normés 
* @param bmpTmg : structure de l'image dont les moments sont à calculer  
* @param p : ordre p (tel que p + q ≤ ordre)
* @param q : ordre q
* @param beta : coefficient
* @return les moments centrés et normés
*/
double Mcentre(BmpImg bmpImg, int p, int q, int beta); //DEBUGGED

/** Fonction permettant de créer la matrice de Vandermonde des moments centrés et normés (en fonction de p, q)
* @param bmpTmg : structure de l'image dont les moments sont à calculer  
* @param ordre : ordre défini au début du main (tel que p + q ≤ ordre)
* @param beta : coefficient
* @return la matrice de Vandermonde des moments centrés et normés (triangulaire inversée)
*/
double** MatMCentree(BmpImg bmpImg, int ordre, int beta); //DEBUGGED


//1.C

/** Fonction permettant de calculer le coefficient de normalisation C 
* @param p : ordre p (tel que p + q ≤ N)
* @param q : ordre q
* @return le coefficient de normalisation C 
*/
double Cpq(int p, int q); //DEBUGGED

/** Fonction permettant de créer la matrice de Vandermonde des coefficients de normalisation C (en fonction de p, q)
* @param ordre : ordre défini au début du main (tel que p + q ≤ ordre)
* @return la matrice de Vandermonde des coefficients de normalisation C (triangulaire inversée)
*/
double** MatCpq(int ordre); //DEBUGGED

/** Fonction permettant de créer la matrice de Vandermonde des coefficients de Legendre
* @param ordre : ordre défini au début du main (tel que p + q ≤ ordre)
* @return la matrice de Vandermonde des coefficients de Legendre (triangulaire)  
*/
double** MatCoeffLeg (int ordre); //DEBUGGED

/** Fonction permettant de calculer la solution polynomiale de Legendre à un x donné 
* @param x : variable x (correspondant ici à l'emplacement d'un pixel donné)
* @param n : ordre n du polynôme
* @param coeff : matrice des coefficients de Legendre (calculée avec la fonction donnée)
* @return la solution polynomiale de Legendre à un x donné   
*/
double polyLeg(int x, int n, double** coeff); //DEBUGGED

/** Fonction permettant de calculer les moments de Legendre (lambda) 
* @param p : ordre p (tel que p + q ≤ N)
* @param q : ordre q
* @param Cpq : coefficient de normalisation C (calculé avec la fonction donnée)
* @param coeff : matrice des coefficients de Legendre (calculée avec la fonction donnée)
* @param Mcentre : moment centré et normé (calculé avec la fonction donnée)
* @return les moments de Legendre 
*/
double Mlegendre(int p, int q, double Cpq, double** coeff, double** Mcentre); //DEBUGGED

/** Fonction permettant de calculer la matrice de Vandermonde des moments de Legendre (en fonction de p, q)
* @param ordre : ordre défini au début du main (tel que p + q ≤ ordre)
* @param Cpq : matrice des coefficients de normalisation C (calculée avec la fonction donnée)
* @param coeff : matrice des coefficients de Legendre (calculée avec la fonction donnée)
* @param Mcentre : matrice des moments centrés et normés (calculée avec la fonction donnée)
* @return la matrice des moments de Legendre (triangulaire inversée)
*/
double** MatMlegendre(int ordre, double** Cpq, double** coeff, double** Mcentre);//DEBUGGED


//1.D

/** Fonction permettant de calculer le pixel reconstruit
* @param ordre : ordre défini au début du main (tel que p + q ≤ ordre)
* @param x : emplacement du pixel sur l'axe x
* @param y : emplacement du pixel sur l'axe y
* @param MatMlegendre :  matrice des moments de Legendre (calculée avec la fonction donnée)
* @param coeff : matrice des coefficients de Legendre (calculée avec la fonction donnée)
* @return le pixel reconstruit
*/
double pixelReconstruit(int ordre, int x, int y, double** MatMlegendre, double** coeff);

/** Fonction permettant de calculer l'image reconstruite
* @param ordre : ordre défini au début du main (tel que p + q ≤ ordre)
* @param bmpImg : structure de l'image à reconstruire
* @param MatMlegendre :  matrice des moments de Legendre (calculée avec la fonction donnée)
* @param coeff : matrice des coefficients de Legendre (calculée avec la fonction donnée)
* @return l'image reconstruite (matrice carrée)
*/
double** imageReconstruite(int ordre, BmpImg bmpImg, double** MatMlegendre, double** coeff);

/** Fonction permettant de calculer la distance Euclidienne entre les matrices de moments (de Legendre)
* @param ordre : ordre défini au début du main (tel que p + q ≤ ordre)
* @param MatMlegendre1 :  matrice des moments de Legendre de l'image 1 (calculée avec la fonction donnée)
* @param MatMlegendre2 :  matrice des moments de Legendre de l'image 2 (calculée avec la fonction donnée)
* @return la distance Euclidienne entre les matrices de moments
*/
double distanceEuclidienne(int ordre, double** MatMlegendre1, double** MatMlegendre2);//DEBUGGED


#endif // RECONNAISSANCE_FORMES_H_INCLUDED
