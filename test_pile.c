#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "pile.h"
#include "file.h"

int main (int argc, char**argv)
{
    ppile_t p = creer_pile();
    char c;
    printf("Regle :\n  q : quit\n  v: pileVide?\n  p: pilePleine?\n  d: depiler\n  e: empiler\n  h: help\n");
    scanf("%c",&c);
    while (c!='q') {
        if (c == 'v') {
            printf("Pile %s\n", ( pile_vide(p)==1 ? "vide" : "non vide" ));
        } else if (c == 'p') {
            printf("Pile %s\n", ( pile_pleine(p)==1 ? "pleine" : "non pleine" ));
        } else if (c == 'd') {
            if (pile_vide(p) == 1) {
                printf("Pile vide\n");
            } else {
                afficher_arbre((Arbre_t)depiler(p),0);
            }
        } else if (c == 'e') {
            if (pile_pleine(p) == 1) {
                printf("Pile pleine\n");
            } else {
                noeud_t np;
                np.cle = p->sommet;
                np.fgauche=NULL;
                np.fdroite=NULL;
                empiler(p,&np);
            }
        } else if (c == 'h'){
            printf("Regle :\n  q : quit\n  v: pileVide?\n  p: pilePleine?\n  d: depiler\n  e: empiler\n  h: help\n");
        }
        scanf("%c",&c);
    }

    detruire_pile(p);
    return 0;
}
