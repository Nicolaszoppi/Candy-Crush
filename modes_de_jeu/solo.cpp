/**
 * @file solo.cpp
 * @author ZOPPI Nicolas, KEOKHAM Rayan, LONGO Matys ; BUT1 Informatique GROUPE
 * @date 31-12-2025
 * @brief Gestion des menus et des boucles de jeu pour le joueur Solo.
 *
 * Ce fichier regroupe les fonctions pour le mode Solo classiquele mode personnalisé,
 * ainsi que le menu de sélection qui redirige vers le mode Infini et le mode Histoire.
 */
#include "solo.h"
#include <iostream>
#include <vector>
#include <ctime>
#include "modeinfini.h"
#include "modehistoire.h"
#include <fstream>
#include <limits>
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
 * @brief Calcule et affiche le score du joueur.
 * Ajoute un multiplicateur de score si le joueur joue en moins de 3 mouvements pour faire un alignement.
 *Affiche également les tours restants.
 *
 * @param[in,out] score Le score actuel du joueur.
 * @param[in] nombredep Le nombre de déplacements effectués pour ce coup.
 * @param[in,out] nombresupp Le nombre de chiffres supprimés
 * @param[in] nbtour Le nombre de tours restants.
 */
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
 * @brief Lance une partie en Mode Solo Normal.
 * La grille est générée automatiquement en fonction du nombre de chiffres choisi.
 * Le jeu s'arrête si le joueur n'a plus de tours ou s'il n'y a plus de mouvements possibles.
 *
 * @param[in,out] score Score du joueur
 * @param[in,out] nombredep Nombre de déplacements
 * @param[in,out] nombresupp Nombre de suppressions
 * @param[out] direction Direction du mouvement
 * @param[in,out] coord Position du joueur
 * @param[out] Nbligne Nombre de lignes
 * @param[out] Nbcolonne Nombre de colonnes
 * @param[out] KNbCandies Nombre de chiffres différents pour le jeu
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

/**
 * @brief Lance une partie en Mode Solo Personnalisé.
 * Permet au joueur de choisir le nombre de lignes, de colonnes, de chiffres et de tours.
 * Le jeu s'arrête si le joueur n'a plus de tours ou s'il n'y a plus de mouvements possibles.
 *
 * @param[in,out] score Score du joueur
 * @param[in,out] nombredep Nombre de déplacements
 * @param[in,out] nombresupp Nombre de suppressions
 * @param[out] direction Direction du mouvement
 * @param[in,out] coord Position du joueur
 * @param[out] Nbligne Nombre de lignes
 * @param[out] Nbcolonne Nombre de colonnes
 * @param[out] KNbCandies Nombre de chiffres différents pour le jeu
 */
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
    return;

}

