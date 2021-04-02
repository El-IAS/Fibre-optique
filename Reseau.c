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
         CellPoint *init_points = chaines->points;
         extrB=rechercheCreeNoeudListe(R,points->x,points->y);

         // Mettre a jour la liste des voisins
        CellNoeud* voisins = NULL ;
        Noeud* fils = NULL ;
         if (points->suiv)  {
           fils = rechercheCreeNoeudListe(R,points->suiv->x,points->suiv->y);
           voisins = malloc(sizeof(CellNoeud)) ;
           voisins->nd = fils ;
           voisins->suiv = NULL ;        
         }

        Noeud* pere = NULL ;         
         
         if (points != init_points) {
            while (init_points->suiv != points)  {
              init_points = init_points->suiv ;
            }

            if (init_points) {
              pere = rechercheCreeNoeudListe(R,init_points->x,init_points->y);
              if (voisins)  {
                voisins->suiv = malloc(sizeof(CellNoeud)) ;
                voisins->suiv->nd = pere ;
                voisins->suiv->suiv = NULL ;
              }
              else {
                voisins = malloc(sizeof(CellNoeud)) ;
                voisins->nd = pere ;
                voisins->suiv = NULL ;    
              }
            }
         }

        extrB->voisins = voisins ;
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
         if (nd->num > voisins->nd->num)
         res++ ;
         voisins = voisins->suiv ;
       }
       noeuds=noeuds->suiv ;
    }
    return res ;
}





void ecrireReseau(Reseau *R, FILE *f){
    
  fprintf(f,"NbNoeuds : %d\nNbLiaisons: %d\nNbCommodites : %d\nGamma : %d\n\n",R->nbNoeuds,nbLiaison(R),nbCommodites(R),R->gamma) ;
    
    /*Afficher les noeuds*/
   CellNoeud *noeuds1 = R->noeuds;
   while(noeuds1){
        Noeud *nd = noeuds1->nd;
        fprintf(f,"v %d %lf %lf\n",nd->num,nd->x,nd->y);
        noeuds1 = noeuds1->suiv; 
   } 
  fprintf(f, "\n") ;
  /*Afficher les liaisons*/


  CellNoeud* noeuds2 = R->noeuds ;
    while (noeuds2) {
       Noeud* nd = noeuds2->nd ;
       CellNoeud* voisins = nd->voisins ;
       while (voisins)  {
         if (nd->num > voisins->nd->num)  {
           fprintf(f, "l %d %d\n", nd->num, voisins->nd->num) ;
         }
         voisins=voisins->suiv ;
       }
       noeuds2=noeuds2->suiv ;
    }
    fprintf(f, "\n") ;
   /*Afficher les commodites*/
   CellCommodite *commodites = R->commodites;
   while(commodites){
        fprintf(f,"k %d %d\n",commodites->extrA->num,commodites->extrB->num);
        commodites = commodites->suiv;
   }
}
