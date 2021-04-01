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



    Noeud *new_noeud = (Noeud*)malloc(sizeof(Noeud));
    new_noeud->x = x ;
    new_noeud->y = y ;
    new_noeud->num = R->nbNoeuds + 1 ;
    new_noeud->voisins = NULL ;
    //
    CellNoeud* new_cell = malloc((sizeof(CellNoeud))) ;
    new_cell->nd = new_noeud ;
    new_cell->suiv = R->noeuds ;
    R->noeuds = new_cell ; 

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
   R->noeuds = NULL ;
   CellChaine *chaines = C->chaines;

   Noeud *extrA = (Noeud*)malloc(sizeof(Noeud));
   Noeud *extrB = (Noeud*)malloc(sizeof(Noeud));

   while(chaines){
      CellPoint *points = chaines->points;
      
      if (points) extrA=rechercheCreeNoeudListe(R,points->x,points->y) ;

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

int max(int a, int b)  {
  if (a>=b) return a ;
  return b ;
}

int min(int a, int b)  {
  if (a>=b) return b ;
  return a ;
}

////////////////////
int** supprimeRepetution(int tab[][2], int taille) {
  int** res = malloc(taille*sizeof(int*));
  res[0] = malloc(2*sizeof(int)) ;
  int cpt=1 ;
  int u ;
  for (int i=0;i<taille;i++)  {
    int a = tab[i][0] ;
    int b = tab[i][1] ;
    u=0 ;
    for (int j=i+1 ;j<taille;j++) {
      if ( (tab[j][0]==a && tab[j][1]==b) || (tab[j][0]==b && tab[j][1]==a))  {
        u=1 ;
      }
    }
    if (u==0)  {
        res[cpt] = malloc(2*sizeof(int)) ;
        res[cpt][0] = min(a,b) ;
        res[cpt][1] = max(a,b) ;
        cpt++ ;
      }
    }
    for (int i=cpt;i<taille;i++)  {
        free(res[i]) ;
    }
    res[0][0] = taille ; // LA TAILLE INITTIALE
    res[0][1] = cpt - 1 ; // LA TAILLE FINALE, 
  return res ;
}
///////////////
int nbLiaison(Reseau* R)   {
    CellNoeud* noeuds = R->noeuds ;
    int res = 0 ; 
    while (noeuds) {
       Noeud* nd = noeuds->nd ;
       CellNoeud* voisins = nd->voisins ;
       while (voisins)  {
         res++ ;
         voisins = voisins->suiv ;
       }
       noeuds=noeuds->suiv ;
    }
    return (int) res/2 ;
}


