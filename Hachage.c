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

    
    /* J'ai utilisé le meme code qu'on a  dans Reseau.c */ 
    
    Noeud *extrA = (Noeud*)malloc(sizeof(Noeud));
    Noeud *extrB = (Noeud*)malloc(sizeof(Noeud));

    CellCommodite* temp_commodites = (CellCommodite*)malloc(sizeof(CellCommodite)) ; 
    CellCommodite* commodites = temp_commodites ;
   // parcours des chaines
   while(chaines){
      CellPoint *points = chaines->points;
      
      if (points) extrA=rechercheCreeNoeudHachage(R, H, points->x,points->y) ;
        // parcours des points
       while(points){
         CellPoint *init_points = chaines->points;
        // on utilise la fonction précédente
         extrB=rechercheCreeNoeudHachage(R, H, points->x,points->y);
         // Mettre a jour la liste des voisins
        CellNoeud* voisins = (CellNoeud*) malloc(sizeof(CellNoeud)) ;
        CellNoeud* temp_voisins = voisins ;

         if (points->suiv)  {
            mettreAJourVoisins(R, voisins, points->suiv->x, points->suiv->y) ;
         }
        
         
         if (points != init_points) {
            while (init_points->suiv != points)  {
              init_points = init_points->suiv ;
            }

            if (init_points) {
              mettreAJourVoisins(R, voisins, init_points->x, init_points->y) ;
            }

         }




        extrB->voisins = temp_voisins ;
        points = points->suiv;
        
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
   
   /* parcours des cases de la table hachage et on
    contruit R->noeuds */
   CellNoeud* noeud = NULL ; /* = R->noeuds */

   for (int i=0; i<H->tailleMax; i++){
       CellNoeud* n = H->TabDeNeouds[i] ;
       if (n != NULL)   {
           while (n->suiv)  {
               n=n->suiv ;
           }
           n->suiv=noeud ;
           noeud = n ;
       }
   }

    R->noeuds = noeud ;
   return R ;

}
 

