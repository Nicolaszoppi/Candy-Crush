#include "duo.h"
#include "modes_de_jeu/solo.h"
#include "modes_de_jeu/pvp.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
void tourjoueur (size_t joueur) {
    couleur(31);
    if (joueur % 2 == 0) {
        cout << "Au tour du joueur 1 !" << endl;
    }
    else {
        cout << "Au tour du joueur 2 !"<< endl;
    }
    couleur(0);

}
void modenormalduo (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & joueur) {
    size_t nbtour = 0;
    creategrille (KNbCandies, Nbligne,Nbcolonne,nbtour);
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu(grille,Nbligne,Nbcolonne)) {
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille,Nbligne,Nbcolonne) && !(nbtour == 0)) {
        tourjoueur(joueur);
        makeAMove (grille,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
        suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
        remonteval (grille,Nbligne,Nbcolonne);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeu(score,nombredep,nombresupp,nbtour);
    }
    cout << endl << "Partie terminée !" << endl;
    scorejeu(score,nombredep,nombresupp,nbtour);
}
void modepersoduo (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & joueur) {
    size_t nbtour = 0;
    creategrilleperso (KNbCandies, Nbligne,Nbcolonne,nbtour);
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu(grille,Nbligne,Nbcolonne)) {
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille,Nbligne,Nbcolonne) && !(nbtour == 0)) {
        tourjoueur(joueur);
        makeAMove (grille,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
        suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
        remonteval (grille,Nbligne,Nbcolonne);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeu(score,nombredep,nombresupp,nbtour);
    }
    cout << endl << "Partie terminée !" << endl;
    scorejeu(score,nombredep,nombresupp,nbtour);
    return;
}

