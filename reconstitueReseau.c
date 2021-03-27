#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Chaine.h"
#include "Reseau.h"



int main(int argc, char** argv) {

    char* nom_fichier = argv[1] ;
    int choix = atoi(argv[2]) ;


    printf("Le fichier choisi : %s\n") ;
    
    switch (choix)
    {
    case 1:
        printf("Liste\n") ;
        break;
    case 2: 
        printf("Table de hachage\n") ;
        break ;
    case 3:
        printf("Arbre\n") ;
        break ;
    default:
        break;
    }

    return 0 ;
    }