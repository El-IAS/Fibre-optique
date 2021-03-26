#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Reseau.h"



Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
      CellNoeud *noeuds = R->noeuds;
      while(noeuds){
          Noeud *nd = noeuds->nd;
          if (nd){
                if (nd->x == x && nd->y == y){
                    return nd;
               }
         }
      noeuds=noeuds->suiv;
    }
    // 
    Noeud *new_noeud = (Noeud*)malloc(sizeof(CellNoeud));
    new_noeud->x = x ;
    new_noeud->y = y ;
    new_noeud->num = R->nbNoeuds + 1 ;
    new_noeud->voisins = NULL ;
    //
    CellNoeud* new_cell = malloc((sizeof(CellNoeud))) ;
    new_cell->nd = new_noeud ;
    new_cell->suiv = NULL ;
    noeuds = new_cell ; 

    R->nbNoeuds++ ;

    return new_noeud ;
}



