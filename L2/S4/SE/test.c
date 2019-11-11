#include <stdlib.h> 
#include <stdio.h> 
/* stdlib pour exit(), et stdio pour puts() */

#include <dirent.h> 
/* Pour l'utilisation des dossiers */

#ifndef WIN32
    #include <sys/types.h>
#endif

int main(void)
{


DIR* rep = NULL;
    struct dirent* fichierLu = NULL; /* Déclaration d'un pointeur vers la structure dirent. */
    rep = opendir("Projet");
    if (rep == NULL)
        exit(1);

    fichierLu = readdir(rep); /* On lit le premier répertoire du dossier. */
    fichierLu = readdir(rep); /* On lit le premier répertoire du dossier. */
    
	printf("Le fichier lu s'appelle '%s'", fichierLu->d_name);
    if (closedir(rep) == -1)
        exit(-1);

    return 0;
}
