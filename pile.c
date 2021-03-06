#include <stdlib.h>
#include "abr.h"
#include "pile.h"

ppile_t creer_pile ()
{
    ppile_t p = (ppile_t)malloc(sizeof(pile_t));
    p->sommet = 0;
    return p;
}

int detruire_pile (ppile_t p)
{
    free(p);
    return 0 ;
}

int pile_vide (ppile_t p)
{
    return (p->sommet == 0) ? 1 : 0;
}

int pile_pleine (ppile_t p)
{
     return (p->sommet == MAX_PILE_SIZE) ? 1 : 0 ;
}

pnoeud_t depiler (ppile_t p)
{
    return p->Tab[--(p->sommet)];
}

int empiler (ppile_t p, pnoeud_t pn)
{
      p->Tab[(p->sommet)++] = pn;
      return 0 ;
}
