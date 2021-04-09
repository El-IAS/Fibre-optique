#include "Hachage.h"
#include <math.h>
#define MA 10
#define A (sqrt(5)-1)/2 

int fonctionClef(int x,int y){
    return y + (x + y)*(x + y + 1)/2;
}


int fonctionHachage(int k){
    return (int)(MA*(k*A - (int)k*A));
} 

Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y){
   int clef = fonctionClef(x,y);
   int emp = fonctionHachage(clef);
   CellNoeud *listeNoeuds = H->TabDeNeouds[emp];
   while(listeNoeuds){
       Noeud *noeud = listeNoeuds->nd;
       if (noeud->x == x && noeud->y == y){
           return noeud;
       }
       listeNoeuds = listeNoeuds->suiv ;
   }


Noeud *new_noeud = (Noeud*)malloc(sizeof(Noeud));
    new_noeud->x = x ;
    new_noeud->y = y ;
    new_noeud->num = R->nbNoeuds + 1 ;
    new_noeud->voisins = NULL ;
    R->nbNoeuds++ ;
   H->nbNoeuds += 1;
   CellNoeud *CellNoeudAjout = (CellNoeud*)malloc(sizeof(CellNoeud));
   CellNoeudAjout->nd = new_noeud ;
   CellNoeudAjout->suiv = H->TabDeNeouds[emp] ;
   H->TabDeNeouds[emp] = CellNoeudAjout ; 

   return new_noeud ;
}


Reseau* reconstitueReseauHachage(Chaines *C, int M){
    Reseau *R = (Reseau*)malloc(sizeof(Reseau));
    R->nbNoeuds = 0 ;
    R->noeuds = (CellNoeud*)malloc(sizeof(CellNoeud));
    R->commodites = (CellCommodite*)malloc(sizeof(CellCommodite));
    TableHachage *H = (TableHachage*)malloc(sizeof(TableHachage));
    H->tailleMax = M;
    H->nbNoeuds = 0;
    CellNoeud **TabDeNoeud = (CellNoeud**)malloc(M*sizeof(CellNoeud*));
    for(int i = 0;i<M;i++){
        TabDeNoeud[i] = NULL;
    }
    H->TabDeNeouds = TabDeNoeud;
    CellChaine *chaines = C->chaines;

    
    // Voisin ?


    //
 
}
