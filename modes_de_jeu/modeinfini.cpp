#include "solo.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <termios.h>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille


void scorejeuinfini (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp, size_t & nbtour) {
    //affiche le score après chaque déplacement et aussi le nombre de déplacement
    cout << "Nombre de déplacements : " << nombredep << endl;
    score = score + (nombresupp * 10);
    cout << "Score jeu : " << score << endl;
    nombresupp = 0;
}

/**
 * @brief main
 * @return
 */

void rempliColonne(mat & grille, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    for (long int i = 0 ; i < Nbligne ; ++i) {
        for (long int j = 0 ; j  < Nbcolonne ; ++j) {
            if (grille[i][j] == -1) {
                grille[i][j] = 1 + rand() % KNbCandies;
            }
        }
    }
}
/**for (int i = (int)startRow - 1; i >= 0; --i) {
        grille[i + howMany][col] = grid[i][col];
    }
    for (unsigned i = 0; i < howMany; ++i) {
        grille[i][col] = 1 + rand() % KNbCandies;
    }
}
*/
void modenormalinfini (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    size_t nbtour = 0;
    creategrille (KNbCandies, Nbligne,Nbcolonne,nbtour);
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu(grille,Nbligne,Nbcolonne)) {
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille,Nbligne,Nbcolonne) && !(nbtour == 0)) {
        makeAMove (grille,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
        suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
        remonteval (grille,Nbligne,Nbcolonne);
        rempliColonne(grille,Nbligne, Nbcolonne, KNbCandies);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeuinfini(score,nombredep,nombresupp,nbtour);
    }
    cout << "Partie terminée !" << endl;
    scorejeuinfini(score,nombredep,nombresupp,nbtour);
}
