#include <stdio.h>

typedef struct pixel_s {
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
}pixel;

typedef struct image_s {
	int h;
	int w;
	pixel* tab;
}image;

typedef enum { R, G, B, A} channel_t;

int kij(int i, int j, int w);

void ascii_print(image* im, channel_t cl, const char* ct);

image* load_image_P1(const char* fname);
image* load_image_P2(const char* fname);
image* load_image_P3(const char* fname);
image* load_image_P4(const char* fname);

bool GetTok(FILE* fdesc, int* ret);

bool hflip(image* im);
bool vflip(image* im);
bool crop(image* im, unsigned int x, unsigned int y, unsigned int w, unsigned int h);
bool resize(image* im, unsigned int w, unsigned int h);