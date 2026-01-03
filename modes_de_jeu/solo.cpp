#include "solo.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <termios.h>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille


void scorejeu (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp, size_t & nbtour) {
    //affiche le score après chaque déplacement et aussi le nombre de déplacement
    cout << "Nombre de déplacements : " << nombredep << endl;
    if (nombredep < 3) {//méthode du calcul du score
        score = score + (nombresupp * 10 * (4 - nombredep));
    }
    else {
        score = score + (nombresupp * 10);
    }
    cout << "Score : " << score << endl;
    cout << "Tours restants : " << nbtour << endl;
    nombresupp = 0;
}

/**
 * @brief main
 * @return
 */
void modenormalsolo (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
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
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeu(score,nombredep,nombresupp,nbtour);
    }
    cout << "Partie terminée !" << endl;
    scorejeu(score,nombredep,nombresupp,nbtour);
}
void modepersosolo (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    size_t nbtour = 0;
    creategrilleperso (KNbCandies, Nbligne,Nbcolonne,nbtour);
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu (grille,Nbligne,Nbcolonne)) {
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille,Nbligne,Nbcolonne) && !(nbtour == 0)) {
        makeAMove (grille,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
        suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
        remonteval (grille,Nbligne,Nbcolonne);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeu(score,nombredep,nombresupp,nbtour);
    }
    cout << "Partie terminée !" << endl;
    scorejeu(score,nombredep,nombresupp,nbtour);

}
void modesolo() {
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
    cout << "Bienvenue !" << endl << "Quel mode choisir ?" << endl;
    cout << "1 : Mode normal" << endl << "2 : Mode personnalisé" << endl << "3 : Règles du jeu" << endl;
    while (true) {
        cin >> mode;
        if (mode == 1) {
            modenormalsolo(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
        }
        else if (mode == 2) {
            modepersosolo(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
        }
        else if (mode == 3) {
            cout << "Dans ce jeu, le but va être de deplacer un jeton (chiffre) et sa ligne et colonne d'arrivée va supprimer les alignements de trois (ou plus) mêmes chiffres. " << endl << "Le but est donc de vider la grille et le jeu se finit quand il n'y a plus d'alignement possible ou que le nombre de tours restants est nul.";
        }
        else {
            cout << "Entrez quelque chose de valide.";
        }
    }
}
