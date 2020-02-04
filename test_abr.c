#include <stdio.h>
#include <stdlib.h>

#include "abr.h"

int main (int argc, char**argv)
{
  Arbre_t a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv[1]) ;

  afficher_arbre (a,0) ;

  printf("===========Test Hauteur Arbre=================\n");
  printf("Recurif: %d\n", hauteur_arbre_r(a));
  printf("Non Recursif: %d\n\n", hauteur_arbre_nr(a));

  printf("===========Test parcour largeur===============\n");
  parcourir_arbre_largeur(a);
  printf("\n\n");

  printf("===========Test Nombre Noeud Niveau===========\n");
  afficher_nombre_noeuds_par_niveau(a);
  printf("\n");

  printf("===========Test Nombres Noeuds================\n");
  printf("Recursif: %d\n", nombre_cles_arbre_r(a));
  printf("Non Recursif: %d\n\n", nombre_cles_arbre_nr(a));

  printf("===========Test Clef Min======================\n");
  printf("Cle min: %d\n\n", trouver_cle_min(a));

  printf("===========Test Liste Clef Triee==============\n");
  printf("Recursif : ");
  imprimer_liste_cle_triee_r(a);
  printf("\nNon Recursif : ");
  imprimer_liste_cle_triee_nr(a);
  printf("\n");


}
