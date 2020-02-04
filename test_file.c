#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "pile.h"
#include "file.h"

int main (int argc, char**argv)
{
    pfile_t p = creer_file();
    char c;
    printf("Regle :\n  q : quit\n  v: fileVide?\n  p: filePleine?\n  d: defiler\n  e: enfiler\n  h: help\n");
    scanf("%c",&c);
    while (c!='q') {
        if (c == 'v') {
            printf("File %s\n", ( file_vide(p)==1 ? "vide" : "non vide" ));
        } else if (c == 'p') {
            printf("File %s\n", ( file_pleine(p)==1 ? "pleine" : "non pleine" ));
        } else if (c == 'd') {
            if (file_vide(p) == 1) {
                printf("File vide\n");
            } else {
                afficher_arbre((Arbre_t)defiler(p),0);
            }
        } else if (c == 'e') {
            if (file_pleine(p) == 1) {
                printf("File pleine\n");
            } else {
                noeud_t np;
                np.cle = p->queue;
                np.fgauche=NULL;
                np.fdroite=NULL;
                enfiler(p,&np);
            }
        } else if (c == 'h'){
            printf("Regle :\n  q : quit\n  v: fileVide?\n  p: filePleine?\n  d: defiler\n  e: enfiler\n  h: help\n");
        }
        scanf("%c",&c);
    }

    detruire_file(p);
    return 0;
}
