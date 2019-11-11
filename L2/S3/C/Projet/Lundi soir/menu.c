#ifndef MENU_C
#define MENU_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#define clear system("clear");

extern bool image_ok;
extern bool res;
menu_s* createMenu(const char* text) {
  menu_s* m = malloc(sizeof(menu_s));
  m->parent = NULL;
  m->nom = malloc((strlen(text) + 1) * sizeof(char));
  strcpy(m->nom,text);
  int i;
  for(i = 0; i < 9; i++) {
    m->item[i].type = 'V';
  }
  m->item_in = 0;
  return m;
}

void addMenuAction(menu_s* m, const char* text, void(*f)()) {
    if(m->item_in == 9) {
      fprintf(stderr, "Dans la fonction addMenuAction : Nombre d'item maximal atteint.\n");
      return;
    }
    m->item[m->item_in].type = 'F';
    char* dest = malloc(sizeof(text));
    strcpy(dest, text);
    m->item[m->item_in].carac.action.nom = dest;
    m->item[m->item_in].carac.action.fonction = f;
    m->item_in++;
}


void addSubMenu(menu_s* m, menu_s* sm) {
 
    m->item[m->item_in].carac.fils = sm;
    sm->parent = m;
    m->item[m->item_in].type = 'M';
      m->item_in++;
}

void deleteMenu(menu_s* m) {
/*    int i;
    if(m->item_in > 0) {
        for(i = 0; i < 9; i++) {
            if(m->item[i].type == 'M') deleteMenu(m->item[i].carac.fils);
        }
    }
  */  free(m);
}


void Help(void) {
  system("clear");
  printf("\n -----  ----- MANUEL DE L'UTILISATEUR -----  ----- \n\n");
  printf("Pour accèder à un champs particulier, veuillez entrer le caractère indiqué\n");
  printf("  à gauche de l'option décrite.\n\n");
  printf("   > : Cette flèche signifie que le champs en question est un sous menu.\n");
  printf("   X : Cette croix apparaitra à coté de chaque action, tant qu'aucune image ne sera chargée.\n");
  printf("    Dans ce cas, toute action sera sans conséquence.\n\n");
  printf("Afin de faciliter l'utilisation de cette application, vous pouvez \n");
  printf("   lancer cette application avec les options suivants:\n\n");
  printf("\n  ---- OPTIONS FICHIER ----\n\n");
  printf("   '-i' ou '–open' ou '–load' + (nom_de_fichier) : charge en image courante l'image \n\t contenue dans le fichier de nom nom_de_fichier.\n");
  printf("   '-o' ou '–save' + (nom_de fichier) : sauvegarde l'image courante dans le fichier \n\t de nom nom_de_fichier.\n");
  printf("   '-p' ou '–print' : affiche les informations concernant l'image courante \n\t(nom du fichier d'origine, ");
  printf(" hauteur et largeur en pixels) puis affiche le canal G \n\t de l'image en ASCII Art dans un format respectant ");
  printf(" les dimensions de l'image mais \n\ttenant sur un écran 80 x 60 caractères.\n");
  printf("\n  ---- OPTIONS COULEUR ----\n\n");
  printf("   '-n' ou '–negative' : calcule le négatif de l'image courante. \n");
  printf("   '-g' ou '–grayscale' : convertit l'image en niveau de gris. \n");
  printf("   '-bw' ou '–black_white' + (entier) : convertit l'image courante en noir et blanc \n\t avec entier pour seuil.\n");
  printf("   '-bwAvg' : convertit l'image courante en noir et blanc avec comme seuil la moyenne \n\t des niveaux de gris.\n");
  printf("   '-bwMed' : convertit l'image courante en noir et blanc avec comme seuil la valeur \n\t médiane des niveaux de gris.\n");
  printf("\n  ---- OPTIONS TRANSFORMATION ----\n\n");
  printf("   '-RL' : pivote l'image courante de 90° vers la gauche (sens anti-horaire).\n");
  printf("   '-RR' : pivote l'image courante de 90° vers la droite (sens horaire). \n");
  printf("   '-RH' : retourne l'image courante horizontalement. \n");
  printf("   '-RV' : retourne l'image courante verticalement. \n");
  printf("   '-r' ou '–resize' + (entier1 + entier2) : redimensionne l'image courante suivant \n\t les nouvelles ");
  printf(" dimensions (entier1 x entier2).\n");
  printf("   '-c' ou '–crop' + (entier1 + entier2 + entier3 + entier4) : découpe l'image courante \n\t à partir du pixel de ");
  printf("coordonnées (entier1,entier2) avec \n\tcomme dimensions (entier3 x entier4). \n");
  printf("   '-h' ou '–help' ou '--help' ou '-man' : Affiche l'aide. \n\n");
  printf("A tout moment vous pouvez entrer Q ou q pour QUITTER l'application,\n");
  printf("  et h ou H pour revenir sur cette AIDE.\n");
  printf("\n\n -----  ----- MANUEL DE L'UTILISATEUR -----  ----- \n");
  printf("\nCi-dessus, aide concernant l'utilisation du logiciel ainsi que de ses options.\n\n");
}



bool Quit() {
  res = false;
  return false;
}


void launchMenu(menu_s* m) {
    printf("\n%s\n\n",m->nom);
    int i;
    for(i = 0; i < 9; i++) {
        if(m->item[i].type == 'M' ) {
          printf("   %d : %s >\n",i + 1,m->item[i].carac.fils->nom);
        }
        if(m->item[i].type == 'F' ) {
          if(image_ok == false && strcmp(m->item[i].carac.action.nom,"Ouvrir") != 0 && strcmp(m->item[i].carac.action.nom,"Help") != 0 && strcmp(m->item[i].carac.action.nom,"Quitter") != 0) {
               printf(" X %d : %s\n",i + 1,m->item[i].carac.action.nom);
          } else printf("   %d : %s\n",i + 1,m->item[i].carac.action.nom);
        }
    }
    if(m->parent != NULL){                        //Quand on a un menu sans parent
         printf("   p : Previous\n");
         if(m->parent->parent != NULL)    printf("   t : TopMenu\n");
    }
    int ch;
    printf("\nEntrer votre choix : ");
    char choix[2];
    scanf("%s",choix);                    //je sais pas pourquoi 2 getchar() mais au moins
    //getchar(); 
    char c = choix[0];
    clear;                          //ça marche ^^
    switch (c) {
        case '9':
        case '8':
        case '7':
        case '6':
        case '5':
        case '4':
        case '3':
        case '2':
        case '1': ch = (int)c-49;
                    if(m->item[ch].type == 'F') {
                        m->item[ch].carac.action.fonction();
                    } else if(m->item[ch].type == 'M') {
                        launchMenu(m->item[ch].carac.fils);
                    }else {
                        printf("Choix incorrect, retour au menu principal. Pour accéder au wiki, tapez help \n");
                    }
                    break;
        
        case 'P':
        case 'p': if(m->parent != NULL) {            //pour revenir au menu précédent
                    launchMenu(m->parent); break;
                } else {
                    printf("Ce menu n'a pas de menu précédent.\n");break;
                }
        case 'T':
        case 't': if(m->parent == NULL) {            //pour revenir au tout début
                    printf("Vous etes déjà au menu principal.\n");
                 } else {
                    while(m->parent != NULL) {        
                        m = m->parent;
                    }
                 launchMenu(m);
                 }
                 break;
        case 'Q':
        case 'q': Quit();
                  break;
        case 'H':
        case 'h': Help();
                  launchMenu(m);
                  break;
        default: printf("Choix incorrect, veuillez rééssayer.\n"); break;
    }
}

 
#endif