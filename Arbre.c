#include "Arbre.h"



void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax, double* ymax){
     CellChaine *chaines = C->chaines;
     *xmin = chaines->points->x;
     *xmax  = chaines->points->x;
     *ymin = chaines->points->y;
     *ymax = chaines->points->y;
     while(chaines){
         CellPoint* points = chaines->points;
         while(points){
              if(points->x > *xmax && points->y > *ymax){
                     *xmax = points->x;
                     *ymax = points->y;
              }

              if(points->x < *xmin && points->y < *ymin){
                     *xmin = points->x;
                     *ymin = points->y;
                }
         points = points->suiv ;
     }
     chaines = chaines->suiv;
    }
}


ArbreQuat* creerArbreQuat(double xc, double yc, double coteX,double coteY) {

    ArbreQuat* arbre = (ArbreQuat*) malloc(sizeof(ArbreQuat)) ;
    arbre->xc = xc ;
    arbre->yc = yc ;
    arbre->coteX = coteX ;
    arbre->coteY = coteY ;
    arbre->ne = NULL ;
    arbre->no = NULL ;
    arbre->se = NULL ;
    arbre->so = NULL ;
    arbre->noeud = NULL ;
    return arbre ;
}



void insererNoeudArbre(Noeud* n, ArbreQuat** a, ArbreQuat* parent){
 /*Cas Arbre vide */
 if (*a == NULL){
    *a = creerArbreQuat(n->x, n->y, parent->coteX/2, parent->coteY/2) ;
    (*a)->noeud = n ;
    if((*a)->xc < parent->xc && (*a)->yc < parent->yc){
         parent->so = *a;
    }
    if((*a)->xc >= parent->xc && (*a)->yc < parent->yc){
         parent->se = *a;
    }
    if((*a)->xc < parent->xc && (*a)->yc >= parent->yc){
         parent->no = *a;
    }
    if((*a)->xc >= parent->xc && (*a)->yc >= parent->yc){
         parent->ne = *a;
    }
   return ;
} 

 if ((*a)->noeud != NULL)  {
   ArbreQuat* a1 = NULL ;
   ArbreQuat* a2 = NULL ;
   Noeud* noeud = (*a)->noeud ;  
   insererNoeudArbre(n, &a1, a) ;
   insererNoeudArbre(noeud , &a2, a) ;
   (*a)->noeud = NULL ;
   return ; 
  }


if ((*a != NULL) && ((*a)->noeud == NULL)) {
    
    if(n->x < parent->xc && n->y < parent->yc){
        insererNoeudArbre(n,&((*a)->so), *a) ;
    }
    if( n->x >= parent->xc && n->y < parent->yc){
         insererNoeudArbre(n,&((*a)->se), *a) ;
    }
    if( n->x < parent->xc && n->y >= parent->yc) {
        insererNoeudArbre(n,&((*a)->no), *a) ;
    }
    if( n->x >= parent->xc && n->y >= parent->yc){
         insererNoeudArbre(n,&((*a)->ne), *a) ;
    }
   return ;
    
   }

}



Noeud* rechercheCreeNoeudArbre(Reseau* R, ArbreQuat** a, ArbreQuat*parent, double x, double y){
    
    if (*a == NULL){
     Noeud *new_noeud = (Noeud*)malloc(sizeof(Noeud));
     new_noeud->x = x ;
     new_noeud->y = y ;
     new_noeud->num = R->nbNoeuds + 1 ;
     new_noeud->voisins = NULL ;

     insererNoeudArbre(new_noeud, a, parent) ;

    }
    
    if ((*a)->noeud!=NULL){
     /*creer les trucs et tester*/
     Noeud* n = (*a)->noeud ;
     if (n->x==x && n->y==y)  {
          return n ;
     }
     Noeud *new_noeud = (Noeud*)malloc(sizeof(Noeud));
     new_noeud->x = x ;
     new_noeud->y = y ;
     new_noeud->num = R->nbNoeuds + 1 ;
     new_noeud->voisins = NULL ;
     // ?? 
     insererNoeudArbre(new_noeud, a , parent) ;

    }
    
    if ((*a != NULL) && ((*a)->noeud == NULL)){
        if(x < (*a)->xc && y < (*a)->yc){
           rechercheCreeNoeudArbre(R,(*a)->so,a,x,y);
        }
        if(x >= (*a)->xc && y < (*a)->yc){
           rechercheCreeNoeudArbre(R,(*a)->se,a,x,y);
        }
        if(x < (*a)->xc && y >= (*a)->yc){
           rechercheCreeNoeudArbre(R,(*a)->no,a,x,y);
        }
        if(x >= (*a)->xc && y >= (*a)->yc){
           
      rechercheCreeNoeudArbre(R,(*a)->ne,a,x,y);  
      }

    }
}




