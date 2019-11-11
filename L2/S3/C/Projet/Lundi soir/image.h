#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h>
#define WH (img->w * img->h)

typedef struct pixel_s { unsigned char R; unsigned char G; unsigned char B; unsigned char A; }pixel;
typedef struct image_s { int h; int w; pixel* tab; }image;
typedef enum channel_e { R, G, B, A} channel_t;

int 	kij(int i, int j, int w);
void 	QuickSort(int tableau[], int debut, int fin);

FILE* 	GetImage (void);

image* 	WidthLength(image* img, FILE* fdesc);

bool 	GetTok(FILE* fdesc, int *ret);
bool 	GetTokBinary(FILE* fdesc, int *ret, int color_max);
bool 	Load_image_P1(image* img, const char* fname);
bool 	Load_image_P2(image* img, const char* fname);
bool 	Load_image_P3(image* img, const char* fname);
bool 	Load_image_P4(image* img, const char* fname);
bool 	Load_image_P5(image* img, const char* fname);
bool 	Load_image_P6(image* img, const char* fname);

bool 	Negative(image* img);
image*  GrayScale(image* img);
bool 	hflip(image* im);	
bool 	vflip(image* im);
bool 	crop(image* im, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
image* 	resize(image* im, unsigned int w, unsigned int h);
image* 	PivotD(image* img);
image*	PivotG(image* img);
bool	BlackWhiteSeuil(image* img, int seuil);
bool	BlackWhiteMoyenne(image* img);
bool	BlackWhiteMediane(image* img);

image* 	Load_image(const char* fname);
bool 	save_image(const char* fname, image* im, const char* magic_number);
void 	ascii_print(image* im, channel_t cl, const char* ct);
void 	PrintDataImg(image* img);
			
void 	ArgLoad(const char* s);
void 	ArgSave(const char* s);
void 	ArgPrintDataImg();
void 	ArgNegative();
void 	ArgGrayScale();
void	ArgBlackWhiteSeuil(int seuil);
void 	ArgBlackWhiteAVG();
void	ArgBlackWhiteMediane();
void 	Arghflip();
void 	Argvflip();
void 	ArgReturnRight();
void	ArgReturnLeft();
void 	ArgCrop( unsigned int x, unsigned int y, unsigned int w, unsigned int h);
void 	ArgResize(unsigned int w, unsigned int h);
#endif