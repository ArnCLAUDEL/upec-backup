#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define p 10

typedef struct action {
  char* nom;
  void (*fonction) ();
} action_s;

typedef union item_nu {
  struct menu* fils;
  action_s action;
} item_u;

typedef struct item_ns {
  enum { A, V, M } type;
  item_u carac;
} item_s;


typedef struct menu {
  struct menu* parent;
  char* nom; 
  item_s item[9];
  int item_in;
} menu_s;


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
};

void addMenuAction(menu_s* m, const char* text, void(*f)()) {
    if(m->item_in == 9) {
      fprintf(stderr, "Dans la fonction addMenuAction : Nombre d'item maximal atteint.\n");
      return;
    }
    m->item[m->item_in].type = 'A';
    char* dest = malloc(sizeof(text));
    strcpy(dest, text);
    m->item[m->item_in].carac.action.nom = dest;
    m->item[m->item_in].carac.action.fonction = f;
    m->item_in++;
};


void addSubMenu(menu_s* m, menu_s* sm) {
 
    m->item[m->item_in].carac.fils = sm;
    sm->parent = m;
	m->item[m->item_in].type = 'M';
      m->item_in++;
};

void deleteMenu(menu_s* m) {
	int i;
	if(m->item_in > 0) {
		for(i = 0; i < 9; i++) {
			if(m->item[i].type == 'M') deleteMenu(m->item[i].carac.fils);
		}
	}
	free(m);
};


void launchMenu(menu_s* m) {
	printf("\n%s\n\n",m->nom);
	int i;
	for(i = 0; i < 9; i++) {
		if(m->item[i].type == 'M' ) printf("   %d : %s >\n",i + 1,m->item[i].carac.fils->nom);
		if(m->item[i].type == 'A' ) printf("   %d : %s\n",i + 1,m->item[i].carac.action.nom);
	}
	if(m->parent != NULL){
		 printf("   p : Previous\n");
		 if(m->parent->parent != NULL)	printf("   t : TopMenu\n");
	}
	int ch;
	printf("Entrer votre choix : ");
	char c = getchar();
	getchar();
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
					if(m->item[ch].type == 'A') { 
						m->item[ch].carac.action.fonction();
						launchMenu(m);
					} else if(m->item[ch].type == 'M') {
						launchMenu(m->item[ch].carac.fils);
					}else {
						printf("Choix incorrect. Retour au menu principal, veuillez rééssayer.\n");
					}
					break;
		case 'p': if(m->parent != NULL) {
					launchMenu(m->parent); break;
				} else {
					printf("Ce menu n'a pas de parent.\n");break;
				}
		case 't': while(m->parent != NULL) {
					m = m->parent;
				}
				launchMenu(m); break;
		default: printf("Choix incorrect, veuillez rééssayer.\n"); break;
	}
};

void f1() {
  printf("Functionality 1 is called\n");
}
 
void f2() {
  printf("Functionality 2 is called\n");
}
 
bool cont = true;
 
void quit() {
  cont = false;
}
 
int main() {
  menu_s* m;
  menu_s* sm;
  menu_s* sm1;
 
  m = createMenu("Main menu");
 
  addMenuAction(m,"Apply functionnality 1",f1);
  addMenuAction(m,"Apply functionnality 2",f2);
 
  sm = createMenu("First submenu");
  addMenuAction(sm,"Apply functionnality 2",f2);
  addSubMenu(m,sm);
 
  sm = createMenu("Second submenu");
  addMenuAction(sm,"Apply functionnality 1",f1);
  addSubMenu(m,sm);
 
  sm1 = createMenu("third submenu");
  addMenuAction(sm1,"Apply functionnality 3",f1);
  addSubMenu(sm,sm1);

  addMenuAction(m,"Quit",quit);
  while(cont) launchMenu(m);
  deleteMenu(m);
  return EXIT_SUCCESS;
}
