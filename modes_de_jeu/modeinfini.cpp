#include "solo.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille

int makeAMoveinfini (mat & grille,maPosition & coord,char & direction,unsigned long & nombredep,const long int & Nbligne,const long int & Nbcolonne) {
    initmove(grille,coord,Nbligne,Nbcolonne);
    size_t valeurtrans;
    //Demande la directon du déplacement (de 1 case seulement)
    while (true) {
        cout << "Entrez votre direction. (ZQSD), R pour revenir en arrière et A pour arrêter" << endl;
        cin >> direction;
        char directionmin = tolower(direction);
        if (directionmin == 'z') {
            if (coord.ord <= 0) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                if (possmove(grille,coord,directionmin,Nbligne,Nbcolonne)) {
                    coord.ord = coord.ord - 1;
                    valeurtrans = grille[coord.ord][coord.abs];
                    grille[coord.ord][coord.abs] = grille[coord.ord + 1][coord.abs];
                    grille[coord.ord + 1][coord.abs] = valeurtrans;
                    ++nombredep;
                    break;
                }
                else {
                    cout << "déplacement impossible." << endl;//dans le cas ou litalign() est faux càd aucune suite de 3 chiffres identiques
                }
            }
        }
        if (directionmin == 's') {
            if (coord.ord >= Nbligne - 1) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                if (possmove(grille,coord,directionmin,Nbligne,Nbcolonne)) {
                    coord.ord = coord.ord + 1;
                    valeurtrans = grille[coord.ord][coord.abs];
                    grille[coord.ord][coord.abs] = grille[coord.ord - 1][coord.abs];
                    grille[coord.ord - 1][coord.abs] = valeurtrans;
                    ++nombredep;
                    break;
                }
                else {
                    cout << "déplacement impossible." << endl;
                }
            }
        }
        if (directionmin == 'q') {
            if (coord.abs <= 0) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                if (possmove(grille,coord,directionmin,Nbligne,Nbcolonne)) {
                    coord.abs = coord.abs - 1;
                    valeurtrans = grille[coord.ord][coord.abs];
                    grille[coord.ord][coord.abs] = grille[coord.ord][coord.abs + 1];
                    grille[coord.ord][coord.abs + 1] = valeurtrans;
                    ++nombredep;;
                    break;
                }
                else {
                    cout << "déplacement impossible." << endl;
                }
            }
        }
        if (directionmin == 'd') {
            if (coord.abs >= Nbcolonne - 1) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                if (possmove(grille,coord,directionmin,Nbligne,Nbcolonne)) {
                    coord.abs = coord.abs + 1;
                    valeurtrans = grille[coord.ord][coord.abs];
                    grille[coord.ord][coord.abs] = grille[coord.ord][coord.abs - 1];
                    grille[coord.ord][coord.abs - 1] = valeurtrans;
                    ++nombredep;
                    break;
                }
                else {
                    cout << "déplacement impossible." << endl;
                }
            }
        }
        if (directionmin == 'r') {//revient en arrière en cas d'erreur
            initmove(grille,coord,Nbligne,Nbcolonne);
        }
        else if (directionmin == 'a') {
            return 0;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
    return 0;
}
void scorejeuinfini (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp) {
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
void modenormalinfini (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    cout << "Nombre max ?" << endl;
    while (true) {
        cin >> KNbCandies;
        if (KNbCandies < 3) {
            cout << "Il doit y avoir minimum 3 chiffres possibles." << endl;
        }
        else break;
    }
    Nbligne = KNbCandies * 5;
    Nbcolonne = Nbligne;
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu(grille,Nbligne,Nbcolonne)) {
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille,Nbligne,Nbcolonne)) {
        makeAMoveinfini (grille,coord,direction,nombredep,Nbligne,Nbcolonne);
        if (direction == 'a') {
            break;
        }
        suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
        remonteval (grille,Nbligne,Nbcolonne);
        rempliColonne(grille,Nbligne, Nbcolonne, KNbCandies);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeuinfini(score,nombredep,nombresupp);
    }
    cout << "Partie terminée !" << endl;
    scorejeuinfini(score,nombredep,nombresupp);
    return;
}
