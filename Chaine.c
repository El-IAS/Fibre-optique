#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"
#include "SVGwriter.h"

Chaines* lectureChaines(FILE *f){
    int nbChaines;
    int gamma;
    fscanf(f,"NbChain: %d\n",&nbChaines);
    fscanf(f,"Gamma: %d\n",&gamma);
    Chaines *ch = (Chaines*) malloc(sizeof(Chaines));
    ch->nbChaines = nbChaines;
    ch->gamma = gamma;
    ch->chaines = NULL;
    //printf("LIGNE 16\n") ;
    int numero;
    int nbPoints;

    CellChaine* cellchaine = (CellChaine*)malloc(sizeof(CellChaine)) ;
    CellChaine* tempChaine = cellchaine ;
    for (int k=0 ; k<nbChaines ; k++)   {
        //printf("%s\n", buffer) ;
        fscanf(f, "%d %d ", &numero, &nbPoints);
        tempChaine->numero = numero;
        double x, y;
        //printf("LIGNE 26\n") ;
        CellPoint *points = (CellPoint *)malloc(nbPoints * sizeof(CellPoint));
        CellPoint *temp = points;

        for (int i = 0; i < nbPoints ; i++)      {
            
            fscanf(f, "%lf %lf ", &x, &y);    
            temp->x = x;
            temp->y = y;
            if (i==nbPoints-1)  break ;
            temp->suiv = malloc(sizeof(CellPoint));
            temp = temp->suiv;

        }
        temp = NULL ;
          /*Mettre a jour le chainage*/
 
        tempChaine->points = points;
        tempChaine->suiv = malloc(sizeof(Chaines)) ;
        tempChaine = tempChaine->suiv ;
        //printf("LIGNE 44\n") ;
    }
    tempChaine = NULL ;
    ch->chaines = cellchaine ;

    return ch ;
}


void ecrireChaines(Chaines *C , FILE *f){
      fprintf(f,"NbChain: %d\n",C->nbChaines);
      fprintf(f,"Gamma: %d\n\n",C->gamma);
      CellChaine *chaines = C->chaines;
      while(chaines->suiv){
         CellPoint *tmp = chaines->points;
         int nbPoints = 0 ;
         while(tmp->suiv){
            nbPoints++;
            tmp = tmp->suiv ;
         }
         printf("%d %d ",chaines->numero,nbPoints);
         fprintf(f,"%d %d ",chaines->numero,nbPoints);
         CellPoint *points = chaines->points;
         printf("NBPoints : %d\n", nbPoints) ;
         while(points->suiv){
             fprintf(f,"%.2f %.2f ",points->x,points->y);
             points = points->suiv;
         }
         chaines=chaines->suiv;
         fprintf(f,"\n");
      }
}



void affiche_Chaines(Chaines *chaine){
    Chaines* ch = chaine ;
    CellChaine* chaine_temp = ch->chaines ;
    for (int i = 0;i<ch->nbChaines;i++){
        printf("chaine num : %d " ,chaine_temp->numero);
        CellPoint * temp = chaine_temp->points ;
        while (temp->suiv) {
            printf("%.2f %.2f ",temp->x,temp->y);
            temp = temp->suiv ;
        }
    chaine_temp = chaine_temp->suiv;
    printf("\n");
    }
}


void afficheChainesSVG(Chaines *C, char* nomInstance){
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}

double longueurChaine(CellChaine *c){
     CellChaine *ch = c;
     double somme = 0.0 ;
     CellPoint *points = ch->points ;
     while(points){
        CellPoint *pointsuiv = points->suiv;
        while(pointsuiv){
             double count = (points->x-pointsuiv->x)*(points->x-pointsuiv->x)+(points->y-pointsuiv->y)*(points->y-pointsuiv->y) ;
             somme = somme + sqrt(count);
             pointsuiv=pointsuiv->suiv;
         }
        points=points->suiv;
     }
      return somme;
}






double longueurTotale(Chaines *C)   {

    CellChaine* temp_chaine = C->chaines ;
    double somme = 0.0 ;
    while (temp_chaine)    {
        somme += longueurChaine(temp_chaine) ;
        temp_chaine = temp_chaine->suiv ;
    }

    return somme ;
}




int comptePointsTotal(Chaines *C)   {
    
    CellChaine* temp_chaine = C->chaines ; 
    int nb_points = 0 ;
    CellPoint* temp_point ; 
    while (temp_chaine) {
        temp_point = temp_chaine->points ;
        while (temp_point)  {
            printf("(%.2f %.2f)\n", temp_point->x, temp_point->y) ; 
            nb_points++ ;
            temp_point = temp_point->suiv ;
        }
        temp_chaine = temp_chaine->suiv ;
    }
    return nb_points ;

}