#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "args.h"
#include "image.h"
#include "menu.h"


menu_s* m;
image* imageC;
char fname[20];
                              // mise en globale des variable pour s'en servir partout
bool res = true;
bool image_ok = false;
bool first = true;

void MenuSaveP1() {
   int x;
  printf("Souhaitez vous modifier le nom de l'image avant de Sauvegarder ? (1:oui | 2:non): "); scanf("%d", &x);
  if(x == 1) {
    printf("Veuillez entrer le nouveau nom: "); scanf("%s", fname);
  }
    BlackWhiteSeuil(imageC,128);
    save_image(fname,imageC,"P1");
}

void MenuSaveP2() {
   int x;
  printf("Souhaitez vous modifier le nom de l'image avant de Sauvegarder ? (1:oui | 2:non): "); scanf("%d", &x);
  if(x == 1) {
    printf("Veuillez entrer le nouveau nom: "); scanf("%s", fname);
  }
    imageC = GrayScale(imageC);
    save_image(fname,imageC,"P2");
}

void MenuSaveP3() {
   int x;
  printf("Souhaitez vous modifier le nom de l'image avant de Sauvegarder ? (1:oui | 2:non): "); scanf("%d", &x);
  if(x == 1) {
    printf("Veuillez entrer le nouveau nom: "); scanf("%s", fname);
  }
    save_image(fname,imageC,"P3");
}


void SaveChoice(){
  int x;
   printf("Souhaitez vous enregistrer l'image actuelle ? (1:oui | 2:non): "); scanf("%d", &x);
  if(x == 1) {
    while(m->parent != NULL) {        
        m = m->parent;
    }
    launchMenu(m->item[0].carac.fils->item[1].carac.fils);
  }
   
    free(imageC);
    image_ok = false;
}

void MenuLoad_image(){
  if(image_ok == true) {
    SaveChoice();
  }
  printf("Entrez le nom du fichier a ouvrir: ");
  scanf("%s", fname);
  imageC = Load_image(fname); 
  if(imageC == NULL) printf("Erreur dans le chargement de l'image, pensez à vérifier l'ortographe.\n   Retour au menu principal.\n");
  else {
    image_ok = true;
    first = false;
  }
}

// Appel la fonction Crop
void MenuCrop(){
  if(image_ok == false) printf("Aucune image chargée, opération impossible. Veuillez charger une image.\n");
  unsigned int x, y, h, w;
  printf("pixel: (x,y)\n");
  printf("Entrez la valeur x du pixel: "); scanf("%d", &x);
  printf("Entrez la valeur y du pixel: "); scanf("%d", &y);
  printf("Entrez la valeur de la nouvelle largeur: "); scanf("%d", &w);
  printf("Entrez la valeur de la nouvelle hauteur: "); scanf("%d", &h);
  if(crop(imageC, x, y, w , h) == false)     printf("Erreur dans Crop\n");
  else printf("Découpage réussie!\n");
} 

// Appel la fonction Grayscale
void MenuGrayScale(){
  if(image_ok == false) {
    printf("\nAucune image chargée, opération impossible. Veuillez charger une image.\n");
    return;
  }
  imageC = GrayScale(imageC); 
}

// Appel la fonction Negative
void MenuNegative(){
  if(image_ok == false) {
    printf("\nAucune image chargée, opération impossible. Veuillez charger une image.\n");
    return;
  }
  if(Negative(imageC) == false)   printf("Erreur dans Negative\n");
}

// Appel la fonction Hflip
void MenuHflip(){
  if(image_ok == false) {
    printf("\nAucune image chargée, opération impossible. Veuillez charger une image.\n");
    return;
  }
  if(hflip(imageC) == false)   printf("Erreur dans Hflip\n");
}

// Appel la fonction Vflip
void MenuVflip(){
  if(image_ok == false) {
    printf("\nAucune image chargée, opération impossible. Veuillez charger une image.\n");
    return;
  }
  if(vflip(imageC) == false)   printf("Erreur dans Vflip\n");
}

// Appel la fonction PrintDataImg
void MenuPrintDataImg(){
  if(image_ok == false) {
    printf("\nAucune image chargée, opération impossible. Veuillez charger une image.\n");
    return;
  }
  PrintDataImg(imageC);
}

void MenuQuit(){
  res = Quit();
}

void MenuResize() {
  unsigned int x,y;
  printf("Entrez la nouvelle largeur souhaitée: "); scanf("%d", &x);
  printf("Entrez la nouvelle hauteur souhaitée: "); scanf("%d", &y);
  imageC = resize(imageC,x,y); printf("Redimension effectuée !\n");
}

void PasFini (void){
  printf("Pas FINI !");
  if(image_ok == false) {
    printf("\nAucune image chargée, opération impossible. Veuillez charger une image.\n");
    return;
  }
}

void MenuHelp(void) {
  Help();
}


void MenuPivotG(void) {
  imageC = PivotG(imageC);
  if(imageC != NULL) printf("Image pivotée avec succès !\n");
}

void MenuPivotD(void) { 
  imageC = PivotD(imageC);
  if(imageC != NULL) printf("Image pivotée avec succès !\n");
}

void MenuBWSeuil() {
  unsigned int x;
  printf("Souhaitez vous utiliser le seuil par défaut ? (1:oui | 2:non): "); scanf("%d", &x);
  if(x == 2) {
    printf("Veuillez entrer le nouveau seuil: "); scanf("%d", &x);
    BlackWhiteSeuil(imageC,x);
  } else {
    BlackWhiteSeuil(imageC,127);
  }
  printf("Convertion en Noir et Blanc (seuil) réussie!\n");
}

void MenuBWMoyenne() {
  BlackWhiteMoyenne(imageC);
  printf("Convertion en Noir et Blanc (moyenne) réussie!\n");
}

void MenuBWMediane() {
  BlackWhiteMediane(imageC);
  printf("Convertion en Noir et Blanc (médiane) réussie!\n");
}


int main(int argc, char** argv) {

 
  menu_s* sm1;
  menu_s* sm2;
 
  m = createMenu("Main menu");
  
  sm1 = createMenu("Fichier");
  addMenuAction(sm1,"Ouvrir", MenuLoad_image);
  sm2 = createMenu("Sauvegarder");
  addMenuAction(sm2, "PBM BINAIRE", PasFini);
  addMenuAction(sm2, "PBM ASCII", MenuSaveP1);
  addMenuAction(sm2, "PPM BINAIRE", PasFini);
  addMenuAction(sm2, "PGM ASCII", MenuSaveP2);
  addMenuAction(sm2, "PPM BINAIRE", PasFini);
  addMenuAction(sm2, "PPM ASCII", MenuSaveP3);
  //addMenuAction(sm2, "PNG", PasFini);
  //addMenuAction(sm2, "BMP", PasFini);
  addSubMenu(sm1, sm2);
  addMenuAction(sm1, "Information", MenuPrintDataImg);
  addMenuAction(sm1, "Quitter", MenuQuit);
  addSubMenu(m,sm1);
  
  sm1 = createMenu("Couleur");
  addMenuAction(sm1, "Negatif", MenuNegative);
  addMenuAction(sm1, "Niveau de gris", MenuGrayScale);
  sm2 = createMenu("Noir et blanc");
  addMenuAction(sm2, "Seuil", MenuBWSeuil);
  addMenuAction(sm2, "Moyenne", MenuBWMoyenne);
  addMenuAction(sm2, "Median", MenuBWMediane);
  addSubMenu(sm1,sm2);
  addSubMenu(m,sm1);

  sm1 = createMenu("Transformation");
  addMenuAction(sm1, "Pivot gauche de 90°", MenuPivotG);
  addMenuAction(sm1, "Pivot droit de 90°", MenuPivotD);
  addMenuAction(sm1, "Retourner horizontal", MenuHflip);
  addMenuAction(sm1, "Retourner verticalement", MenuVflip);
  addMenuAction(sm1, "Redimensionner", MenuResize);
  addMenuAction(sm1, "Decouper", MenuCrop);
  addSubMenu(m,sm1);

  addMenuAction(m, "Help", MenuHelp);
    system("clear");
    printf("Programme '%s' lancé avec %d option(s) :\n", argv[0], argc-1);
    option_t* opt = NOOPTION;
    opt = CreateOption(opt);
    ProcessArguments(opt, argc, argv);

  while(res) launchMenu(m);
  deleteMenu(m);

  return EXIT_SUCCESS;
}
  /* // Description du type
  image* img = Load_image("im_p2");

  PrintDataImg(img, "im_p2");
  ascii_print(img, B, " .-%#");

  PrintDataImg(Negative(img), "im_p2");
  ascii_print(img, B, " .-%#");
  */
