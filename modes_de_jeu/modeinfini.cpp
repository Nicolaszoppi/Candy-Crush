/**
 * @file modeinfini.cpp
 * @author ZOPPI Nicolas, KEOKHAM Rayan, LONGO Matys ; BUT1 Informatique GROUPE
 * @date 31-12-2025
 * @brief mode de jeu infini.
 * 
 * Ce mode fait en sorte de remplir la grille automatiquement après chaque coup,
 * permettant une partie sans fin tant que des coups sont possibles.
 */
#include "solo.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;
/**
 * @typedef line
 * @brief Représente une ligne de la grille
 */
typedef vector <short int> line; // un type représentant une ligne de la grille

/**
 * @typedef mat
 * @brief Représente la grille du jeu
 */
typedef vector <line> mat; // un type représentant la grille


/**
 * @brief Gère le déplacement d'un bonbon en mode infini
 * Pareil que celle de base et ajoute la possibilité d'arrêter la partie en appuyant sur la touche 'A' .
 * @param[in,out] grille La grille de jeu.
 * @param[in,out] coord La position du curseur.
 * @param[out] direction La direction choisie par le joueur.
 * @param[in,out] nombredep Compteur de déplacements (incrémenté si mouvement valide).
 * @param[in] Nbligne Nombre de lignes.
 * @param[in] Nbcolonne Nombre de colonnes.
 * @return int Retourne 0 (Code de statut, potentiellement pour future extension).
 */
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


/**
 * @brief Affiche et met à jour le score pour le mode infini.
 * Le score est calculé en multipliant le nombre de bonbons supprimés par 10.
 *
 * @param[in,out] score Score total du joueur
 * @param[in] nombredep Nombre total de déplacements effectués
 * @param[in,out] nombresupp Nombre de chiffres supprimés remis a 0 après chaque deplacements
 */
void scorejeuinfini (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp) {
    //affiche le score après chaque déplacement et aussi le nombre de déplacement mais pas les tours
    cout << "Nombre de déplacements : " << nombredep << endl;
    score = score + (nombresupp * 10);
    cout << "Score : " << score << endl;
    nombresupp = 0;
}

/**
 * @brief main
 * @return
 */

/**
 * @brief Remplit les colonnes de la grille
 * Remplit les cases vides -1 de la grille avec des vals aléatoires entre 1 et KNbCandies
*
 * @param[in,out] grille La grille
 * @param[in] Nbligne Nombre de lignes
 * @param[in] Nbcolonne Nombre de colonnes
 * @param[in] KNbCandies Nombes de chiffres différents
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

/**
 * @brief Fonction principale du jeu en Mode Infini.
 * Initialise une grille mode normal
 * La boucle continue tant que des coups sont possibles ou que le joueur n'appuie pas sur A.
 * À chaque tour, la grille est rempli via rempliColonne.
 *
 * @param[in,out] score Score du joueur
 * @param[in,out] nombredep Compteur de déplacements
 * @param[in,out] nombresupp Compteur de chiffres supprimés.
 * @param[out] direction Direction du mouvement
 * @param[in,out] coord Position du joueur
 * @param[out] Nbligne Nombre de lignes
 * @param[out] Nbcolonne Nombre de colonnes
 * @param[out] KNbCandies Nombre de chiffres différents pour le jeu
 */
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
