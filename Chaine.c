#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"

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

        for (int i = 0; i < nbPoints; i++)      {
            
            fscanf(f, "%lf %lf ", &x, &y);               
            temp->x = x;
            temp->y = y;
            temp->suiv = malloc(sizeof(CellPoint));
            temp = temp->suiv;
            //printf("LIGNE 36\n") ;
            /*Mettre a jour le chainage */
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


void affiche_Chaines(Chaines *chaine){
    Chaines* ch = chaine ;
    for (int i = 0;i<ch->nbChaines;i++){
        printf("chaine num : %d " ,ch->chaines->numero);
        while (ch->chaines->points->suiv) {
            printf("%.2f %.2f ",ch->chaines->points->x,ch->chaines->points->y);
            ch->chaines->points = ch->chaines->points->suiv;
        }
    ch->chaines = ch->chaines->suiv;
    printf("\n");
    }
}



