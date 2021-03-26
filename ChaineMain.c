#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"
#include "SVGwriter.h"


int main(int argc, char** argv) {

    FILE* f = fopen(argv[1], "r") ;

    Chaines* ch = lectureChaines(f) ;

    affiche_Chaines(ch) ;

    //FILE* g = fopen("testMainChaine.cha", "w") ;
    //ecrireChaines(ch, g) ;
    //afficheChainesSVG(ch, "Chaines") ; 
    fclose(f) ; 
    //fclose(g) ;


    printf("longueurTotal : %.2f\n nb_points = %d\n", longueurTotale(ch), comptePointsTotal(ch)) ;
}