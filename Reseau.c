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
   R->nbNoeuds = 0 ;
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
        CellNoeud* voisins = (CellNoeud*) malloc(sizeof(CellNoeud)) ;
        CellNoeud* temp_voisins = voisins ;
        Noeud* fils = NULL ;
         if (points->suiv)  {
           fils  = rechercheCreeNoeudListe(R,points->suiv->x,points->suiv->y);
           voisins->nd = malloc(sizeof(Noeud)) ;
           voisins->nd = NULL ; 
           voisins->nd = fils ; 
           printf("%d\n", voisins->nd->num) ;
           voisins->suiv = NULL ;
           printf("%d\n", fils->num) ;
                
         }
        Noeud* pere = NULL ;         
         
         if (points != init_points) {
            while (init_points->suiv != points)  {
              init_points = init_points->suiv ;
            }

            if (init_points) {
              voisins->suiv = malloc(sizeof(CellNoeud)) ;
              voisins = voisins->suiv ;
              voisins->nd = malloc(sizeof(Noeud)) ;
              voisins->nd=NULL ;
              pere = rechercheCreeNoeudListe(R,init_points->x,init_points->y);
              voisins->nd = pere ;
              voisins->suiv = NULL ;                
            }

         }


        CellNoeud* test = temp_voisins ;
        while (test && test->nd)  {
            printf("%d\n", test->nd->num) ;
            printf("HHH\n") ;
            test= test->suiv ;
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


///////////////
int nbLiaison(Reseau* R)   {
    CellNoeud* noeuds = R->noeuds ;
    int res = 0 ; 
    while (noeuds && noeuds->nd && noeuds->nd->voisins) {
       Noeud* nd = noeuds->nd ;
       CellNoeud* voisins = nd->voisins ;
       while (voisins)  {
         if ((nd->num) > (voisins->nd->num))
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
        if (nd) fprintf(f,"v %d %lf %lf\n",nd->num,nd->x,nd->y);
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
