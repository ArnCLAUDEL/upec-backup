#ifndef MENU_H
#define MENU_H

#include <stdbool.h>

typedef struct action { char* nom; void (*fonction) (); } action_s;
typedef union item_nu { struct menu* fils; action_s action; } item_u;
typedef struct item_ns { enum { Ac, V, M } type; item_u carac; } item_s;
typedef struct menu { struct menu* parent; char* nom; item_s item[9]; int item_in; } menu_s;

menu_s* createMenu(const char* text);

void addMenuAction(menu_s* m, const char* text, void(*f)());
void addSubMenu(menu_s* m, menu_s* sm);
void deleteMenu(menu_s* m);
void launchMenu(menu_s* m);

/* FONCTION DE VERIFICATION */ 
void VerificationCreation(menu_s* m);
void VerificationCreationAction(menu_s* m);
void VerificationCreationSousMenu(menu_s* m);

void Help();
bool Quit();

#endif