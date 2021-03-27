#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Reseau.h"
#include "Chaine.h" 



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


Reseau* reconstitueReseauListe(Chaines *C){
   // Preparation du reseau
   Reseau *R = (Reseau*)malloc(sizeof(Reseau));
   R->gamma = C->gamma;
   CellCommodite* temp_commodites = (CellCommodite*)malloc(sizeof(CellCommodite)) ; 
   CellCommodite* commodites = temp_commodites ;
   R->noeuds = (CellNoeud*)malloc(sizeof(CellNoeud));

   CellChaine *chaines = C->chaines;

   Noeud *extrA = (Noeud*)malloc(sizeof(Noeud));
   Noeud *extrB = (Noeud*)malloc(sizeof(Noeud));

   while(chaines){
       CellPoint *points = chaines->points;
       if(points == NULL)    continue ;
      extrA=rechercheCreeNoeudListe(R,points->x,points->y) ;
   
       while(points){
         CellNoeud* voisins = R->noeuds ;
         extrB=rechercheCreeNoeudListe(R,points->x,points->y);
         points = points->suiv;
         // Mettre a jour la liste des voisins
         extrB->voisins = voisins ;
         CellNoeud *precedents = voisins ; 
         while(precedents){
           CellNoeud* voisins_prec = precedents->suiv ;
           while (voisins_prec) { voisins_prec= voisins_prec->suiv ; }
           voisins_prec = (CellNoeud*)malloc(sizeof(CellNoeud)) ;
           voisins_prec->nd = extrB ;
           voisins_prec->suiv = NULL ;
           precedents = precedents->suiv ;
         }
       }
     
       // Ajouter les commodités
       if (temp_commodites==NULL) temp_commodites =  (CellCommodite*)malloc(sizeof(CellCommodite));
       temp_commodites->extrA =extrA ;
       temp_commodites->extrB =extrB ;
       temp_commodites->suiv = NULL ;
       temp_commodites=temp_commodites->suiv ;

     chaines = chaines->suiv ;
   }

   R->commodites = commodites ;

   return R ;

}



int nbCommodites(Reseau *R){
     CellCommodite *commodites = R->commodites;
     int nbc=0;
     while(commodites){
        nbc++;
        commodites = commodites->suiv;
     }
      return nbc;
}


int nbLiaison(Reseau* R)   {
     CellCommodite *commodites = R->commodites;
     int nbc=0;
     while(commodites){
        commodites = commodites->suiv;
     }
      return nbc;
}