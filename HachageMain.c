#include "Hachage.h"




int main()  {

    for (int x=1 ; x<=10 ; x++) {
        for (int y=1 ; y<=10 ; y++) {
            printf("x=%d y=%d -> %d\n", x, y, fonctionClef(x,y)) ;
         }
    }


    return 0 ;
}



/* gcc -Wall -o HachageMain HachageMain.c Hachage.c*/