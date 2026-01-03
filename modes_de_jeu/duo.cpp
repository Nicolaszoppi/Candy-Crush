#include "duo.h"
#include "modes_de_jeu/solo.h"
#include "modes_de_jeu/pvp.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <termios.h>
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
void modeduo() {
    size_t joueur = 2;
    unsigned long score = 0;
    unsigned long nombredep = 0;
    unsigned long nombresupp = 0;
    char direction = 'a';
    maPosition coord;
    coord.ord = 0;
    coord.abs = 0;
    long int Nbligne;
    long int Nbcolonne;
    size_t KNbCandies;
    size_t mode;
    cout << "Bienvenue !" << endl << "Quel mode de jeu choisir ?" << endl;
    while (true) {
        cout << "1 : Mode coop" << endl << "2 : Mode PVP (contre)" << endl << "3 : Règles du jeu" << endl;
        cout << "(10 pour quitter)" << endl;
        cin >> mode;
        if (mode == 1) {
            while (true) {
                cout << "Quel mode de choisir ?" << endl;
                cout << "1 : Mode normal" << endl << "2 : Mode personnalisé" << endl << "3 : Règles du jeu" << endl;
                cout << "(10 pour quitter)" << endl;
                cin >> mode;
                if (mode == 1) {
                    modenormalduo(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies,joueur);
                }
                else if (mode == 2) {
                    modepersoduo(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies,joueur);
                }
                else if (mode == 3) {
                    cout << "Dans ce jeu, le but va être de deplacer un jeton (chiffre) et sa ligne et colonne d'arrivée va supprimer les alignements de trois (ou plus) mêmes chiffres. " << endl << "Le but est donc de vider la grille et le jeu se finit quand il n'y a plus d'alignement possible ou que le nombre de tours restants est nul." << endl << "chacun des 2 joueurs joue quand c'est son tour !" << endl << endl;
                }
                else if (mode == 10) {
                    return;
                }
                else {
                    cout << "Entrez quelque chose de valide.";
                }
            }
        }
        else if (mode == 2) {
            modepvp();
        }
        else if (mode == 3) {
            cout << "Dans ce jeu, le but va être de deplacer un jeton (chiffre) et sa ligne et colonne d'arrivée va supprimer les alignements de trois (ou plus) mêmes chiffres. " << endl << "Le but est donc de vider la grille et le jeu se finit quand il n'y a plus d'alignement possible ou que le nombre de tours restants est nul." << endl << "chacun des 2 joueurs joue quand c'est son tour !" << endl << endl;
        }
        else if (mode == 10) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide.";
        }
    }

}
