#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define min(x,y) ((x)>(y)?(y):(x))

// Sortie standard erreur

void* mymalloc(size_t sz) {
  void* test_malloc = malloc(sz);
  if(test_malloc == NULL) {
    fprintf(stderr, "Erreur dans l'allocation de la mémoire\n");
    exit(EXIT_FAILURE);
  }  return test_malloc;
}

FILE* myfopen(const char* fname, const char* mode) {
  FILE* fichier = fopen(fname,mode);
  if(fichier == NULL) {
    fprintf(stderr, "Erreur dans l'ouverture du fichier %s  en mode %s\n",fname,mode);
    exit(EXIT_FAILURE);
  }
  return fichier;
}

//Copie de fichiers

bool display(const char* fname) {
  FILE* fichier = myfopen(fname,"r");
  char* s = mymalloc(11*sizeof(char));
  int x = 0;
  while(x == 0 ) {
    s = fgets(s,12*sizeof(char),fichier);
    if(s ==  NULL){
      x = 1;
    } else {
      printf("%s",s);
    }
  }
  printf("\n");
  fclose(fichier);
  free(s);
  return true; 
}

bool copy(const char* fname1, const char* fname2) {
  FILE* fichier1 = myfopen(fname1,"r");
  FILE* fichier2 = myfopen(fname2,"w");
  char* s = mymalloc(4*sizeof(char));
  int  nbchar;
  do {
    nbchar = fread(s,sizeof(char),4,fichier1);
    fwrite(s,sizeof(char),nbchar,fichier2);
  } while(nbchar != 0);
  fclose(fichier1);
  fclose(fichier2);
  free(s);
  return true; 
}


bool duplicate(const char* fname){
    FILE* fichier1 = myfopen(fname,"r");
    FILE* fichier2 = myfopen(fname,"a");
    char s[5];
    int nbchar = ftell(fichier2);
    int i;
    while(nbchar > 0) {
      i = fread(s,sizeof(char),min(5,nbchar),fichier1);
      fwrite(s,sizeof(char),i,fichier2);
      nbchar -= i;
    }
    fclose(fichier1);
    fclose(fichier2);
    return true;
}


// Recoder les fonctions d'entrée/sortie standard

int myfgetc(const char* fname) {
  FILE* fichier = myfopen(fname,"r");
  unsigned char c;
   int nc;
  fread(&c,sizeof(char),1,fichier);
  nc = (int) c;
  fclose(fichier);
  return nc;
  
}

//Premiers pas en cryptographie

bool cesar(const char* fn_encrypted, const char* fn_original, unsigned char key) {
  FILE* fichier1 = myfopen(fn_original,"r");
  FILE* fichier2 = myfopen(fn_encrypted,"w");
  FILE* fichier3 = myfopen(fn_original,"a");
  int c;
  int nbchar = ftell(fichier3);
  do {
    c = fgetc(fichier1);
    c+=key;
    if(c >= 256) {
      c -= 256;
    }
    fputc(c,fichier2);
    nbchar--;
  }while(nbchar > 0);
  fclose(fichier1);
  fclose(fichier2);
  fclose(fichier3);
  return true;
  
}

bool uncesar(const char* fn_encrypted, const char* fn_original, unsigned char key) {
  FILE* fichier1 = myfopen(fn_original,"r");
  FILE* fichier2 = myfopen(fn_encrypted,"w");
  FILE* fichier3 = myfopen(fn_original,"a");
  int c;
  int nbchar = ftell(fichier3);
  do {
    c = fgetc(fichier1);
    c-=key;
    if(c < 0) c += 256;
    fputc(c,fichier2);
    nbchar--;
  }while(nbchar > 1);
  fclose(fichier1);
  fclose(fichier2);
  fclose(fichier3);
  return true;
}

bool vigenere(const char* fn_encrypted, const char* fn_original, const char* key) {
  FILE* fichier1 = myfopen(fn_original,"r");
  FILE* fichier2 = myfopen(fn_encrypted,"w");
  FILE* fichier3 = myfopen(fn_original,"a");
  int c;
  int i = 0;
  int nbchar = ftell(fichier3);
  do {
    if(i == (int)strlen(key)) i = 0;
    c = fgetc(fichier1);
    c += key[i];
    i++;
    if(c >'z') c -= 26;
    fputc(c,fichier2);
    nbchar--;
  }while(nbchar > 1);
  fclose(fichier1);
  fclose(fichier2);
  fclose(fichier3);
  return true;
}

bool unvigenere(const char* fn_encrypted, const char* fn_original, const char* key) {
  FILE* fichier1 = myfopen(fn_original,"r");
  FILE* fichier2 = myfopen(fn_encrypted,"w");
  FILE* fichier3 = myfopen(fn_original,"a");
  int c;
  int i = 0;
  int nbchar = ftell(fichier3);
  do {
    if(i == (int)strlen(key)) i = 0;
    c = fgetc(fichier1);
    c -= key[i];
    i++;
    if(c <'a') c += 26;
    fputc(c,fichier2);
    nbchar--;
  }while(nbchar > 1);
  fclose(fichier1);
  fclose(fichier2);
  fclose(fichier3);
  return true;
}

//Piste au message

void reveal(const char* fname) {
  FILE* fichierC = myfopen(fname,"r");
  FILE* fichierB = myfopen(fname,"rb");
  FILE* fichierEnd = myfopen(fname,"a");
  int cC,cB,cT;
 // int end = ftell(fichierEnd);
  int i,x = 0;
  while(x < 50) {
    i = 0;
    cB = 0;
    cC = fgetc(fichierC);
    fseek(fichierB,ftell(fichierC)*sizeof(char),SEEK_SET);
    if(cC == '1') {   
              for(;i < 32; i++){
                cT = fgetc(fichierB);
                cB = cB << 1;
                cB += cT;
              }
              fseek(fichierC,cB*sizeof(char),SEEK_SET);
    } else if(cC == '2') {
             for(;i < 32; i++){
                cT = fgetc(fichierB);
                cB = cB << 1;
                cB += cT;
              }
             fseek(fichierC,cB*sizeof(char),SEEK_END);
    } else if(cC == '3') {
             for(;i < 32; i++){
                cT = fgetc(fichierB);
                cB = cB << 1;
                cB += cT;
              }
             fseek(fichierC,cB*sizeof(char),SEEK_CUR);
    } else {
       printf("%c",cC);
    }
    x++;
  }
  fclose(fichierC);
  fclose(fichierB);
  fclose(fichierEnd);
}

int main() {
  // Début
  /*
  char* fname1 = "test1";
  char* fname2 = "test2";
  
  FILE* fichier1 = myfopen(fname1,"w");
  char* s1 = "rien";
  if(fwrite(s1,sizeof(char),4,fichier1) == 4) printf("SUCCESS\n");
  fclose(fichier1);

  FILE* fichier2 = myfopen(fname1,"r");
  char* s2 = mymalloc(sizeof(char)*4);
  fread(s2,sizeof(char),4,fichier2);
  if (ferror(fichier2)) printf("FAILURE\n"); else printf("SUCCESS\n");
  fclose(fichier2);
  
  FILE* fichier3 = myfopen(fname1,"w");
  char* s3 = "Bonjour Bonjour Bonjour";
  fwrite(s3,sizeof(char),25,fichier3);	
  fclose(fichier3);
  display(fname1);
  copy(fname1,fname1);
  display(fname1);
  
  FILE* fichier4 = myfopen(fname1,"w");
  char* s4 = "Bonjour Bonjour Bonjour";
  fwrite(s4,sizeof(char),25,fichier4);	
  fclose(fichier4);
  duplicate(fname1);
  display(fname1);
  
  FILE* fichier5 = myfopen(fname1,"w");
  char* s5 = "Bonjour Bonjour Bonjour";
  fwrite(s5,sizeof(char),25,fichier5);
  fclose(fichier5);
  int x = myfgetc(fname1);
  printf("%d",x);
  */
  
  //Chiffres de César et de Vigenère
  /**/

  char* fname3 = "test3";
  char* fname4 = "test4";
  char* fname5 = "test5";
  
  FILE* fichier6 = myfopen(fname3,"w");
  char* s6 = "Bonjour Bonjour Bonjour";
  fwrite(s6,sizeof(char),25,fichier6);
  fclose(fichier6);
  printf("\nOriginal : ");
  display(fname3);
  printf("\n");
  printf("Cesar : ");
  cesar(fname4,fname3,8);
  display(fname4);
  printf("\n");
  printf("unCesar : ");
  uncesar(fname5,fname4,8);
  display(fname5);
  printf("\n");
  printf("Vigenere : ");
  vigenere(fname4,fname3,"test");
  display(fname4);
  printf("\n");
  printf("unVigenere : ");
  unvigenere(fname5,fname4,"test");
  display(fname5);
  printf("\n");

  
  //Piste au message
 // char* fname6 = "message_secret";
  //reveal(fname6);
 /* FILE* pd = myfopen("message_secret","r");
  int i=0,c = 0;   
  for(;i<15;i++) {
    fread(&c,sizeof(char),1,pd);
    printf("%d ",c);
  }
  printf("\n");
  fclose(pd);*/
  return EXIT_SUCCESS;
}
