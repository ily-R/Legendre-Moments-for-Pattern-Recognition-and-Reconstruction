#include "myBmpGris.h"

// Constructeur et Destructeur
/** Methode de creation d'une image Bmp "standard" (pas de LUT, pas d'alpha, codage sur 24 bits)
  * @param dimX nombre de lignes de l'image
  * @param dimY nombre de colonnes de l'image
  * @return une image prete a l'emploi (plans couleur a remplir)
  */
BmpImg createBmpImg( char* str, int dimX, int dimY ) {
    BmpImg bmpImg = initImg( );
    // 1) Dimensions et nom de l'image
    bmpImg.nomImg = str;
    bmpImg.dimX = dimX;
    bmpImg.dimY = dimY;
    // 2) Differentes tailles de l'image
    bmpImg.bmpSize = 14; // octets
    bmpImg.dibSize = 56; // octets

    unsigned int byteAlignment = (3*dimY)%4;
    if( byteAlignment == 0 ) {  // Pas de 4 byte alignment
        bmpImg.imgSize = 3 * dimX * dimY; // 3 plans couleur de dimX x dimY octets
    } else {    // 4 byte alignment
        bmpImg.imgSize = dimX * ( 3*dimY + 4 - byteAlignment );
    }

    bmpImg.headerSize = bmpImg.bmpSize + bmpImg.dibSize;
    bmpImg.fileSize = bmpImg.headerSize + bmpImg.imgSize;
    // 3) On cree le header
    createBmpHeader( &bmpImg );
    createDibHeader( &bmpImg );
    // 4) On cree les plans couleurs
    createImg( &bmpImg );

    return bmpImg;
}

/** Methode de creation d'un header Bmp "standard" (14 octets, pas de LUT, pas d'alpha, codage sur 24 bits)
  * @param bmpImg une struct BmpImg ou les champs dimX, dimY et de taille (xxSize) sont deja remplis
  */
void createBmpHeader( BmpImg* bmpImg ) {
    bmpImg->bmpHeader[0] = 'B';
    bmpImg->bmpHeader[1] = 'M';
    uInt2Char( 70, bmpImg->bmpHeader, 2 );
    uInt2Char( 0, bmpImg->bmpHeader, 6 );    // Unused (appli specific)
    uInt2Char( bmpImg->headerSize, bmpImg->bmpHeader, 10 );   // Offset where the pixel array can be found
}

/** Methode de creation d'un header DIB "standard" (40 octets, pas de LUT, pas d'alpha, codage sur 24 bits)
  * @param bmpImg une struct BmpImg ou les champs dimX, dimY et de taille (xxSize) sont deja remplis
  */
void createDibHeader( BmpImg* bmpImg ) {
	bmpImg->dibHeader = calloc( bmpImg->dibSize, sizeof( unsigned char ) );
    uInt2Char( 40, bmpImg->dibHeader, 0 );  // Number of bytes in the DIB header
    uInt2Char( bmpImg->dimY, bmpImg->dibHeader, 4 );    // Width of the bitmap in pixels (left to right order)
    uInt2Char( bmpImg->dimX, bmpImg->dibHeader, 8 );    // Height of the bitmap in pixels (bottom to top order). Positive for bottom to top pixel order.
    uInt2Char( 1572865, bmpImg->dibHeader, 12 );	// Number of color planes being used & bits per pixel

    uInt2Char( 0, bmpImg->dibHeader, 16 );  // BI_RGB, no pixel array compression used
    uInt2Char( bmpImg->imgSize, bmpImg->dibHeader, 20 );	// Size of the raw bitmap data (including padding)
    uInt2Char( 2835, bmpImg->dibHeader, 24 );   // Horizontal resolution of the image (72 DPI × 39.3701 inches per meter)
    uInt2Char( 2835, bmpImg->dibHeader, 28 );	// Vertical resolution of the image (72 DPI × 39.3701 inches per meter)
    uInt2Char( 0, bmpImg->dibHeader, 32 );      // Number of colors in the palette
    uInt2Char( 0, bmpImg->dibHeader, 36 );      // Important colors: 0 means all colors are important
}

/** Methode d'initialisation d'une image Bmp
  * Met toutes les tailles a 0 et tous les pointeurs a NULL
  * @return une image initialisee
  */
BmpImg initImg( ) {
	BmpImg bmpImg;
    // 1) Dimensions et nom de l'image
    bmpImg.nomImg = NULL;
    bmpImg.dimX = 0;
    bmpImg.dimY = 0;
    // 2) Differentes tailles de l'image
    bmpImg.bmpSize = 0;
    bmpImg.dibSize = 0;
    bmpImg.imgSize = 0;
    bmpImg.headerSize = 0;
    bmpImg.fileSize = 0;
    // 3) On fait pointer le header et le plan de gris vers NULL
	bmpImg.dibHeader = NULL;
	bmpImg.img = NULL;

    return bmpImg;
}


/** Methode de destruction d'une image
  * @param bmpImg image a detruire / desallouer
  */
void freeBmpImg( BmpImg* bmpImg ) {
	int i;
	// On desalloue chaque ligne de chaque plan couleur
	for( i = 0; i < bmpImg->dimX; i++ )
		free( bmpImg->img[i] );
	// On desalloue chaque plan couleur
	free( bmpImg->img );
	// On pointe vers NULL par securite
	bmpImg->img = NULL;
	// On desalloue le header dib
	free( bmpImg->dibHeader );
	// La taille de l'image est 0
	bmpImg->fileSize = 0;
	bmpImg->headerSize = 0;
	bmpImg->imgSize = 0;
	bmpImg->dibSize = 0;
	bmpImg->dimY = 0;
	bmpImg->dimX = 0;
	bmpImg->nomImg = NULL;
}



// Methode de lecture / ecriture
/** Methode de lecture d'une image bitmap
  * @param imgName nom de l'image
  * @return l'image
  */
BmpImg readBmpImage( char* imgName ) {
	BmpImg bmpImg = initImg( );
	bmpImg.nomImg = imgName;
	FILE *fImg = fopen( imgName, "rb" );

	readHeader( fImg, &bmpImg );
	readImg( fImg, &bmpImg );

	fclose( fImg );
	return bmpImg;
}

/** Methode auxiliaire de lecture d'une image bitmap
  * Sert a lire le header (14 premiers octets) et le dib header
  * @param fImg le fichier image (deja ouvert)
  * @param bmpImg pointeur vers une structure d'image. Apres appel a la fonction,
  * 	il contiendra les champs:
  * 		fileSize, headerSize, dibSize et imgSize
  * 		bmpHeader et dibHeader
  * 		dimX et dimY
  */
void readHeader( FILE* fImg, BmpImg* bmpImg ) {
	// Bmp Header
	fread( bmpImg->bmpHeader, sizeof( char ), 14, fImg );
	bmpImg->fileSize = char2UInt( bmpImg->bmpHeader, 2 );		// Taille du fichier en octet (octets 2 a 5)
	bmpImg->headerSize = char2UInt( bmpImg->bmpHeader, 10 );	// Taille du header en octet (octets 10 a 13)
	bmpImg->bmpSize = 14;										// Taille du header BMP en octet
	bmpImg->imgSize = bmpImg->fileSize - bmpImg->headerSize;	// Taille de l'image en octet

	// DIB Header
	bmpImg->dibSize = bmpImg->headerSize - bmpImg->bmpSize;		// Taille du header DIB en octet
	bmpImg->dibHeader = calloc( bmpImg->dibSize, sizeof(char) );
	fread( bmpImg->dibHeader, sizeof(char), bmpImg->dibSize, fImg );
	bmpImg->dimY = char2UInt( bmpImg->dibHeader, 4 );	// Nombre de colonnes (octets 4 a 7)
	bmpImg->dimX = char2UInt( bmpImg->dibHeader, 8 );	// Nombre de lignes (octets 8 a 11)
}

/** Methode auxiliaire de lecture d'une image bitmap
  * Sert a lire les 3 plans couleurs (en codage direct)
  * @param fImg le fichier image (deja ouvert)
  * @param bmpImg pointeur vers une structure d'image. Apres appel a la fonction,
  * 	il contiendra les champs imgR, imgG et imgB
  */
void readImg( FILE* fImg, BmpImg* bmpImg ) {
	int i = 0;

	bmpImg->img = calloc( bmpImg->dimX, sizeof(unsigned char*) );
	for( i = 0; i < bmpImg->dimX; i++ )
		bmpImg->img[i] = calloc( bmpImg->dimY, sizeof(unsigned char) );

	/* Le format bitmap stocke les lignes de bas en haut mais en image on
	 * considere la ligne du haut comme etant la 0.
	 * => On part de i = dimX-1 et on decremente pour que 0 corresponde
	 * a la ligne du haut et dimX-1 a celle du bas
	 */
	i--;
	int j = 0;
	int pos;
	unsigned char tmp;
	int byteAlignment = 4 - (3 * bmpImg->dimY) % 4;
	if( byteAlignment == 4 ) byteAlignment = 0;
	// On lit 3 caracteres par tour => pos + 3
	for( pos = 0; pos < bmpImg->imgSize; pos = pos + 3 ) {
		fread( &(bmpImg->img[i][j]), sizeof( unsigned char ), 1, fImg );
		fread( &tmp, sizeof( unsigned char ), 1, fImg );
		fread( &tmp, sizeof( unsigned char ), 1, fImg );
		j++;
		if( j >= bmpImg->dimY ) {
            // 4 byte alignment
			for( j = 0; j < byteAlignment; j++ ) {
                fread( &tmp, sizeof( unsigned char ), 1, fImg );
                pos++;
			}
            // RaZ de j, MaJ de i
			j = 0;
			i--;
		}
	}
}


/** Methode d'ecriture d'une image bitmap
  * @param imgName nom de l'image
  * @param bmpImg pointeur vers une structure d'image.
  */
void writeBmpImage( char* imgName, BmpImg* bmpImg ) {
	int i, j;
	FILE *fImg = fopen( imgName, "wb" );

	// 1) Write Bmp Header
	fwrite( bmpImg->bmpHeader, sizeof( char ), 14, fImg );
	// 2) Write DIB Header
	fwrite( bmpImg->dibHeader, sizeof( char ), bmpImg->dibSize, fImg );
	// 3) Write Image

	unsigned char tmp = 0;
	int byteAlignment = 4 - (3 * bmpImg->dimY) % 4;
	if( byteAlignment == 4 ) byteAlignment = 0;
	for( i = bmpImg->dimX-1; i >= 0; i-- ) {
		for( j = 0; j < bmpImg->dimY; j++ ) {
			fwrite( &(bmpImg->img[i][j]), sizeof( unsigned char ), 1, fImg );
			fwrite( &(bmpImg->img[i][j]), sizeof( unsigned char ), 1, fImg );
			fwrite( &(bmpImg->img[i][j]), sizeof( unsigned char ), 1, fImg );
		}
        // 4 bytes alignment
        for( j = 0; j < byteAlignment; j++ ) {
            fwrite( &tmp, sizeof( unsigned char ), 1, fImg );
        }
	}
	fclose( fImg );
}



// Methodes de copie
/** Methode effectuant la copie complete d'une image (header et plan couleur)
  * @param bmpImg image a copier
  * @return la copie de l'image
  */
BmpImg copyBmpAll( BmpImg bmpImg ) {
    BmpImg copyImg = initImg( );
    copyBmpHeader( bmpImg, &copyImg );
    copyBmpImg( bmpImg, &copyImg );

    return( copyImg );
}

/** Methode effectuant la copie du header d'une image bitmap
  * @param origImg image a copier
  * @param copyImg copie de l'image
  */
void copyBmpHeader( BmpImg origImg, BmpImg* copyImg ) {
    // 1) On copie les dimensions et le nom de l'image
    copyImg->nomImg = origImg.nomImg;
    copyImg->dimX = origImg.dimX;
    copyImg->dimY = origImg.dimY;
    // 2) On copie les differentes tailles
    copyImg->fileSize = origImg.fileSize;
    copyImg->headerSize = origImg.headerSize;
    copyImg->dibSize = origImg.dibSize;
    copyImg->imgSize = origImg.imgSize;
    // 3) On copie les headers
    int i;
        // Header bitmap
    for( i = 0; i < 14; i++ )
        copyImg->bmpHeader[i] = origImg.bmpHeader[i];
        // On s'assure que le header dib est desalloue
    if( copyImg->dibHeader != NULL )
        free( copyImg->dibHeader );

        // Copie du header dib
    copyImg->dibHeader = calloc( copyImg->dibSize, sizeof( char ) );
    for( i = 0; i < copyImg->dibSize; i++ )
        copyImg->dibHeader[i] = origImg.dibHeader[i];
}

/** Methode effectuant la copie des plans couleur d'une image bitmap
  * Ne fait rien si les tailles d'image sont differentes
  * @param origImg image a copier
  * @param copyImg copie de l'image
  */
void copyBmpImg( BmpImg origImg, BmpImg* copyImg ) {
    int i, j;
    int dimXO = origImg.dimX;
    int dimYO = origImg.dimY;
    int dimXC = copyImg->dimX;
    int dimYC = copyImg->dimY;

    // On s'assure que les tailles d'images sont les memes (sinon il faudrait changer le header)
    if( (dimXO == dimXC) && (dimYO == dimYC) ) {
        // 1) On s'assure que les images de la copie sont desallouees
        freeMat( copyImg->img, dimXC );
        // 2) On cree le plan de gris
        createImg( copyImg );
        // 3) On copie les colonnes
        for( i = 0; i < dimXC; i++ ) {
            for( j = 0; j < dimYC; j++ )
                copyImg->img[i][j] = origImg.img[i][j];
        }
    }
}



// Getter et Setter
/** Methode renvoyant la couleur (r, g, b) d'un pixel
  * @param bmpImg une structure image bmp
  * @param x la coordonnee x (ligne) du pixel
  * @param y la coordonnee y (colonne) du pixel
  * @return un entier correspondant au niveau de gris du pixel (0-255)
  * 	ou a -1 si en dehors de l'image
  */
int getPixel( BmpImg bmpImg, int x, int y ) {
	int res = -1;
	if( (x >= 0) && (x < bmpImg.dimX) ) {
		if( (y >= 0) && (y < bmpImg.dimY) ) {
			res = bmpImg.img[x][y];
		}
	}
	return res;
}

/** Methode stockant la couleur (r, g, b) d'un pixel
  * @param bmpImg une structure image bmp
  * @param clr un entier correspondant au niveau de gris du pixel (0-255)
  * @param x la coordonnee x (ligne) du pixel
  * @param y la coordonnee y (colonne) du pixel
  */
void setPixel( BmpImg bmpImg, int clr, int x, int y ) {
	if( (x >= 0) && (x < bmpImg.dimX) ) {
		if( (y >= 0) && (y < bmpImg.dimY) )
			bmpImg.img[x][y] = (unsigned char)(clr);
	}
}



// Methodes diverses
/** Methode desallouant une matrice de char apres avoir verifie si elle est allouee
  * @param mat la matrice a desallouer
  * @param dimX le nombre de lignes de la matrice
  */
void freeMat( unsigned char** mat, int dimX ) {
    if( mat != NULL ){
        int i;
        for( i = 0; i < dimX; i++ )
            free( mat[i] );
        free( mat );
    }
    mat = NULL;
}

/** Methode allouant l'espace memoire necessaire aux 3 plans couleur d'une image Bmp
  * @param bmpImg une struct BmpImg ou les champs dimX, dimY
  */
void createImg( BmpImg* bmpImg ) {
    // 1) On alloue les lignes
    bmpImg->img = calloc( bmpImg->dimX, sizeof( unsigned char* ) );
    // 2) On alloue les colonnes
    int i;
    for( i = 0; i < bmpImg->dimX; i++ )
        bmpImg->img[i] = calloc( bmpImg->dimY, sizeof( unsigned char ) );
}

/** Methode de conversion d'un tableau de char vers un entier non signe
  * @param buffer le tableau de char a convertir
  * @param pos la position du char de poids faible
  * @return entier non signe correspondant aux char entre pos+3 et pos
  */
unsigned int char2UInt( unsigned char* buffer, int pos ) {
	unsigned int res = (unsigned char)( buffer[pos+3] ) << 24
					   | (unsigned char)( buffer[pos+2] ) << 16
					   | (unsigned char)( buffer[pos+1] ) <<  8
					   | (unsigned char)( buffer[pos] );
	return res;
}

/** Methode de conversion d'un entier non signe vers un tableau de char
  * @param entier non signe a convertir
  * @param buffer le tableau de char ou stocke l'entier
  * @param pos la position du char de poids faible
  */
void uInt2Char( unsigned int n, unsigned char* buffer, int pos ) {
	buffer[pos+3] = (n >> 24) & 0xFF;
	buffer[pos+2] = (n >> 16) & 0xFF;
	buffer[pos+1] = (n >> 8) & 0xFF;
	buffer[pos] = n & 0xFF;
}
