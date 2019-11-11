#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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
  printf("\n\n");
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
        k2 = kij((im->h)-i-1,j,im->w);
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
        k2 = kij(i,(im->w)-j-1,im->w);
        printf("k1: %d k2: %d\n",k1,k2);
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
  //int coefW = w/(im->w);
  int coefH = h/(im->h);
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
    im->h = nim->h;
    im->w = nim->w;
    im->tab = nim->tab;
    free(nim);
    return true;
}

image* resize1(image* im, unsigned int w, unsigned int h) {
  int iW = im->w,iH = im->h;
  ascii_print(im,G," .*&&#");
  image* nim = malloc(sizeof(image));
  const pixel* tab = malloc(sizeof(im->w*im->h));
  tab = im->tab;
  int coefW = w/(im->w);
  int coefH = h/(im->h);
    nim->w = w;
    nim->h = h;
    nim->tab = malloc(w*h);
  int i = 0,j = 0,g1 = 0,g2 = 0,k = 0, cpt = 0;
    for(i = 0; i < iH; i++) {
      g1 = 1;
      while(g1 <= coefH) {
        g1++;
        for(j = 0; j < iW; j++) {
            k = kij(i,j,iW);
            g2  = 1;
            while(g2 <= coefW) {
             g2++;
             printf("i:%d j:%d k:%d cpt:%d tab:%d\n",i,j,k,cpt,tab[k].G);
            nim->tab[cpt].R = tab[k].R;
            nim->tab[cpt].G = tab[k].G;
            nim->tab[cpt].B = tab[k].B;
            cpt++;
        }
      }
      printf("  --------------------\n");
    }
            printf("  --------------------\n");
  }
    return nim;
}

/*
bool PivotD(image* img) {
  pixel* tab = malloc(sizeof(img->tab));
  pixel* tab2 = malloc(sizeof(img->tab));
  tab2 = img->tab;
  int i = 0,j = 0,k1,k2 = 0;
  for(i = 0; i < img->w; i++) {
    for(j = img->h-1; j >= 0; j--) {
      k1 = kij(j,i,img->w);
            // printf("i:%d j:%d k1:%d k2:%d tab:%d\n",i,j,k1,k2,tab2[k1].G);
      tab[k2] = tab2[k1];
      k2++;
    }
       //   printf("  --------------------\n");

  }
  int trans = img->w;
  img->w = img->h;
  img->h = trans;
  img->tab = tab;
  return true;
}
*/
image* PivotD(image* img) {
  image* nim = malloc(sizeof(image));
  nim->w = img->h;
  nim->h = img->w;
  //nim->tab = malloc(sizeof(nim->h*nim->w));
  int i = 0,j = 0,k1,k2 = 0;
  for(i = 0; i < img->w; i++) {
    for(j = img->h-1; j >= 0; j--) {
      k1 = kij(j,i,img->w);
      nim->tab[k2] = img->tab[k1];
      k2++;
    }
  }/*
  imageC->h = nim->h;
  imageC->w = nim->w;
  imageC->tab = nim->tab;
  free(nim);*/
  return nim;
}

image* PivotG(image* img) {
  image* nim = malloc(sizeof(image));
  nim->w = img->h;
  nim->h = img->w;
  int i = 0,j = 0,k1,k2 = 0;
  for(i = img->w-1; i >= 0; i--) {
    for(j = 0; j < img->h; j++) {
      k1 = kij(j,i,img->w);
      nim->tab[k2] = img->tab[k1];
      k2++;
    }
  }/*
  imageC->h = nim->h;
  imageC->w = nim->w;
  imageC->tab = nim->tab;
  free(nim);
  */
  return nim;
}

 /*
bool resize2(image* im, unsigned int w, unsigned int h) {
  image* nim = malloc(sizeof(image));
  pixel* tab = im->tab;
  int coefW = w/(im->w);
  int coefH = h/(im->h);
    nim->w = w;
    nim->h = h;
    nim->tab = malloc(w*h);
  int i = 0,j = 0,g = 0,k = 0, cpt = 0,iW = im->w,iH = im->h;
    for(i = 0; i < iH; i++) {
        for(j = 0; j < iW; j++) {
            k = kij(i,j,iW);
              g  = 1;
              while(g <= coefW) {
                g++;
            printf("i: %d j: %d k: %d cpt: %d g: %d tab.R: %d\n",i,j,k,cpt,g,tab[k].G);
            nim->tab[cpt].R = tab[k].R;
            nim->tab[cpt].G = tab[k].G;
            nim->tab[cpt].B = tab[k].B;
            cpt++;
        }
      }
      printf("  --------------------\n");
    }
    im->h = nim->h;
    im->w = nim->w;
    im->tab = nim->tab;
    free(nim);
    return true;
}
  */


bool GrayScale(image* img){
  printf("In GreyScale: \n");
  int k = 0, max = 0, min = 0;
  int mid = 0;
  for(k = 0; k < img->w*img->h; k++){
      max = img->tab[k].R;
      if(img->tab[k].G > max) max = img->tab[k].G;
      if(img->tab[k].B > max) max = img->tab[k].B;
      min = img->tab[k].R;
      if(img->tab[k].G < min) min = img->tab[k].G;
      if(img->tab[k].B < min) max = img->tab[k].B;
      printf("max: %d  min: %d\n",max,min);

      mid = (max+min)/2;
      
      img->tab[k].R = (int)mid;
      img->tab[k].G = (int)mid;
      img->tab[k].B = (int)mid;
    }
  return img;
}

bool save_image(const char* fname, image* im, const char* magic_number) {
  FILE* fdesc = fopen(fname,"w");

  fprintf(fdesc, "%s\n%d %d\n", magic_number, im->w, im->h);
  if(!strcmp(magic_number,"P2") || !strcmp(magic_number,"P3")) fprintf(fdesc, "255\n");
  int i = 0, j = 0, k = 0;
  for(i = 0; i < im->h; i++) {
    for(j = 0; j < im->w; j++) {
      k = kij(i,j,im->w);
        fprintf(fdesc, "%d ",im->tab[k].G);
    }
    fprintf(fdesc, "\n");
  }

  fclose(fdesc);
  return true;
}

int main () {
 image* img2 = load_image_P2("im_P2"); ascii_print(img2,G," .*&&#");
 printf("-------------------------------------------\n\n");
 img2 = PivotD(img2); 
 img2 = PivotG(img2); 
 //img2 = PivotD(img2); 
 ascii_print(img2,G," .*&&#");
 //save_image("maintenant",img2,"P2");
 //GrayScale(img2);ascii_print(img2,G," .*&&#");
//  image* img3 = load_image_P3("im_P3"); ascii_print(img3,G," .-+=*&#");free(img3);
//  image* img1 = load_image_P1("im_P1"); ascii_print(img1,G," .-+=*&#");
//  image* img4 = load_image_P4("im_P4"); //ascii_print(img4,G," .-+=*&#");free(img4);
  return EXIT_SUCCESS;
}

