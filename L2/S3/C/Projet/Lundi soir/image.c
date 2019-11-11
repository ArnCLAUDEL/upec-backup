#ifndef IMAGE_C
#define IMAGE_C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "image.h"

extern image* imageC;
extern char fname[20];
extern bool first;
extern bool image_ok;
// position du pixel ij dans le tableau a 1 dimension
int kij(int i, int j, int w) {
  return (i*w) + j;
}

void QuickSort(int tab[], int debut, int fin){
    int gauche = debut-1;
    int droite = fin+1;
    const int pivot = tab[debut];
    /* Si le tableau est de longueur nulle, il n'y a rien à faire. */
    if(debut >= fin)
        return;
    /* Sinon, on parcourt le tableau, une fois de droite à gauche, et
    une autre de gauche à droite, à la recherche d'éléments mal placés,
    que l'on permute. Si les deux parcours se croisent, on arrête. */
    while(1)
    {
        do droite--; while(tab[droite] > pivot);
        do gauche++; while(tab[gauche] < pivot);

        if(gauche < droite){
            int temp = tab[gauche];
            tab[gauche] = tab[droite];
            tab[droite] = temp;
        }else break;
    }
    /* Maintenant, tous les éléments inférieurs au pivot sont avant ceux supérieurs au pivot. On a donc deux groupes de cases à trier. On utilise pour cela... la méthode quickSort elle-même ! */
    QuickSort(tab, debut, droite);
    QuickSort(tab, droite+1, fin);
}


// Demande a l'utilisateur le fichier qu'il veut ouvrir
// @return renvoi le descripteur de fichier ouvert
FILE* GetImage (void){
  char* titre = malloc(20 * sizeof(char));
  scanf("%s", titre);
  FILE* fdesc = fopen(titre, "r");
  if(fdesc == NULL) {fprintf(stderr, "In GetImage: Erreur, FILE* non cree."); exit(EXIT_FAILURE);}
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
  if(color_max  <= 255)     {buffer = malloc(1 * 8 * sizeof(char)); nbOctet = 1;} // tableau de 8 bits  (1 octet) par pixel
  else                      {buffer = malloc(2 * 8 * sizeof(char)); nbOctet = 2;} // tableau de 16 bits (2 octets) par pixel
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
bool Load_image_P1(image* img, const char* fname){
    FILE* fdesc = fopen(fname,"r");
    fseek(fdesc,2,SEEK_SET);
    printf("Chargement de l'image PBM en ascii: \n");
    int ret = 0;
    WidthLength(img, fdesc);
    if(img->w == 0 || img->h == 0)  return false;
    if(first) img->tab = malloc(WH);
    if(img->tab == NULL) {fprintf(stderr, "In Load_image_P1: Erreur d'allocation memoire tab\n"); exit(EXIT_FAILURE);}
       int k = 0;
       for(k = 0; k < WH; k++) {
         GetTok(fdesc, &ret);
           img->tab[k].R = ret * 255;
           img->tab[k].G = ret * 255;
           img->tab[k].B = ret * 255;
         }
    fclose(fdesc);
    return true;
}



// PGM
// Charge une image PGM en ascii
// @Param prend en entree une image et un descripteur de fichier
// @Return renvoi l'image chargee
bool Load_image_P2(image* img, const char* fname){
    printf("Chargement de l'image PGM en ascii: \n");
    FILE* fdesc = fopen(fname,"r");
    fseek(fdesc,2,SEEK_SET);
    int ret = 0;
    WidthLength(img, fdesc);
    if(img->w == 0 || img->h == 0)  return false;
    if(first) img->tab = malloc(WH);
    if(img->tab == NULL) {fprintf(stderr, "In Load_image_P2: Erreur d'allocation memoire tab\n"); exit(EXIT_FAILURE);}
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
    return true;
}



// PPM
// Charge une image PPM en ascii
// @Param prend en entree une image et un descripteur de fichier
// @Return renvoi l'image chargee
bool Load_image_P3(image* img, const char* fname) {
    printf("Chargement de l'image PPM en ascii: \n");
    FILE* fdesc = fopen(fname,"r");
    fseek(fdesc,2,SEEK_SET);
    int ret = 0;
    WidthLength(img, fdesc);
    if(img->w == 0 || img->h == 0)  return false;
    if(first) img->tab = malloc(WH);
    if(img->tab == NULL) {fprintf(stderr, "In Load_image_P3: Erreur d'allocation memoire tab\n"); exit(EXIT_FAILURE);}
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
    return true;
}
   
    
    

/* ---------- CHARGEMENT IMAGE EN BINAIRE ---------- */

/* ---------- >>>>> A FAIRE <<<<< ---------- */
// PBM
// Charge une image PBM en binaire
// @Param prend en entree une image, un descripteur de fichier et le nom du fichier
// @Return renvoi l'image chargee
bool Load_image_P4(image* img, const char* fname){
  printf("Chargement de l'image PBM en binaire: \n");
  FILE* fdesc = fopen(fname, "rb");
  fseek(fdesc,2,SEEK_SET);
  if(fdesc == NULL) return false;
  int ret = 0;
  // recuperation W et H
  WidthLength(img, fdesc);
  // recuperation couleur max
  GetTok(fdesc, &ret);
  int color_max = ret;
  // recuperation des donnees pour chaque pixel
  int k = 0;
  for(k = 0; k < WH; k++){
    ret = 4;
    GetTokBinary(fdesc, &ret, color_max);
    img->tab[k].R = (ret * 255) / color_max;
    img->tab[k].G = (ret * 255) / color_max;
    img->tab[k].B = (ret * 255) / color_max;
  }     
  // Fermeture du fichier
    fclose(fdesc);
    return true;
}



// PGM
// Charge une image PGM en binaire
// @Param prend en entree une image, un descripteur de fichier et le nom du fichier
// @Return renvoi l'image chargee
bool Load_image_P5(image* img, const char* fname){
  printf("Chargement de l'image PGM en binaire: \n");
  FILE* fdesc = fopen(fname, "rb");
  fseek(fdesc,2,SEEK_SET);
  if(fdesc == NULL) return false;
  int ret = 0;
  // recuperation W et H
  WidthLength(img, fdesc);
  // recuperation couleur max
  GetTok(fdesc, &ret);
  int color_max = ret;
  // recuperation des donnees pour chaque pixel
  int k = 0;
  for(k = 0; k < WH; k++){
    ret = 5;
    GetTokBinary(fdesc, &ret, color_max);
    img->tab[k].R = (ret * 255) / color_max;
    img->tab[k].G = (ret * 255) / color_max;
    img->tab[k].B = (ret * 255) / color_max;
  }     
  // Fermeture du fichier
    fclose(fdesc);
    return true;
}


/* ---------- >>>>> A FAIRE <<<<< ---------- */
// PPM
// Charge une image PPM en binaire
// @Param prend en entree une image, un descripteur de fichier et le nom du fichier
// @Return renvoi l'image chargee
bool Load_image_P6(image* img, const char* fname){
  printf("Chargement de l'image PPM en binaire: \n");
  FILE* fdesc = fopen(fname, "rb");
  fclose(fdesc);
  return true;
}



// NEGATIF
// Transforme une image chargee en un negatif
// @Param prend en entree une image
// @Return renvoi l'image en negatif
bool Negative(image* img){
  printf("In Negative: \n");
  int k = 0;
  for(k = 0; k < WH; k++){
    img->tab[k].R = 255 - img->tab[k].R;  // inversement des couleurs
    img->tab[k].G = 255 - img->tab[k].G;
    img->tab[k].B = 255 - img->tab[k].B;
  }
  return true;
}

// NEGATIF par Arguments
void ArgNegative() {
  Negative(imageC);
}

// GRAYSCALE
// Transforme une image chargee en une nuance de gris
// @Param prend en entree une image
// @Return renvoi l'image en une nuance de gris
image* GrayScale(image* img){
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
      //printf("max: %d  min: %d\n",max,min);

      mid = (max+min)/2;
      
      img->tab[k].R = (int)mid;
      img->tab[k].G = (int)mid;
      img->tab[k].B = (int)mid;
    }
  return img;
}

// GRAYSCALE par Arguments
void ArgGrayScale() {
  imageC = GrayScale(imageC);
}

//Noir et blanc SEUIL
//Convertis l'image en noir et blanc, avec un seuil par défaut de 127
//ou spécifié par l'utilsateur
//@Param prend en entrée une image et le seuil
//@Return true en cas de succès
bool BlackWhiteSeuil(image* img, int seuil){
    printf("In BlackWhiteSeuil:\n");
    GrayScale(img);
    int k,mid;
    for(k = 0; k < WH; k++) {
        mid = img->tab[k].G;
        if(mid <= seuil) mid = 0;
          else  mid = 255;
          img->tab[k].R = mid;
          img->tab[k].G = mid;
          img->tab[k].B = mid;
        //printf("R: %d G: %d B: %d\n",img->tab[k].R,img->tab[k].G,img->tab[k].B);
    }
  return true;
}

// Noir et Blanc Seuil par Arguments
void ArgBlackWhiteSeuil(int seuil) {
  BlackWhiteSeuil(imageC,seuil);
}

//Noir et blanc Moyenne
//Convertis l'image en noir et blanc, avec pour seuil la moyenne des
//niveaux de gris
//@Param prend en entrée une image et le seuil
//@Return true en cas de succès
bool BlackWhiteMoyenne(image* img){
  printf("In BlackWhiteMoyenne:\n");
    GrayScale(img);
    int k,mid,seuil;
    for(k = 0; k < WH; k++) {
      seuil += img->tab[k].G;
    }
    seuil /= WH;
    for(k = 0; k < WH; k++) {
        mid = img->tab[k].G;
        if(mid <= seuil) mid = 0;
          else  mid = 255;
          img->tab[k].R = mid;
          img->tab[k].G = mid;
          img->tab[k].B = mid;
        //printf("R: %d G: %d B: %d\n",img->tab[k].R,img->tab[k].G,img->tab[k].B);
    }
  return true;
}

//Noir et Blanc Moyenne par Arguments
void ArgBlackWhiteAVG() {
  BlackWhiteMoyenne(imageC);
}

//Noir et blanc Mediane
//Convertis l'image en noir et blanc, avec pour seuil la mediane des
//niveaux de gris
//@Param prend en entrée une image et le seuil
//@Return true en cas de succès
bool BlackWhiteMediane(image* img){
    printf("In BlackWhiteMediane:\n");
    GrayScale(img);
    int cpt= 0, med, i= 0;
    int tabMed[WH];
    for(i = 0; i < WH; i++){
      tabMed[i] = img->tab[i].G;
      cpt++;
    }
    QuickSort(tabMed, 0, WH);
    med = tabMed[cpt/2];
    printf("Médiane : %d\n",med);
    BlackWhiteSeuil(imageC,med);
    return true;
}

//Noir et blanc Mediane
void ArgBlackWhiteMediane()  {
  BlackWhiteMediane(imageC);
}

// INVERSEMENT HORIZONTAL
// inverse une image horizontalement a la moitié
// @Param prend en entree une image
// @Return renvoi vrai si tous va bien et false si lallocation n'a pas reussi a creer le pixel de swap>
bool hflip(image* img) {
    printf("In hflip: \n");
    pixel* temp = malloc(sizeof(pixel));  // on cree un pixel temporaire de sauvegarde pour le swap
    if(temp == NULL)  return false;
    int i,j,k1,k2;
    for(i = 0; i < ((img->h)/2) + 1; i++) {
      for(j = 0; j < img->w; j++) {
        k1 = kij(i, j, img->w);
        k2 = kij((img->h)-i-1, j, img->w);
        *temp = img->tab[k1];
        img->tab[k1] = img->tab[k2];
        img->tab[k2] = *temp;
      }
    }
    free(temp);
    return true;
}


// INVERSEMENT HORIZONTAL par Arguments
void Arghflip() {
  hflip(imageC);
}

// INVERSEMENT VERTICAL
// inverse une image verticalement a la moitié
// @Param prend en entree une image
// @Return renvoi vrai si tous va bien et false si l'allocation n'a pas reussi a creer le pixel de swap>
bool vflip(image* img) {
    printf("In vflip: \n");
    pixel* temp = malloc(sizeof(pixel));
    if(temp == NULL)  return false;
    int i,j,k1,k2;
    for(i = 0; i < img->h; i++) {
      for(j = 0; j < ((img->w)/2)+1; j++) {
        k1 = kij(i, j, img->w);
        k2 = kij(i, (img->w)-j-1, img->w);
        *temp = img->tab[k1];
        img->tab[k1] = img->tab[k2];
        img->tab[k2] = *temp;
      }
    }
    free(temp);
    return true; 
}

// INVERSEMENT VERTICAL par Arguments
void Argvflip() {
  vflip(imageC);
}


// CROP
//restreint une image à une sous-image de taille w x h
//ayant comme coin supérieur gauche le pixel de coordonnées (x,y) ; 
//@Param pixel de coordonnées (x,y); nouvelle dimension de l'image (w x h)
//@Return renvoie false + message d'erreur en cas d'incohérence
bool crop(image* img, unsigned int x, unsigned int y, unsigned int w,unsigned int h) {
    printf("In crop:\n");
    if(y>(img->h)||x>(img->w)) {
      printf("Veuillez rentre les coordonnées d'un pixel qui est dans l'image.\n");
      return false;
    }
    if(x<0||y<0) {
      printf("Veuillez rentrer les coordonnées d'un pixel qui est dans l'image.\n");
      return false;
    }
    if(h>(img->h)||w>(img->w)) {
      printf("Les nouvelles dimensions sont incohérentes avec les dimensions initiales de l'image.\n");
      return false;
    }
    if(h !=(img->h)-y||w !=(img->w)-x) {
      printf("Les nouvelles dimensions de l'image sont incohérentes avec le pixel donné.\n");
      return false;
    }
    pixel* tab = malloc(w*h);
    int i,j,k,csr = 0;
    for(i = y; i < img->h; i++) {
      for(j = x; j < img->w; j++) {
        k = kij(i,j,img->w);
            tab[csr].R = img->tab[k].R;
            tab[csr].G = img->tab[k].G;
            tab[csr].B = img->tab[k].B;
        //printf("i:%d j:%d k:%d csr:%d tab:%d im->tab:%d\n",i,j,k,csr,tab[csr].G,img->tab[k].G);
        csr++;
      }
      //printf("---------------------\n"   );
      //csr += y;
    }
    img->h = h;
    img->w = w;
    img->tab = tab;
    return true; 
}

//Découper par Arguments
void ArgCrop( unsigned int x, unsigned int y, unsigned int w, unsigned int h) {
  crop(imageC,x,y,w,h);
}

//Resize
//Redimensionne l'image donnée avec les nouvelles dimensions données.
//@Param Nouvelle dimension de l'image W*H
//@return Renvoie l'image si elle est bien redimensionnée
image* resize(image* im, unsigned int w, unsigned int h) {
  printf("In reisze:\n");
  int iW = im->w,iH = im->h;
 // ascii_print(im,G," .*&&#");
  image* nim = malloc(sizeof(image));
   pixel* tab = malloc(sizeof(im->w*im->h));
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
            // printf("i:%d j:%d k:%d cpt:%d tab:%d\n",i,j,k,cpt,tab[k].G);
            nim->tab[cpt].R = tab[k].R;
            nim->tab[cpt].G = tab[k].G;
            nim->tab[cpt].B = tab[k].B;
            cpt++;
        }
      }
  //    printf("  --------------------\n");
    }
  //          printf("  --------------------\n");
  }
    return nim;
}

//Redimensionner par Arguments
void  ArgResize(unsigned int w, unsigned int h) {
  imageC = resize(imageC,w,h);
}

//PivotD 
//pivote l'image courante de 90° vers la droite
//@Param une image
//@Return vrai si l'image est bien retournée
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

void  ArgReturnRight() {
  imageC = PivotD(imageC);
  printf("Image pivotée avec succès !\n");
}

//PivotG 
//pivote l'image courante de 90° vers la gauche
//@Param une image
//@Return vrai si l'image est bien retournée
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

void  ArgReturnLeft() {
  imageC = PivotG(imageC);
  printf("Image pivotée avec succès !\n");
}

// Switch vers la fonction correspondente au magic number
// @Param Prend en entree un nom de fichier
// @Return renvoi une image chargee
image* Load_image(const char* fname){
  FILE* fdesc = fopen(fname, "r");
  if(fdesc == NULL) return NULL;
  image* img = malloc(sizeof(image));

  char c;
  fread(&c, sizeof(char), 1, fdesc);
  fread(&c, sizeof(char), 1, fdesc);
  fclose(fdesc);
    // Switch a partir du nombre magic sur l'image associee
  switch(c){
    // PBM
    case 49: {Load_image_P1(img, fname); break;}            // si c = 1 en ascii => 49 en decimal
    case 52: {Load_image_P4(img, fname); break;}
    // PGM
    case 50: {Load_image_P2(img, fname); break;}
    case 53: {Load_image_P5(img, fname); break;}
    // PPM
    case 51: {Load_image_P3(img, fname); break;}
    case 54: {Load_image_P6(img, fname); break;}
  }
  return img;
}


//Load_Image par Arguments
void ArgLoad(const char* s) {
  strcpy(fname,s);
  printf("%s ",fname);
  imageC = Load_image(fname);
    if(imageC == NULL) printf("Erreur dans le chargement de l'image, pensez à vérifier l'ortographe.\n   Retour au menu principal.\n");
    else {
      image_ok = true;
      first = false;
  }
}


//SAVE IMAGE
//Enregistre une image dans le fichier fname, au format précisé par magic_number
//@Param Nom du fichier, image à enregistrer et format de l'image
//@Return vrai en cas de succès
bool save_image(const char* fname, image* im, const char* magic_number) {
  FILE* fdesc = fopen(fname,"w");
  fprintf(fdesc, "%s\n%d %d\n", magic_number, im->w, im->h);
  switch(magic_number[1]) {
          int i = 0, j = 0, k = 0;

  case 49: BlackWhiteSeuil(imageC,128);
           for(i = 0; i < im->h; i++) {
            for(j = 0; j < im->w; j++) {
              k = kij(i,j,im->w);
              if(im->tab[k].G == 255)fprintf(fdesc, "0 ");
              if(im->tab[k].G == 0)fprintf(fdesc, "1 ");
            } 
          fprintf(fdesc, "\n");
          }
          break;
  
  case 50: GrayScale(imageC);
           fprintf(fdesc, "255\n");
          for(i = 0; i < im->h; i++) {
            for(j = 0; j < im->w; j++) {
              k = kij(i,j,im->w);
              fprintf(fdesc, "%d ",im->tab[k].G);
            } 
          fprintf(fdesc, "\n");
          }
          break;

  }
  fclose(fdesc);
  printf("Sauvegarde réussie !\n");
  return true;
}

//Save_image par Arguments
void ArgSave(const char* s) {
  char c;
  int i,j;
  for(i = 0; i < strlen(s); i++) {
    c = s[i];
    if(c == '.') j = i;
  }
  c = s[j+2];
  switch(c) {
    case 'b': save_image(s,imageC,"P1"); break;
    case 'g': save_image(s,imageC,"P2"); break;
    case 'p': save_image(s,imageC,"P3"); break;
    default: printf("Attention, extension incorrecte pour la sauvegardede l'image.\n");
  }
}


//Affichage Informations
// Affiche les donnees charge depuis un fichier dan sune image
// @Param prends en entree une image charge
void PrintDataImg(image* img){
  printf("In PrintDataImg:\n");
  printf("Nom du fichier: %s\n", fname);
  printf("W: %d / H: %d\n\n", img->w, img->h);
/*  int i = 0, j = 0, k = 0;
  for(i = 0; i < img->h; i++) {
    for(j = 0; j < img->w; j++) {
      k = kij(i,j,img->w);
    }
  }
*/printf("Affichage de l'image: \n\n");
  ascii_print(img, G, " .-OO#");
  printf("\n");
}

//Affichage Informations par Arguments
void ArgPrintDataImg() {
  PrintDataImg(imageC);
}


#endif