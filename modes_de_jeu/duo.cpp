/**
 * @file duo.cpp
 * @author ZOPPI Nicolas, KEOKHAM Rayan, LONGO Matys ; BUT1 Informatique GROUPE
 * @date 31-12-2025
 * @brief Mode de jeu à deux joueurs COOP et PVP
 *
 * Ce fichier contient les menus et les fonctions pour le mode Duo.
 * On y trouve le mode coopératif et le mode PvP
 */
#include "duo.h"
#include "modes_de_jeu/solo.h"
#include "modes_de_jeu/pvp.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

/**
 * @typedef line
 * @brief Représente une ligne de la grille.
 */
typedef vector <short int> line;
/**
 * @typedef mat
 * @brief Représente la grille de jeu.
 */
typedef vector <line> mat;

/**
 * @brief Affiche quel joueur doit jouer sur le tour
 * Si pair joueur 1 joue, si impair joueur 2 joue
 * @param[in] joueur Compteur du joueur(tour) donc pair joueur 1, impair joueur 2
 */
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
/**
 * @brief Lance une partie en mode Duo.
 * Les joueurs partagent le même score et la même grille.
 * @param[in,out] score Score cumulé des 2 joueurs
 * @param[in,out] nombredep Nombre de déplacements faits
 * @param[in,out] nombresupp Nombre de chiffres supprimées
 * @param[out] direction Variable temporaire pour stocker la direction choisie.
 * @param[in,out] coord Variable temporaire pour la position du chiffre
 * @param[out] Nbligne Nombre de lignes de la grille
 * @param[out] Nbcolonne Nombre de colonnes de la grille
 * @param[out] KNbCandies Nombre de types de chiffres
 * @param[in] joueur joueur qui doit jouer
 */
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
/**
 * @brief Lance une partie en mode Duo version personalisée
 * Comme le mode normal mais on peut choisir ses propres paramètres de grille et de jeu
 *
 * @param[in,out] score Score cumulé des 2 joueurs
 * @param[in,out] nombredep Nombre de déplacements
 * @param[in,out] nombresupp chiffres supprimées
 * @param[out] direction Direction du déplacement
 * @param[in,out] coord Position du chiffre
 * @param[out] Nbligne Nombre de lignes
 * @param[out] Nbcolonne Nombre de colonnes
 * @param[out] KNbCandies Nombres de chiffres différents
 * @param[in] joueur tour du joueur
 */
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
/**
 * @brief Menu principal du mode Duo.
 * Permet de choisir entre le mode coop et le mode PVP
 */
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
                    reglesjeu ();
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
            reglesjeu ();
        }
        else if (mode == 10) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide.";
        }
    }

}
