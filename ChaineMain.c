#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"
#include "Reseau.h"
//#include "SVGwriter.h"


int main(int argc, char** argv) {

    FILE* f = fopen(argv[1], "r") ;

    Chaines* ch = lectureChaines(f) ;

    //affiche_Chaines(ch) ;

    Reseau* R = reconstitueReseauListe(ch) ;
    FILE* g = fopen("testMainChaine.cha", "w") ;
    ecrireReseau(R, g) ;
    //afficheChainesSVG(ch, "Chaines") ; 
    fclose(f) ; 
    fclose(g) ;

    //printf("%d\n", R->nbNoeuds) ;
   //printf("longueurTotal : %.2f\n nb_points = %d\n", longueurTotale(ch), comptePointsTotal(ch)) ;
}

/* gcc -Wall -o ChaineMain ChaineMain.c Chaine.c Reseau.c SVGwriter.c -lm */