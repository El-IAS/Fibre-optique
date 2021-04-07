 #include "Reseau.h"
 
 typedef struct hachage{
    int tailleMax;
    int nbNoeuds;
    CellNoeud **TabDeNeouds;
}TableHachage ;


int fonctionClef(int x,int y) ;
int fonctionHachage(int k) ;
Noeud* rechercheCreeNoeudHachage(Reseau* R, TableHachage* H, double x, double y); 
Reseau* reconstitueReseauHachage(Chaines *C, int M);