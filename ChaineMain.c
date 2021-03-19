#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chaine.h"



int main(int argc, char** argv) {

    FILE* f = fopen(argv[1], "r") ;

    Chaines* ch = lectureChaines(f) ;

    affiche_Chaines(ch) ;


}