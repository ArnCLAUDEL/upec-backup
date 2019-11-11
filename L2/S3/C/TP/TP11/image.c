#ifndef IMAGE_C
#define IMAGE_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "image.h"

int kij(int i, int j, int w) {
  return i*w + j;
}


void ascii_print(image* im, channel_t cl, const char* ct) {
  int i = 0, j = 0, k = 0;
  for(i = 0; i < im->h; i++){
    for(j = 0; j < im->w; j++){
      k = kij(i,j,im->w);
      switch(cl) {  
        case R: printf("%c",ct[((int)strlen(ct) * im->tab[k].R) / 256]);break;
        case G: printf("%c",ct[((int)strlen(ct) * im->tab[k].G) / 256]);break;
        case B: printf("%c",ct[((int)strlen(ct) * im->tab[k].B) / 256]);break;
        case A: printf("%c",ct[((int)strlen(ct) * im->tab[k].A) / 256]);break;
      };
      printf(" ");
    }
    printf("\n");
  }
}

bool GetTok(FILE* fdesc, int* ret){
  static char buffer[100] = {'\0'};
  static int pos = 0;
  while(true){
    switch(buffer[pos]){
        case ' ':
        case '\r':
        case '\n':    
        case '\t':  pos++;
                    break;
        case '\0':  
        case '#' :  fgets(buffer, 100, fdesc);
                    if(buffer[0] == '\0') return false;
                    pos = 0;
                    break;

        default:   if(!sscanf(buffer+pos, "%d", ret)) return false;
                   while((buffer[pos] >= '0') && (buffer[pos] <= '9')) pos++;
                   return true;
                   break;
    }
  }
}


image* load_image_P1(const char* fname) {
    FILE* fdesc = fopen(fname,"r");
    int adress = 0;
    int* ret = &adress;
    image* img = malloc(sizeof(image));
    fseek(fdesc,2,SEEK_SET);
      GetTok(fdesc,ret);
        img->w = *ret;
      GetTok(fdesc,ret);
        img->h = *ret;
          img->tab = malloc((img->w) * (img->h));
        int k = 0; 
        for(k = 0; k < img->w * img->h; k++) {
          GetTok(fdesc,ret);
            img->tab[k].R = (*ret)*255;
            img->tab[k].G = (*ret)*255;
            img->tab[k].B = (*ret)*255;
          }
    fclose(fdesc);
    ret = NULL;
    return img;
}

image* load_image_P2(const char* fname) {
    FILE* fdesc = fopen(fname,"r");
    int adress = 0;
    int* ret = &adress;
    image* img = malloc(sizeof(image));
    fseek(fdesc,2,SEEK_SET);
      GetTok(fdesc,ret);
       img->w = *ret;
      GetTok(fdesc,ret);
        img->h = *ret;
      img->tab = malloc((img->w) * (img->h));
      int k = 0; 
      GetTok(fdesc,ret);
      int color_max = *ret;
        for(k = 0; k < img->w * img->h; k++) {
          GetTok(fdesc,ret);
            img->tab[k].R = (*ret)*255/color_max;
            img->tab[k].G = (*ret)*255/color_max;
            img->tab[k].B = (*ret)*255/color_max;
        }
    fclose(fdesc);
    ret = NULL;
    return img;
}
  
image* load_image_P3(const char* fname) {
    FILE* fdesc = fopen(fname,"r");
    int adress = 0;
    int* ret = &adress;
    image* img = malloc(sizeof(image));
    fseek(fdesc,2,SEEK_SET);
      GetTok(fdesc,ret);
       img->w = *ret;
      GetTok(fdesc,ret);
        img->h = *ret;
      img->tab = malloc((img->w) * (img->h));
      int k = 0;
      GetTok(fdesc,ret);
      int color_max = *ret;
        for(k = 0; k < img->w * img->h; k++) {
          GetTok(fdesc,ret);
            img->tab[k].R = (*ret)*255/color_max;
          GetTok(fdesc,ret);
            img->tab[k].G = (*ret)*255/color_max;
          GetTok(fdesc,ret);
            img->tab[k].B = (*ret)*255/color_max;
        }
    fclose(fdesc);
    ret = NULL;
    return img;
}


bool hflip(image* im) {
    pixel* temp = malloc(sizeof(pixel));
    int i,j,k1,k2;
    for(i = 0; i < ((im->h)/2) + 1; i++) {
      for(j = 0; j < im->w; j++) {
        k1 = kij(i,j,im->w);
        k2 = kij((im->h)-i,j,im->w);
        *temp = im->tab[k1];
        im->tab[k1] = im->tab[k2];
        im->tab[k2] = *temp;
      }
    }
    free(temp);
    return true;
}

bool vflip(image* im) {
     pixel* temp = malloc(sizeof(pixel));
    int i,j,k1,k2;
    for(i = 0; i < im->h; i++) {
      for(j = 0; j < ((im->w)/2)+1; j++) {
        k1 = kij(i,j,im->w);
        k2 = kij(i,(im->w)-j,im->w);
        *temp = im->tab[k1];
        im->tab[k1] = im->tab[k2];
        im->tab[k2] = *temp;
      }
    }
    free(temp);
    return true; 
}

bool crop(image* im, unsigned int x, unsigned int y, unsigned int h, unsigned int w) {
    if(x>(im->h)||y>(im->w)) {
      printf("Veuillez rentre les coordonnées d'un pixel qui est dans l'image.\n");
      return false;
    }
    if(x<0||y<0) {
      printf("Veuillez rentreR les coordonnées d'un pixel qui est dans l'image.\n");
      return false;
    }
    if(h>(im->h)||w>(im->w)-y) {
      printf("Les nouvelles dimensions sont incohérentes avec les dimensions initiales de l'image.\n");
      return false;
    }
    if(h!=(im->h)-x||w!=(im->w)-y) {
      printf("Les nouvelles dimensions de l'image sont incohérentes avec le pixel donné.\n");
      return false;
    }
    pixel* tab = malloc(w*h);
    int i,j,k,csr = 0;
    for(i = x; i < im->h; i++) {
      for(j = y; j < im->w; j++) {
        k = kij(i,j,im->w);
            tab[csr].R = im->tab[k].R;
            tab[csr].G = im->tab[k].G;
            tab[csr].B = im->tab[k].B;
        csr++;
      }
      csr += y;
    }
    im->tab = tab;
    return true; 
}

bool resize(image* im, unsigned int w, unsigned int h) {
  image* nim = malloc(sizeof(image));
  int coefW = w/(im->w),coefH = h/(im->h);
    nim->w = w;
    nim->h = h;
    nim->tab = malloc(w*h);
   int iN = 0,jN = 0,gN = 0,k = 0,kN = 0;
    for(iN = 0; iN < nim->h; iN++) {
      for(jN= 0; jN < nim->w; jN++) {
        k = kij(iN,jN,im->w);  
        for(gN = 0; gN < coefH; gN++) {
          kN = kij(iN+gN,jN,im->w);  
          nim->tab[kN] = im->tab[k];
        }
      }
    }
    im = nim;
    return true;
}

#endif