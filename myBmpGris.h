#ifndef _myBmpGris_h_
#define _myBmpGris_h_

#include <stdlib.h>
#include <stdio.h>

typedef struct BmpImg_s BmpImg;
struct BmpImg_s {
	unsigned char** img;	// Image en niveaux de gris
	unsigned int dimX;		// Dimension en x (hauteur)
	unsigned int dimY;		// Dimension en y (largeur)
	
	char* nomImg;				// Nom de l'image
	unsigned int fileSize;		// Taille du fichier en octet
	unsigned int headerSize;	// Taille de l'header en octet
    unsigned int bmpSize;		// Taille de l'header BMP en octet
	unsigned int dibSize;		// Taille de l'header DIB en octet
	unsigned int imgSize;		// Taille de l'image en octet
	
	unsigned char* dibHeader;	// La taille du DIB varie selon que l'on stocke ou non la colormap
	unsigned char bmpHeader[14];	// Bmp Header fait toujours 14 octets (soit 14 char)
};


// Constructeur et Destructeur
/** Methode de creation d'une image Bmp "standard" (pas de LUT, pas d'alpha, codage sur 24 bits)
  * @param dimX nombre de lignes de l'image
  * @param dimY nombre de colonnes de l'image
  * @return une image prete a l'emploi (plans couleur a remplir)
  */
BmpImg createBmpImg( char* str, int dimX, int dimY );

/** Methode de creation d'un header Bmp "standard" (14 octets, pas de LUT, pas d'alpha, codage sur 24 bits)
  * @param bmpImg une struct BmpImg ou les champs dimX, dimY et de taille (xxSize) sont deja remplis
  */
void createBmpHeader( BmpImg* bmpImg );

/** Methode de creation d'un header DIB "standard" (40 octets, pas de LUT, pas d'alpha, codage sur 24 bits)
  * @param bmpImg une struct BmpImg ou les champs dimX, dimY et de taille (xxSize) sont deja remplis
  */
void createDibHeader( BmpImg* bmpImg );

/** Methode d'initialisation d'une image Bmp
  * Met toutes les tailles a 0 et tous les pointeurs a NULL
  * @return une image initialisee
  */
BmpImg initImg( );

/** Methode de destruction d'une image
  * @param bmpImg image a detruire / desallouer
  */
void freeBmpImg( BmpImg* bmpImg );



// Methode de lecture / ecriture
/** Methode de lecture d'une image bitmap
  * @param imgName nom de l'image
  * @return l'image
  */
BmpImg readBmpImage( char* imgName );

/** Methode auxiliaire de lecture d'une image bitmap
  * Sert a lire le header (14 premiers octets) et le dib header
  * @param fImg le fichier image (deja ouvert)
  * @param bmpImg pointeur vers une structure d'image. Apres appel a la fonction, 
  * 	il contiendra les champs:
  * 		fileSize, headerSize, dibSize et imgSize
  * 		bmpHeader et dibHeader
  * 		dimX et dimY
  */
void readHeader( FILE* fImg, BmpImg* bmpImg );

/** Methode auxiliaire de lecture d'une image bitmap
  * Sert a lire les 3 plans couleurs (en codage direct)
  * @param fImg le fichier image (deja ouvert)
  * @param bmpImg pointeur vers une structure d'image. Apres appel a la fonction, 
  * 	il contiendra les champs imgR, imgG et imgB
  */
void readImg( FILE* fImg, BmpImg* bmpImg );


/** Methode d'ecriture d'une image bitmap
  * @param imgName nom de l'image
  * @param bmpImg pointeur vers une structure d'image.
  */
void writeBmpImage( char* imgName, BmpImg* bmpImg );



// Methodes de copie
/** Methode effectuant la copie complete d'une image (header et plan couleur)
  * @param bmpImg image a copier
  * @return la copie de l'image
  */
BmpImg copyBmpAll( BmpImg bmpImg );

/** Methode effectuant la copie du header d'une image bitmap
  * @param origImg image a copier
  * @param copyImg copie de l'image
  */
void copyBmpHeader( BmpImg origImg, BmpImg* copyImg );

/** Methode effectuant la copie des plans couleur d'une image bitmap
  * Ne fait rien si les tailles d'image sont differentes
  * @param origImg image a copier
  * @param copyImg copie de l'image
  */
void copyBmpImg( BmpImg origImg, BmpImg* copyImg );



// Getter et Setter
/** Methode renvoyant la couleur (r, g, b) d'un pixel
  * @param bmpImg une structure image bmp
  * @param x la coordonnee x (ligne) du pixel
  * @param y la coordonnee y (colonne) du pixel
  * @return un entier correspondant au niveau de gris du pixel (0-255)
  * 	ou a -1 si en dehors de l'image
  */
int getPixel( BmpImg bmpImg, int x, int y );

/** Methode stockant la couleur (r, g, b) d'un pixel
  * @param bmpImg une structure image bmp
  * @param clr un entier correspondant au niveau de gris du pixel (0-255)
  * @param x la coordonnee x (ligne) du pixel
  * @param y la coordonnee y (colonne) du pixel
  */
void setPixel( BmpImg bmpImg, int clr, int x, int y );



// Methodes diverses
/** Methode desallouant une matrice de char apres avoir verifie si elle est allouee
  * @param mat la matrice a desallouer
  * @param dimX le nombre de lignes de la matrice
  */
void freeMat( unsigned char** mat, int dimX );

/** Methode allouant l'espace memoire necessaire au plan d'intensite d'une image Bmp
  * @param bmpImg une struct BmpImg ou les champs dimX, dimY sont remplis
  */
void createImg( BmpImg* bmpImg );

/** Methode de conversion d'un tableau de char vers un entier non signe
  * @param buffer le tableau de char a convertir
  * @param pos la position du char de poids faible
  * @return entier non signe correspondant aux char entre pos+3 et pos
  */
unsigned int char2UInt( unsigned char* buffer, int pos );

/** Methode de conversion d'un entier non signe vers un tableau de char
  * @param entier non signe a convertir
  * @param buffer le tableau de char ou stocke l'entier
  * @param pos la position du char de poids faible
  */
void uInt2Char( unsigned int n, unsigned char* buffer, int pos );

#endif
