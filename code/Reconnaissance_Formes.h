//
//  Reconnaissance_Formes.h
//  Projet_3E103
//
//  Created by ilyas Aroui and Baldet Ryo on 14/12/2017.


#ifndef RECONNAISSANCE_FORMES_H_INCLUDED
#define RECONNAISSANCE_FORMES_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "myBmpGris.h"





/** free a matrix of order N+1
* @param order : order of the matrix
* @param VM : the matrix to free
*/
void freeVM(int ordre, double** VM); //DEBUGGED

/** create Vandermonde matrix of x's powers
* @param dim : dimension in x of the matrix
* @param puissance : dimension in power of the matrix
* @param xmoy : the value of x centered (used for the centered moments)
* @return Vandermonde matrix of x's powers (square)
*/
double** VMpuissance(int dim, int puissance, double xmoy); //DEBUGGED

/** calculate the image's geometric moments
* @param bmpImg : image structure
* @param p : order p (such that p + q ≤ N)
* @param q : order q
* @return the image's geometric moments
*/
double Mgeo(BmpImg bmpImg, int p, int q);//DEBUGGED


//1.B

/** calculate normalized and centered moments
* @param bmpTmg : image structure
* @param p : order p (such that p + q ≤ order)
* @param q : order q
* @param beta : normalization coeff
* @return normalized and centered moments
*/
double Mcentre(BmpImg bmpImg, int p, int q, int beta); //DEBUGGED

/** create Vandermonde matric of centered and normalized moments (in function of p, q)
* @param bmpTmg : image structure
* @param order : order define in main.c (such that p + q ≤ order)
* @param beta : normalization coeff
* @return  Vandermonde matric of centered and normalized moments (inversed triangular)
*/
double** MatMCentree(BmpImg bmpImg, int N, int beta);//DEBUGGED



/** calculate normalization coeff C
* @param p : order p (such that p + q ≤ N)
* @param q : order q
* @return normalization coeff C
*/
double Cpq(int p, int q); //DEBUGGED

/** create Vandermonde matrix of normalization coeffs C (in function of p, q)
* @param order : order defined in main.c (such that p + q ≤ order)
* @return Vandermonde matrix of normalization coeffs C (inversed triangular)
*/
double** MatCpq(int ordre); //DEBUGGED

/** create Vandermonde matrix of Legendre moments
* @param ordre : order defined in main.c (such that p + q ≤ order)
* @return Vandermonde matrix of Legendre moments (triangular)
*/
double** MatCoeffLeg (int ordre); //DEBUGGED

/** find the polynomial solution of Legendre at a given x
* @param x : variable x (the position of a given pixel)
* @param n : polynomial order
* @param coeff : Legendre coeffs matrix (calculated by a given function)
* @return the polynomial solution of Legendre at a given x
*/
double polyLeg(float x, int n, double** coeff); //DEBUGGED

/** calculate Legendre moments (lambda)
* @param p : order p (such that p + q ≤ N)
* @param q : order q
* @param Cpq : normalization coeff C (calculated by a given function)
* @param coeff : Legendre coeffs matrix (calculated by a given function)
* @param Mcentre : normalized and centered moments (calculated by a given function)
* @return Legendre moments
*/
double Mlegendre(int p, int q, double Cpq, double** coeff, double** Mcentre); //DEBUGGED

/** calculate Vandermonde matrix of Legendre moments (in function of  p, q)
* @param order : order defined in main.c (such that p + q ≤ order)
* @param Cpq : normalization coeffs matrix C (calculated by a given function)
* @param coeff : Legendre coeffs matrix (calculated by a given function)
* @param Mcentre : normalized and centered moments matrix (calculated by a given function)
* @return Vandermonde matrix of Legendre moments (inversed triangular)
*/
double** MatMlegendre(int ordre, double** Cpq, double** coeff, double** Mcentre); //DEBUGGED



/** calculate the reconstructed pixel
* @param order : order defined in main.c (such that p + q ≤ order)
* @param x : pixel placement on x axis
* @param y : pixel placement on y axis
* @param MatMlegendre : Legendre moments matrix  (calculated by a given function)
* @param coeff : Legendre coeffs matrix (calculated by a given function)
* @return reconstructed pixel
*/
double pixelReconstruit(int ordre, float x, float y, double** Mlegendre, double** coeff); //DEBUGGED

/** calculate the reconstruct image
* @param order : order defined in main.c (such that p + q ≤ order)
* @param bmpImg : the reconstructed image structure
* @param MatMlegendre : Legendre moments matrix  (calculated by a given function)
* @param coeff : Legendre coeffs matrix (calculated by a given function)
* @return the reconstructed image (square matrix)
*/
double** imageReconstruite(int ordre, BmpImg bmpImg,double** Mlegendre, double** coeff); //DEBUGGED



/** calculate the euclidean distance between two Legendre moments matrices
* @param order : order defined in main.c (such that p + q ≤ order)
* @param MatMlegendre1 : image 1 Legendre moments matrix  (calculated by a given function)
* @param MatMlegendre2 : image 2 Legendre moments matrix  (calculated by a given function)
* @return euclidean distance between two Legendre moments matrices
*/
double distanceEuclidienne(int ordre, double** Mlegendre1, double** Mlegendre2); //DEBUGGED



/** write a .txt file the Lengendre moments matrix of a given image
* @param imageName : image full path
* @param Filename : .txt file full path
* @param order : order defined in main.c (such that p + q ≤ order)
* @param beta : normalization coeff
*/
void ecrireMlegendre(char* imageName, char* Filename, int ordre, int beta); //DEBUGGED

/** read from a .txt file the Lengendre moments matrix of a given image
* @param Filename : .txt file full path
* @param order : order defined in main.c (such that p + q ≤ order)
* @return Legendre moments of the image (inversed triangular)
*/
double** lireMlegendre(char* Filename, int ordre); //DEBUGGED



/** compare a given image to the database using euclidean distance
* @param imageName : image's full path
* @param order : order defined in main.c (such that p + q ≤ order)
* @param a : 3D tensor of containing the Legendre moments of all the images in the database
* @param beta : normalization coeff
* @param s :number of images in the database
* @param reconstruit :if 1 create a .txt that contains the reconstructed image
*/
void comparaisonImages(char* imageName, int ordre, double*** a, int beta, int s, int reconstruit);

/** display the name of the closest image from the database to the input image
* @param flag: index of the closest image from the database
*/
void imageChoisie(int flag);


#endif // RECONNAISSANCE_FORMES_H_INCLUDED
