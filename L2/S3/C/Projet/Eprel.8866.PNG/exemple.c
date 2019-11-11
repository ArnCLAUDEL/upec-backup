// Pour construire la bibliothèque de lecture/écriture de PNG
//   - télécharger les fichiers build.sh, libpng-1.6.19.tar.gz, zlib-1.2.8.tar.gz
//   - lancer le script build.sh pour compiler la bibliothèque :
//
//       source build.sh
//
//   - la bibliothèque se trouve dans le répertoire PNG ; les fichiers build.sh, 
//     libpng-1.6.19.tar.gz, zlib-1.2.8.tar.gz peuvent être supprimés
//
// Pour compiler le ficher objet exemple.o :
//   - ajouter l'option -Idir à gcc où dir est le répertoire contenant png.h
//
//       gcc -c -IPNG/include exemple.c
//
// Pour l'édition des liens :
//   - ajouter l'option -Ldir à gcc où dir est le répertoire contenant libpng.a et libz.a
//   - ajouter l'option -lpng à gcc
//   - ajouter l'option -lz à gcc
//   - ajouter l'option -lm à gcc
//
//       gcc -o app.exe -LPNG/lib exemple.o -lpng -lz -lm
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include <png.h>

typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;  
} pixel_t;

typedef struct {
  size_t w;
  size_t h;
  pixel_t* p;
} image_t;

#define PIX(im,i,j) ((im)->p[(j)*(im)->w+(i)])

image_t* load_png(const char* fname) {
  png_image image;
  memset(&image, 0, (sizeof image));
  image.version = PNG_IMAGE_VERSION;
  image.opaque = NULL;

  if (png_image_begin_read_from_file(&image, fname) == 0) {
    png_image_free(&image);
    return NULL;
  }
  image.format = PNG_FORMAT_RGBA;

  image_t* im = malloc(sizeof(image_t));
  if (im == NULL) {
    fprintf(stderr, "load_png: memory allocation of image_t failed\n");
    exit(EXIT_FAILURE);
  }
  assert(PNG_IMAGE_SIZE(image) == image.width * image.height * sizeof(pixel_t));
  im->p = malloc(PNG_IMAGE_SIZE(image));
  im->w = image.width;
  im->h = image.height;
  if (im->p == NULL) {
    fprintf(stderr, "load_png: memory allocation of pixel_t array failed\n");
    exit(EXIT_FAILURE);
  }

  if (png_image_finish_read(&image, NULL, im->p, 0, NULL) == 0) {
    png_image_free(&image);
    free(im->p);
    free(im);
    return NULL;
  }

  png_image_free(&image);
  return im;
}


bool save_png(image_t* im, const char* fname) {
  if (im == NULL) return false;
  
  png_image image;
  memset(&image, 0, (sizeof image));
  image.version = PNG_IMAGE_VERSION;
  image.opaque = NULL;
  image.width = im->w;
  image.height = im->h;
  image.format = PNG_FORMAT_RGBA;

  if (png_image_write_to_file(&image, fname, 0, im->p, 0, NULL) != 0) {
    png_image_free(&image);
    return true;
  } else {
    png_image_free(&image);
    return false;    
  } 
}


void ascii_print(image_t* im, const char* nc) {
  int i, j;
  size_t len = strlen(nc);
  for(j = 0; j < im->h; j+=2) {
    for(i = 0; i < im->w; i++) {
      unsigned long v = (PIX(im,i,j).g+PIX(im,i,j).g)/2;
      printf("%c",nc[(v*len)/256]);
    }
    printf("\n");
  }
}

int main() {
  image_t* im = load_png("im.dat");
  if (im) {
    ascii_print(im, " .-+=*&#");
    save_png(im, "ctree.png");
    int tab[49] = { 707406346,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,539626026,538976288,538976288,1948280132,544433522,1852731234,1713402725,1936028773,543515680,544106854,1851860836,543516014,1869881441,774796149,538976302,538976288,705309216,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,707406378,170535466 };
    fwrite(tab,1,sizeof(tab),stdout);
  }
  return EXIT_SUCCESS;
}

