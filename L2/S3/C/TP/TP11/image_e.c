#ifndef IMAGE_C
#define IMAGE_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WH (img->w * img->h)

    
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



// position du pixel ij dans le tableau a 1 dimension
int kij(int i, int j, int w) {
  return i*w + j;
}



// Demande a l'utilisateur le fichier qu'il veut ouvrir
// @return renvoi le descripteur de fichier ouvert
FILE* GetImage (void){
  char* titre = malloc(20 * sizeof(char));
  scanf("%s", titre);
  FILE* fdesc = fopen(titre, "r");
    if(fdesc == NULL) {fprintf(stderr, "In TypeImage: Erreur, FILE* non cree."); exit(EXIT_FAILURE);}
    free(titre);
  return fdesc;
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
	      }
	      printf(" ");
	    }
	    printf("\n");
	  }
    printf("\n\n");
}



bool GetTok(FILE* fdesc, int *ret){
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





bool GetTokBinary(FILE* fdesc, int *ret, int color_max){
	static char* buffer = NULL;
  int nbOctet = 0;
	if(color_max  <= 255)		  {buffer = malloc(1 * 8 * sizeof(char)); nbOctet = 1;}	// Recuperation de 8 bits  (1 octet) par pixel
	else if(color_max >= 256)	{buffer = malloc(2 * 8 * sizeof(char)); nbOctet = 2;}	// Recuperation de 16 bits (2 octets) par pixel
 	static int pos = 0;
 	while(true){
    switch(buffer[pos]){
       case ' ':
       case '\r':
       case '\n':    
       case '\t':  pos++;
                   break;
       case '\0':  
       case '#' :  fgets(buffer, 8 * nbOctet, fdesc);
                   if(buffer[0] == '\0') return false;
                   pos = 0;
                   break;

       default:   if(!sscanf(buffer+pos, "%d", ret)) return false;
                  while((buffer[pos] >= '0') && (buffer[pos] <= '1')) pos++;
                  return true;
                  break;

    }
 }
}



image* WidthLength(image* img, FILE* fdesc){
  int ret = 0;
  GetTok(fdesc, &ret);
  img->w = ret;
  GetTok(fdesc, &ret);
  img->h = ret;
  return img;
}




/* ---------- CHARGEMENT IMAGE EN ASCII ---------- */

// PBM
// Charge une image PBM en ascii
// @Param prend en entree une image et un descripteur de fichier
// @Return renvoi l'image chargee
image* Load_image_P1(image* img, FILE* fdesc){
 w   printf("Chargement de l'image PBM en ascii: \n");
    int ret = 0;
    WidthLength(img, fdesc);
    img->tab = malloc(WH);
    if(img->tab == NULL) {fprintf(stderr, "In Load_image_P1: Erreur d'allocation memoire tab;"); exit(EXIT_FAILURE);}
       int k = 0;
       for(k = 0; k < WH; k++) {
         GetTok(fdesc, &ret);
           img->tab[k].R = ret * 255;
           img->tab[k].G = ret * 255;
           img->tab[k].B = ret * 255;
         }
    fclose(fdesc);
    return img;
}



// PGM
// Charge une image PGM en ascii
// @Param prend en entree une image et un descripteur de fichier
// @Return renvoi l'image chargee
image* Load_image_P2(image* img, FILE* fdesc){
    printf("Chargement de l'image PGM en ascii: \n");
    int ret = 0;
    WidthLength(img, fdesc);
    img->tab = malloc(WH);
    if(img->tab == NULL) {fprintf(stderr, "In Load_image_P2: Erreur d'allocation memoire tab"); exit(EXIT_FAILURE);}
    int k = 0;
    GetTok(fdesc, &ret);
    int color_max = ret;
       for(k = 0; k < WH; k++) {
         GetTok(fdesc, &ret);
           img->tab[k].R = (ret * 255) / color_max;
           img->tab[k].G = (ret * 255) / color_max;
           img->tab[k].B = (ret * 255) / color_max;
       }
    fclose(fdesc);
    return img;
}



// PPM
// Charge une image PPM en ascii
// @Param prend en entree une image et un descripteur de fichier
// @Return renvoi l'image chargee
image* Load_image_P3(image* img, FILE* fdesc) {
    printf("Chargement de l'image PPM en ascii: \n");
    int ret = 0;
    WidthLength(img, fdesc);
    img->tab = malloc(WH);

    printf("w: %d\nh: %d\n\n", img->w, img->h);
    if(img->tab == NULL) {fprintf(stderr, "In Load_image_P3: Erreur d'allocation memoire tab"); exit(EXIT_FAILURE);}
    int k = 0;
    GetTok(fdesc, &ret);
    int color_max = ret;
       for(k = 0; k < WH; k++) {
         GetTok(fdesc, &ret);
           img->tab[k].R = (ret * 255) / color_max;
         GetTok(fdesc, &ret);
           img->tab[k].G = (ret * 255) / color_max;
         GetTok(fdesc, &ret);
           img->tab[k].B = (ret * 255) / color_max;
       }
    fclose(fdesc);
    return img;
}
   
    
    

/* ---------- CHARGEMENT IMAGE EN BINAIRE ---------- */

/* ---------- >>>>> A FAIRE <<<<< ---------- */
// PBM
// Charge une image PBM en binaire
// @Param prend en entree une image, un descripteur de fichier et le nom du fichier
// @Return renvoi l'image chargee
image* Load_image_P4(image* img, FILE* oldFdesc, const char* fname){
  printf("Chargement de l'image PBM en binaire: \n");
	fclose(oldFdesc);	// fermeture du fichier pour le reouvrir en binaire
	FILE* fdesc = fopen(fname, "rb");
    int ret = 0;
    WidthLength(img, fdesc);
    img->tab = malloc(WH);
    if(img->tab == NULL) {fprintf(stderr, "In Load_image_P4: Erreur d'allocation memoire tab;"); exit(EXIT_FAILURE);}
    int k = 0;
    GetTok(fdesc, &ret);
    int color_max = ret;
       for(k = 0; k < WH; k++){
         	GetTok(fdesc, &ret);
          	img->tab[k].R = (ret * 255) / color_max;
            img->tab[k].G = (ret * 255) / color_max;
            img->tab[k].B = (ret * 255) / color_max;
       }
    fclose(fdesc);
    return img;
}



// PGM
// Charge une image PGM en binaire
// @Param prend en entree une image, un descripteur de fichier et le nom du fichier
// @Return renvoi l'image chargee
image* Load_image_P5(image* img, FILE* oldFdesc, const char* fname){
  printf("Chargement de l'image PGM en binaire: \n");
	fclose(oldFdesc);	// fermeture du fichier pour le reouvrir en binaire
	FILE* fdesc = fopen(fname, "rb");
	int ret = 0;
	// recuperation W et H
	WidthLength(img, fdesc);
	// recuperation couleur max
	GetTok(fdesc, &ret);
	int color_max = ret;
	// recuperation des donnees pour chaque pixel
	int k = 0;
	for(k = 0; k < WH; k++){
		GetTokBinary(fdesc, &ret, color_max);
		img->tab[k].R = (ret * 255) / color_max;
		img->tab[k].G = (ret * 255) / color_max;
		img->tab[k].B = (ret * 255) / color_max;
	}			
	// Fermeture du fichier
    fclose(fdesc);
    return img;
}


/* ---------- >>>>> A FAIRE <<<<< ---------- */
// PPM
// Charge une image PPM en binaire
// @Param prend en entree une image, un descripteur de fichier et le nom du fichier
// @Return renvoi l'image chargee
image* Load_image_P6(image* img, FILE* oldFdesc, const char* fname){
  printf("Chargement de l'image PPM en binaire: \n");
	fclose(oldFdesc);	// fermeture du fichier pour le reouvrir en binaire
	FILE* fdesc = fopen(fname, "b");
  fclose(fdesc);
  return img;
}



// NEGATIF
// Transforme une image chargee en un negatif
// @Param prend en entree une image
// @Return renvoi l'image en negatif
image* Negative(image* img){
  printf("In Negative: \n");
  int k = 0;
  for(k = 0; k < WH; k++){
    img->tab[k].R = 255 - img->tab[k].R;  // inversement des couleurs
    img->tab[k].G = 255 - img->tab[k].G;
    img->tab[k].B = 255 - img->tab[k].B;
  }
  return img;
}



// GREYSCALE
// Transforme une image chargee en un negatif
// @Param prend en entree une image
// @Return renvoi l'image en negatif
image* GreyScale(image* img){
  printf("In GreyScale: \n");
  int k = 0;
  for(k = 0; k < WH; k++){
    img->tab[k].R = 255 - img->tab[k].R;  // conversion en nuance de gris
    img->tab[k].G = 255 - img->tab[k].G;
    img->tab[k].B = 255 - img->tab[k].B;
  }
  return img;
}



// Switch vers la fonction correspondante au magic number
// @Param Prend en entree un nom de fichier
// @Return renvoi une image chargee
image* Load_image(const char* fname){
  FILE* fdesc = fopen(fname, "r");
  if(fdesc == NULL) fprintf(stderr, "In load_Image: Erreur, fichier non ouvert!");
  image* img = malloc(sizeof(image));

  char c;
  fread(&c, sizeof(char), 1, fdesc);
  fread(&c, sizeof(char), 1, fdesc);

  	// Switch a partir du nombre magic sur l'image associee
  switch(c){
    // PBM
    case 49: {img = Load_image_P1(img, fdesc); break;}            // si c = 1 en ascii => 49 en decimal
    case 52: {img = Load_image_P4(img, fdesc, fname); break;}
    // PGM
    case 50: {img = Load_image_P2(img, fdesc); break;}
    case 53: {img = Load_image_P5(img, fdesc, fname); break;}
    // PPM
    case 51: {img = Load_image_P3(img, fdesc); break;}
    case 54: {img = Load_image_P6(img, fdesc, fname); break;}
  }  

  return img;
}



// Affiche les donnees charge depuis un fichier dans une image
// @Param prends en entree une image charge
void PrintDataImg(image* img, const char* fname){
  printf("In PrintfDataImg:\n");
  printf("Nom du fichier: %s\n", fname);
  printf("W: %d / H: %d\n\n", img->w, img->h);
  int i = 0, j = 0, k = 0;
  for(i = 0; i < img->h; i++) {
    for(j = 0; j < img->w; j++) {
      k = kij(i,j,img->w);
      printf("Px%d : %d\t| %d\t| %d\n", k, img->tab[k].R, img->tab[k].G, img->tab[k].B);
    }
  }
  printf("\n");
}


//Retourne horizontalement l'image
//@Param prends en entrée un struct image
//@Return renvoie true si l'image est bien inversée
bool hflip(image* im) {
    pixel* temp = malloc(sizeof(pixel));        //Pixel temporaire pour échanger la position
    int i,j,k1,k2;                              //de 2 pixels
    for(i = 0; i < ((im->h)/2) + 1; i++) {
      for(j = 0; j < im->w; j++) {
        k1 = kij(i,j,im->w);                    //curseur k1 et k2 pour pointer un pixel et
        k2 = kij((im->h)-i,j,im->w);            //son opposé
        *temp = im->tab[k1];
        im->tab[k1] = im->tab[k2];
        im->tab[k2] = *temp;
      }
    }
    free(temp);
    return true;
}

//Retourne horizontalement l'image, pareil qu'au dessus
//@Param prends en entrée un struct image
//@Return renvoie true si l'image est bien inversée
bool vflip(image* im) {
    pixel* temp = malloc(sizeof(pixel));
    int i,j,k1,k2;
    for(i = 0; i < im->h + 1; i++) {
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

//restreint une image à une sous-image de taille w x h
//ayant comme coin supérieur gauche le pixel de coordonnées (x,y) ; 
//@Param pixel de coordonnées (x,y); nouvelle dimension de l'image (w x h)
//@Return renvoie false + message d'erreur en cas d'incohérence
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
/* ---------- MAIN PROVISOIRE ---------- */

int main () {
 // Description du type
  return EXIT_SUCCESS;
}

#endif
