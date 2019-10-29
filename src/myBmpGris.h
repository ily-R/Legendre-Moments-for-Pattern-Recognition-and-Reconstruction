#ifndef _myBmpGris_h_
#define _myBmpGris_h_

#include <stdlib.h>
#include <stdio.h>

typedef struct BmpImg_s BmpImg;
struct BmpImg_s {
	unsigned char** img;	// gray scale image
	unsigned int dimX;		// height
	unsigned int dimY;		// width

	char* nomImg;				// image's name
	unsigned int fileSize;		// file size in octet
	unsigned int headerSize;	// header size in octet
    unsigned int bmpSize;		// Bmp header size in octet
	unsigned int dibSize;		// DIB header size in octet
	unsigned int imgSize;		// image size in octet

	unsigned char* dibHeader;	// DIB size depends on colormap stored
	unsigned char bmpHeader[14];	// Bmp Header is always 14 octet ( 14 chars )
};


// Constructor and Destructor
/** create a standard Bmp image (no LUT, nor alpha, over 24 bits)
  * @param dimX number of lines in the image
  * @param dimY number of columns in the image
  * @return a ready empty image
  */
BmpImg createBmpImg( char* str, int dimX, int dimY );

/** create a standar Bmp header (14 octet, no LUT, nor alpha, over 24 bits)
  * @param bmpImg: BmpImg structure where dimX, dimY and xxSize are already filled
  */
void createBmpHeader( BmpImg* bmpImg );

/** create a standar DIB header (40 octets,  no LUT, nor alpha,  24 bits)
  * @param bmpImg: BmpImg structure where dimX, dimY and xxSize are already filled
  */
void createDibHeader( BmpImg* bmpImg );

/** initialize a Bmp image
  * put 0 to the sizes and NULL to the pointers
  * @return an initialized image
  */
BmpImg initImg( );

/** destruct an image
  * @param bmpImg: image to destruct
  */
void freeBmpImg( BmpImg* bmpImg );



/** read a bitmap image
  * @param imgName:image's name
  * @return the image
  */
BmpImg readBmpImage( char* imgName );

/** other methods to read bitmap image
  * read header and dibheader
  * @param fImg: image file (already open)
  * @param bmpImg: pointer to image structure. after calling the function,
  * 	it contains:
  * 		fileSize, headerSize, dibSize et imgSize
  * 		bmpHeader et dibHeader
  * 		dimX et dimY
  */
void readHeader( FILE* fImg, BmpImg* bmpImg );

/** other methods to read bitmap image
  * read header and dibheader
  * @param fImg: image file (already open)
  * @param bmpImg: pointer to image structure. after calling the function,
  * 	it contains: imgR, imgG et imgB
  */
void readImg( FILE* fImg, BmpImg* bmpImg );


/** write bitmap image
  * @param imgName
  * @param bmpImg: pointer to the image structure
  */
void writeBmpImage( char* imgName, BmpImg* bmpImg );



/** compy an image (header and color plane)
  * @param bmpImg: image to copy
  * @return the image copy
  */
BmpImg copyBmpAll( BmpImg bmpImg );

/** copy a header of a bitmap image
  * @param origImg: image to copy
  * @param copyImg: the image copy
  */
void copyBmpHeader( BmpImg origImg, BmpImg* copyImg );

/** copy bitmap image's color planes
  * do nothing if the images dont have the same size
  * @param origImg
  * @param copyImg
  */
void copyBmpImg( BmpImg origImg, BmpImg* copyImg );



/** get the color (r, g, b) of a pixel
  * @param bmpImg : a bmp image structure
  * @param x row coordinate
  * @param y column coordinate
  * @return grascale color (0-255)
  * 	or a -1 if outside image border
  */
int getPixel( BmpImg bmpImg, int x, int y );

/** store pixel's color (r, g, b)
  * @param bmpImg image structure bmp
  * @param clr gray color level of the pixel (0-255)
  * @param x row coordinate
  * @param y column coordinate of the pixel
  */
void setPixel( BmpImg bmpImg, int clr, int x, int y );



// Methodes diverses
/** free a matrix of Chars if it's acllocated
  * @param mat the matrix to be free
  * @param dimX number of rows in the matrix
  */
void freeMat( unsigned char** mat, int dimX );

/** allocate the needed memory space for the image Bmp
  * @param bmpImg BmpImg structure where the attributes dimX, dimY are filled
  */
void createImg( BmpImg* bmpImg );

/** convert an array of chars to an unsigned integer
  * @param buffer: the array of chars
  * @param pos position of the weak weight chars
  * @return unsigned int corresponds to the char between pos+3 and pos
  */
unsigned int char2UInt( unsigned char* buffer, int pos );

/** convert an unsigned int to an array of chars
  * @param entier unsigned int
  * @param buffer array of chars
  * @param pos position of the weak weight chars
  */
void uInt2Char( unsigned int n, unsigned char* buffer, int pos );

#endif
