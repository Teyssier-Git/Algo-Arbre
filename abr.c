#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "file.h"
#include "pile.h"


#define max(a,b) ((a)>(b)?(a):(b))


int feuille (Arbre_t a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if ((a->fgauche == NULL) && (a->fdroite == NULL))
	return 1 ;
      else
	return 0 ;
    }
}

Arbre_t ajouter_noeud (Arbre_t a, Arbre_t n)
{
  /* ajouter le noeud n dans l'arbre a */

  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  else
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  return a ;

}

Arbre_t rechercher_cle_arbre (Arbre_t a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else
    {
      if (a->cle == valeur)
	return a ;
      else
	{
	  if (a->cle < valeur)
	    return rechercher_cle_arbre (a->fdroite, valeur) ;
	  else
	    return rechercher_cle_arbre (a->fgauche, valeur) ;
	}
    }
}

Arbre_t ajouter_cle (Arbre_t a, int cle)
{
  Arbre_t n ;
  Arbre_t ptrouve ;

  /*
     ajout de la clé. Creation du noeud n qu'on insere
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
    {
      n = (Arbre_t) malloc (sizeof(noeud_t)) ;
      n->cle = cle;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      a = ajouter_noeud (a, n) ;
      return a ;
    }
  else
    return a ;
}


Arbre_t lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre_t a = NULL;

  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }

  fclose (f) ;

  return a ;
}

void afficher_arbre (Arbre_t a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */

  int i ;

  if (a != NULL)
      {
	afficher_arbre (a->fdroite,niveau+1) ;

	for (i = 0; i < niveau; i++)
	  printf ("\t") ;
	printf (" %d (%d)\n\n", a->cle, niveau) ;

	afficher_arbre (a->fgauche, niveau+1) ;
      }
  return ;
}


int hauteur_arbre_r (Arbre_t a)
{
    //pnoeud_t p = (pnoeud_t)a;
    if (a == NULL) {
        return -1;
    }
    int c = hauteur_arbre_r(a->fgauche);
    int b = hauteur_arbre_r(a->fdroite);
    if (c > b) {
        return c + 1;
    }
    return b + 1;
}

int hauteur_arbre_nr (Arbre_t a)
{
    int max = 0;
    ppile_t p = creer_pile();
    a->hauteur = 0;
    empiler(p,a);
    while (!pile_vide(p)) {
        Arbre_t cur = depiler(p);

        if (cur->hauteur > max) {
            max = cur->hauteur;
        }

        if (cur->fgauche != NULL) {
            cur->fgauche->hauteur = cur->hauteur + 1;
            empiler(p,cur->fgauche);
        }

        if (cur->fdroite != NULL) {
            cur->fdroite->hauteur = cur->hauteur + 1;
            empiler(p,cur->fdroite);
        }
    }
    return max ;
}


void parcourir_arbre_largeur (Arbre_t a)
{
    pfile_t f = creer_file();
    enfiler(f,a);
    while (!file_vide(f)) {
        Arbre_t cur = defiler(f);
        printf(" %d |",cur->cle);

        if (cur->fgauche != NULL) {
            enfiler(f,cur->fgauche);
        }

        if (cur->fdroite != NULL) {
            enfiler(f,cur->fdroite);
        }
    }
}

void afficher_nombre_noeuds_par_niveau (Arbre_t a)
{
    int niveau=0;
    pfile_t f = creer_file();
    enfiler(f,a);
    a->hauteur = 0;
    int nbNoeud=0;
    while (!file_vide(f)) {
        Arbre_t cur = defiler(f);
        if (cur->hauteur > niveau) {
            printf("Niveau %d: %d\n",niveau,nbNoeud);
            niveau = cur->hauteur;
            nbNoeud=0;
        }
        nbNoeud++;

        if (cur->fgauche != NULL) {
            cur->fgauche->hauteur = cur->hauteur + 1;
            enfiler(f,cur->fgauche);
        }

        if (cur->fdroite != NULL) {
            cur->fdroite->hauteur = cur->hauteur + 1;
            enfiler(f,cur->fdroite);
        }
    }
    printf("Niveau %d: %d\n",niveau,nbNoeud);

}


int nombre_cles_arbre_r (Arbre_t a)
{
  if (a!=NULL) {
      return 1+nombre_cles_arbre_r(a->fgauche)+nombre_cles_arbre_r(a->fdroite);
  }
  return 0 ;
}

int nombre_cles_arbre_nr (Arbre_t a)
{
    int nbNoeud = 0;
    ppile_t p = creer_pile();
    empiler(p,a);
    while (!pile_vide(p)) {
        Arbre_t cur = depiler(p);
        nbNoeud++;

        if (cur->fgauche != NULL) {
            empiler(p,cur->fgauche);
        }

        if (cur->fdroite != NULL) {
            empiler(p,cur->fdroite);
        }
    }
    return nbNoeud;
}

int trouver_cle_min (Arbre_t a)
{
    if (a->fgauche!=NULL) {
        return trouver_cle_min(a->fgauche);
    }
    return a->cle ;
}



void imprimer_liste_cle_triee_r (Arbre_t a)
{
  if (a!=NULL) {
      imprimer_liste_cle_triee_r(a->fgauche);
      printf(" %d |",a->cle);
      imprimer_liste_cle_triee_r(a->fdroite);
  }
}

void imprimer_liste_cle_triee_nr (Arbre_t a)
{
  if(a!=NULL){
    ppile_t pile=creer_pile();
    int fin=0;
    pnoeud_t noeud=a;
    while(fin!=1){
      while(noeud!=NULL){
        empiler(pile,noeud);
        noeud=noeud->fgauche;
      }
      if(pile_vide(pile)){
        fin=1;
      }
      else{
        noeud=depiler(pile);
        printf(" %d |", noeud->cle);
        noeud=noeud->fdroite;
      }
    }
  }
}


int arbre_plein (Arbre_t a)
{
  /*
    a completer
  */

  return 0 ;
}

int arbre_parfait (Arbre_t a)
{
  /*
    a completer
  */

  return 0 ;
}




Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur)
{
  /*
    a completer
  */

  return NULL ;

}

Arbre_t rechercher_cle_inf_arbre (Arbre_t a, int valeur)
{
  /*
    a completer
  */

  return NULL ;

}


Arbre_t detruire_cle_arbre (Arbre_t a, int cle)
{
  /*
    a completer
  */

  return NULL ;
}



Arbre_t intersection_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  /*
    a completer
  */

  return NULL ;

}

Arbre_t union_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  /*
    a completer
  */

  return NULL ;
}
