#include "myBmpGris.h"


BmpImg createBmpImg( char* str, int dimX, int dimY ) {
    BmpImg bmpImg = initImg( );
    bmpImg.nomImg = str;
    bmpImg.dimX = dimX;
    bmpImg.dimY = dimY;
    bmpImg.bmpSize = 14; // octets
    bmpImg.dibSize = 56; // octets

    unsigned int byteAlignment = (3*dimY)%4;
    if( byteAlignment == 0 ) {
        bmpImg.imgSize = 3 * dimX * dimY;
    } else {
        bmpImg.imgSize = dimX * ( 3*dimY + 4 - byteAlignment );
    }

    bmpImg.headerSize = bmpImg.bmpSize + bmpImg.dibSize;
    bmpImg.fileSize = bmpImg.headerSize + bmpImg.imgSize;
    createBmpHeader( &bmpImg );
    createDibHeader( &bmpImg );
    createImg( &bmpImg );

    return bmpImg;
}


void createBmpHeader( BmpImg* bmpImg ) {
    bmpImg->bmpHeader[0] = 'B';
    bmpImg->bmpHeader[1] = 'M';
    uInt2Char( 70, bmpImg->bmpHeader, 2 );
    uInt2Char( 0, bmpImg->bmpHeader, 6 );
    uInt2Char( bmpImg->headerSize, bmpImg->bmpHeader, 10 );
}


void createDibHeader( BmpImg* bmpImg ) {
	bmpImg->dibHeader = calloc( bmpImg->dibSize, sizeof( unsigned char ) );
    uInt2Char( 40, bmpImg->dibHeader, 0 );
    uInt2Char( bmpImg->dimY, bmpImg->dibHeader, 4 );
    uInt2Char( bmpImg->dimX, bmpImg->dibHeader, 8 );
    uInt2Char( 1572865, bmpImg->dibHeader, 12 );
    uInt2Char( 0, bmpImg->dibHeader, 16 );
    uInt2Char( bmpImg->imgSize, bmpImg->dibHeader, 20 );
    uInt2Char( 2835, bmpImg->dibHeader, 24 );
    uInt2Char( 2835, bmpImg->dibHeader, 28 );
    uInt2Char( 0, bmpImg->dibHeader, 32 );
    uInt2Char( 0, bmpImg->dibHeader, 36 );
}


BmpImg initImg( ) {
	BmpImg bmpImg;
    bmpImg.nomImg = NULL;
    bmpImg.dimX = 0;
    bmpImg.dimY = 0;
    bmpImg.bmpSize = 0;
    bmpImg.dibSize = 0;
    bmpImg.imgSize = 0;
    bmpImg.headerSize = 0;
    bmpImg.fileSize = 0;
	bmpImg.dibHeader = NULL;
	bmpImg.img = NULL;

    return bmpImg;
}



void freeBmpImg( BmpImg* bmpImg ) {
	int i;
	for( i = 0; i < bmpImg->dimX; i++ )
		free( bmpImg->img[i] );
	free( bmpImg->img );
	bmpImg->img = NULL;
	free( bmpImg->dibHeader );
	bmpImg->fileSize = 0;
	bmpImg->headerSize = 0;
	bmpImg->imgSize = 0;
	bmpImg->dibSize = 0;
	bmpImg->dimY = 0;
	bmpImg->dimX = 0;
	bmpImg->nomImg = NULL;
}



BmpImg readBmpImage( char* imgName ) {
	BmpImg bmpImg = initImg( );
	bmpImg.nomImg = imgName;
	FILE *fImg = fopen( imgName, "rb" );

	readHeader( fImg, &bmpImg );
	readImg( fImg, &bmpImg );

	fclose( fImg );
	return bmpImg;
}


void readHeader( FILE* fImg, BmpImg* bmpImg ) {
	fread( bmpImg->bmpHeader, sizeof( char ), 14, fImg );
	bmpImg->fileSize = char2UInt( bmpImg->bmpHeader, 2 );
	bmpImg->headerSize = char2UInt( bmpImg->bmpHeader, 10 );
	bmpImg->bmpSize = 14;
	bmpImg->imgSize = bmpImg->fileSize - bmpImg->headerSize;

	bmpImg->dibSize = bmpImg->headerSize - bmpImg->bmpSize;
	bmpImg->dibHeader = calloc( bmpImg->dibSize, sizeof(char) );
	fread( bmpImg->dibHeader, sizeof(char), bmpImg->dibSize, fImg );
	bmpImg->dimY = char2UInt( bmpImg->dibHeader, 4 );
	bmpImg->dimX = char2UInt( bmpImg->dibHeader, 8 );
}

void readImg( FILE* fImg, BmpImg* bmpImg ) {
	int i = 0;

	bmpImg->img = calloc( bmpImg->dimX, sizeof(unsigned char*) );
	for( i = 0; i < bmpImg->dimX; i++ )
		bmpImg->img[i] = calloc( bmpImg->dimY, sizeof(unsigned char) );


	i--;
	int j = 0;
	int pos;
	unsigned char tmp;
	int byteAlignment = 4 - (3 * bmpImg->dimY) % 4;
	if( byteAlignment == 4 ) byteAlignment = 0;
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



void writeBmpImage( char* imgName, BmpImg* bmpImg ) {
	int i, j;
	FILE *fImg = fopen( imgName, "wb" );

	fwrite( bmpImg->bmpHeader, sizeof( char ), 14, fImg );
	fwrite( bmpImg->dibHeader, sizeof( char ), bmpImg->dibSize, fImg );

	unsigned char tmp = 0;
	int byteAlignment = 4 - (3 * bmpImg->dimY) % 4;
	if( byteAlignment == 4 ) byteAlignment = 0;
	for( i = bmpImg->dimX-1; i >= 0; i-- ) {
		for( j = 0; j < bmpImg->dimY; j++ ) {
			fwrite( &(bmpImg->img[i][j]), sizeof( unsigned char ), 1, fImg );
			fwrite( &(bmpImg->img[i][j]), sizeof( unsigned char ), 1, fImg );
			fwrite( &(bmpImg->img[i][j]), sizeof( unsigned char ), 1, fImg );
		}
        for( j = 0; j < byteAlignment; j++ ) {
            fwrite( &tmp, sizeof( unsigned char ), 1, fImg );
        }
	}
	fclose( fImg );
}



BmpImg copyBmpAll( BmpImg bmpImg ) {
    BmpImg copyImg = initImg( );
    copyBmpHeader( bmpImg, &copyImg );
    copyBmpImg( bmpImg, &copyImg );

    return( copyImg );
}


void copyBmpHeader( BmpImg origImg, BmpImg* copyImg ) {
    copyImg->nomImg = origImg.nomImg;
    copyImg->dimX = origImg.dimX;
    copyImg->dimY = origImg.dimY;
    copyImg->fileSize = origImg.fileSize;
    copyImg->headerSize = origImg.headerSize;
    copyImg->dibSize = origImg.dibSize;
    copyImg->imgSize = origImg.imgSize;
    int i;
    for( i = 0; i < 14; i++ )
        copyImg->bmpHeader[i] = origImg.bmpHeader[i];
    if( copyImg->dibHeader != NULL )
        free( copyImg->dibHeader );

    copyImg->dibHeader = calloc( copyImg->dibSize, sizeof( char ) );
    for( i = 0; i < copyImg->dibSize; i++ )
        copyImg->dibHeader[i] = origImg.dibHeader[i];
}


void copyBmpImg( BmpImg origImg, BmpImg* copyImg ) {
    int i, j;
    int dimXO = origImg.dimX;
    int dimYO = origImg.dimY;
    int dimXC = copyImg->dimX;
    int dimYC = copyImg->dimY;

    if( (dimXO == dimXC) && (dimYO == dimYC) ) {
        freeMat( copyImg->img, dimXC );
        createImg( copyImg );
        for( i = 0; i < dimXC; i++ ) {
            for( j = 0; j < dimYC; j++ )
                copyImg->img[i][j] = origImg.img[i][j];
        }
    }
}




int getPixel( BmpImg bmpImg, int x, int y ) {
	int res = -1;
	if( (x >= 0) && (x < bmpImg.dimX) ) {
		if( (y >= 0) && (y < bmpImg.dimY) ) {
			res = bmpImg.img[x][y];
		}
	}
	return res;
}


void setPixel( BmpImg bmpImg, int clr, int x, int y ) {
	if( (x >= 0) && (x < bmpImg.dimX) ) {
		if( (y >= 0) && (y < bmpImg.dimY) )
			bmpImg.img[x][y] = (unsigned char)(clr);
	}
}



void freeMat( unsigned char** mat, int dimX ) {
    if( mat != NULL ){
        int i;
        for( i = 0; i < dimX; i++ )
            free( mat[i] );
        free( mat );
    }
    mat = NULL;
}


void createImg( BmpImg* bmpImg ) {
    // 1) On alloue les lignes
    bmpImg->img = calloc( bmpImg->dimX, sizeof( unsigned char* ) );
    // 2) On alloue les colonnes
    int i;
    for( i = 0; i < bmpImg->dimX; i++ )
        bmpImg->img[i] = calloc( bmpImg->dimY, sizeof( unsigned char ) );
}


unsigned int char2UInt( unsigned char* buffer, int pos ) {
	unsigned int res = (unsigned char)( buffer[pos+3] ) << 24
					   | (unsigned char)( buffer[pos+2] ) << 16
					   | (unsigned char)( buffer[pos+1] ) <<  8
					   | (unsigned char)( buffer[pos] );
	return res;
}


void uInt2Char( unsigned int n, unsigned char* buffer, int pos ) {
	buffer[pos+3] = (n >> 24) & 0xFF;
	buffer[pos+2] = (n >> 16) & 0xFF;
	buffer[pos+1] = (n >> 8) & 0xFF;
	buffer[pos] = n & 0xFF;
}
