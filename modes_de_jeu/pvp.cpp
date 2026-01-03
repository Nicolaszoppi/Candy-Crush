#include "duo.h"
#include "modes_de_jeu/solo.h"
#include "modes_de_jeu/duo.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <termios.h>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille

void scorejeupvp (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp, size_t & nbtour,size_t joueur ) {
    //affiche le score après chaque déplacement et aussi le nombre de tours restants et le nombre de déplacements
    cout << "Nombre de déplacements : " << nombredep << endl;
    if (nombredep < 3) {//méthode du calcul du score
        score = score + (nombresupp * 10 * (4 - nombredep));
    }
    else {
        score = score + (nombresupp * 10);
    }
    cout << "Score : " << score << endl;
    if (joueur % 2 == 1) --nbtour;
    cout << "Tours restants : " << nbtour << endl;
    nombresupp = 0;
}

void modenormalpvp (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & joueur) {
    size_t nbtour = 0;
    creategrille (KNbCandies, Nbligne,Nbcolonne,nbtour);
    mat grille1(Nbligne,line (Nbcolonne,0));
    initGrid(grille1,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu(grille1,Nbligne,Nbcolonne)) {
        initGrid (grille1,Nbligne,Nbcolonne, KNbCandies);
    }
    mat grille2 = grille1;
    displayGrid(grille2, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille1,Nbligne,Nbcolonne) && !findujeu (grille2,Nbligne,Nbcolonne) && !(nbtour == 0)) {
        tourjoueur(joueur);
        if (joueur % 2 == 0) {
            makeAMove (grille1,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
            suppressiondoublons(grille1,coord,Nbligne,Nbcolonne,nombresupp);
            remonteval (grille1,Nbligne,Nbcolonne);
            displayGrid(grille1, Nbligne,Nbcolonne,coord);
            scorejeupvp(score,nombredep,nombresupp,nbtour,joueur);
            coord.abs = 0;
            coord.ord = 0;
        }
        else {
            makeAMove (grille2,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
            suppressiondoublons(grille2,coord,Nbligne,Nbcolonne,nombresupp);
            remonteval (grille2,Nbligne,Nbcolonne);
            displayGrid(grille2, Nbligne,Nbcolonne,coord);
            scorejeupvp(score2,nombredep2,nombresupp2,nbtour,joueur);
            coord.abs = 0;
            coord.ord = 0;
        }
    }
    cout << endl << "Partie terminée !" << endl;
    scorejeufinal(score,nombredep,nombresupp,nbtour);
}
void modepersopvp (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & joueur) {
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
        ++joueur;
    }
    cout << "Partie terminée !" << endl;
    scorejeu(score,nombredep,nombresupp,nbtour);
}
void modepvp() {
    size_t joueur = 2;
    unsigned long score = 0;
    unsigned long nombredep = 0;
    unsigned long nombresupp = 0;
    unsigned long score2 = 0;
    unsigned long nombredep2 = 0;
    unsigned long nombresupp2 = 0;
    char direction = 'a';
    maPosition coord;
    coord.ord = 0;
    coord.abs = 0;
    long int Nbligne;
    long int Nbcolonne;
    size_t KNbCandies;
    size_t mode;
    while (true) {
        cout << "Quel mode choisir ?" << endl;
        cout << "1 : Mode normal" << endl << "2 : Mode personnalisé" << endl << "3 : Règles du jeu" << endl;
        cin >> mode;
        if (mode == 1) {
            modenormalpvp(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies,joueur);
        }
        else if (mode == 2) {
            modepersopvp(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies,joueur);
        }
        else if (mode == 3) {
            cout << "Dans ce jeu, le but va être de deplacer un jeton (chiffre) et sa ligne et colonne d'arrivée va supprimer les alignements de trois (ou plus) mêmes chiffres. " << endl << "Le but est donc de vider la grille et le jeu se finit quand il n'y a plus d'alignement possible ou que le nombre de tours restants est nul." << endl << "chacun des 2 joueurs joue quand c'est son tour et celui qui finit avec le meilleur score gagne !" << endl << endl;
        }
        else {
            cout << "Entrez quelque chose de valide.";
        }
    }
}
