#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>    
    // Description du type

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
        case R: printf("%c",ct[(int)strlen(ct) * im->tab[k].R / 255]);break;
        case G: printf("%c",ct[(int)strlen(ct) * im->tab[k].G / 255]);break;
        case B: printf("%d",ct[((int)strlen(ct) * im->tab[k].B) / 255]);break;
        case A: printf("%c",ct[(int)strlen(ct) * im->tab[k].A / 255]);break;
      };
      printf(" ");
    }
    printf("\n");
  }
}

image* load_image(const char* fname) {
    FILE* fichier = fopen(fname,"r");
    image* img = malloc(sizeof(image));
    char* format = malloc(sizeof(char)*2);
    char c;
    fread(format,sizeof(char),2,fichier);
    fseek(fichier,1,SEEK_CUR);
    
    if(strcmp(format,"P3") == 0 ) {
      c = fgetc(fichier);
      while(c == '#') {
      	c = fgetc(fichier);
        while(c != 10) {
        	c = fgetc(fichier);
    	}
        c = fgetc(fichier);
      }

//remplissage du champs w
      int cpt = 1;
      while(c != ' ') {
      	c =  fgetc(fichier);
      	cpt++;
      }
      fseek(fichier,-cpt,SEEK_CUR);
      char* s = malloc(sizeof(char)*cpt);
      fread(s,sizeof(char),cpt,fichier);
      img->w = atoi(s);
      free(s);
    	
//remplissage du champs h
      fseek(fichier,1,SEEK_CUR);
      cpt = 1; 
      while(c != 10) {
      	c = fgetc(fichier);
      	cpt++;
      }
      fseek(fichier,-cpt,SEEK_CUR);
      s = malloc(sizeof(char)*cpt);
      fread(s,sizeof(char),cpt,fichier);
      img->h = atoi(s);
      free(s);

//remplissage du champs intensité max
      c = fgetc(fichier); 
      while(c != 10 && c != ' ') {
      			c = fgetc(fichier);
      		}
      img->tab = malloc((img->w * img->h));
      int i = 0, j = 0, k = 0;

        for(i = 0; i < img->h; i++) {
        	for(j = 0; j < img->w; j++) {
          		k = kij(i,j,img->w);

//remplissage du champs R
           		cpt = 1;
				c = fgetc(fichier); 
				while(c != 10 && c != ' ') {
      				c = fgetc(fichier);
      				cpt++;
      			}
      			fseek(fichier,-cpt,SEEK_CUR);
      			s = malloc(sizeof(char)*cpt);
      			fread(s,sizeof(char),cpt,fichier);
      			img->tab[k].R = atoi(s);
      			free(s);
          while(c == 10 && c == ' ') {
               c = fgetc(fichier);
         }

//remplissage du champs G          	
          		cpt = 1; 
          		c = fgetc(fichier); 
      			while(c != 10 && c != ' ') {
      				c = fgetc(fichier);
      				cpt++;
      			}
      			fseek(fichier,-cpt,SEEK_CUR);
      			s = malloc(sizeof(char)*cpt);
      			fread(s,sizeof(char),cpt,fichier);
      			img->tab[k].G = atoi(s);
      			free(s);
            while(c == 10 && c == ' ') {
            c = fgetc(fichier);
          }

//remplissage du champs B          	
	          	cpt = 1; 
	          	c = fgetc(fichier); 
    	  		while(c != 10 && c != ' ') {
      				c = fgetc(fichier);
      				cpt++;
      			}
      			fseek(fichier,-cpt,SEEK_CUR);
      			s = malloc(sizeof(char)*cpt);
      			fread(s,sizeof(char),cpt,fichier);
      			img->tab[k].B = atoi(s);
      			free(s);
          	fseek(fichier,1,SEEK_CUR);
       		}
          fseek(fichier,-1,SEEK_CUR);
      	}
      	return img;
    }
    return NULL;
}


int main () {
 // Description du type
	image* img = load_image("test");
	int i = 0, j = 0, k = 0;
	for(i = 0; i < 2; i++) {
		for(j = 0; j < 3; j++) {
			k = kij(i,j,img->w);
			printf("%d : %d %d %d  ",k,img->tab[k].R,img->tab[k].G,img->tab[k].B);
		}
	printf("\n");
	}
	//ascii_print(img,B,"test");
	return EXIT_SUCCESS;
}