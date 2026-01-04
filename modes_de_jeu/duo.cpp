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
typedef vector <short int> line; // un type représentant une ligne de la grille
/**
 * @typedef mat
 * @brief Représente la grille de jeu.
 */
typedef vector <line> mat; // un type représentant la grille

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

