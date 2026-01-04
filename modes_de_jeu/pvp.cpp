/**
 * @file pvp.cpp
 * @author ZOPPI Nicolas, KEOKHAM Rayan, LONGO Matys ; BUT1 Informatique GROUPE
 * @date 31-12-2025
 * @brief Gestion du mode PvP
 *
 * Ce fichier contient les fonctions pour faire marcher le mode pvp
 * Chaque joueur dispose de sa propre grille identique au début et doit réaliser le meilleur score.
 */


#include "duo.h"
#include "modes_de_jeu/solo.h"
#include "modes_de_jeu/duo.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <termios.h>
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
 * @brief Calcule et affiche le score d'un joueur pendant son tour.
 * Applique un bonus de points si le joueur a joué vite (moins de 3 déplacements).
 * enlève un tour au compteur si tour du joueur 2
 *
 * @param[in,out] score Score actuel du joueur.
 * @param[in] nombredep Nombre de déplacements effectués
 * @param[in,out] nombresupp Nombre de chiffres supprimés 
 * @param[in,out] nbtour Nombre de tours restants pour la partie.
 * @param[in] joueur joueur 1 ou joueur 2 selon la parité.
 */
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

/**
 * @brief Affiche les résultats et choisi le vainqueur 
 * Compare les scores des deux joueurs et affiche un message de victoire ou d'égalité,et les stats de la partie.
 *
 * @param[in] score Score final du Joueur 1.
 * @param[in] score2 Score final du Joueur 2.
 * @param[in] nombredep Total des déplacements du Joueur 1.
 * @param[in] nombredep2 Total des déplacements du Joueur 2.
 */
void scorejeufinal(unsigned long & score,unsigned long & score2, unsigned long & nombredep,unsigned long nombredep2) {
    couleur(31);
    if (score2 > score) {
        cout << "Le joueur 2 a gagné !" << endl;
        couleur(0);
        cout << "Son score : " << score2 << endl << " Score de l'autre joueur : " << score << endl;
        cout << "Nombre de déplacements du joueur 1 : " << nombredep << endl;
        cout << "Nombre de déplacements du joueur 2 : " << nombredep2 << endl;
    }
    if (score > score2) {
        cout << "Le joueur 1 a gagné !" << endl;
        couleur(0);
        cout << "Son score : " << score << endl << " Score de l'autre joueur : " << score2 << endl;
        cout << "Nombre de déplacements du joueur 1 : " << nombredep << endl;
        cout << "Nombre de déplacements du joueur 2 : " << nombredep2 << endl;
    }
    else {
        cout << "Egalité !" << endl;
        cout << "Les deux joueurs finissent avec " << score << " de score !";
        cout << "Nombre de déplacements du joueur 1 : " << nombredep << endl;
        cout << "Nombre de déplacements du joueur 2 : " << nombredep2 << endl;
    }
}
/**
 * @brief Lance une partie PvP en mode normal.
 * Génère une grille, puis la duplique pour que chaque joueur ait exactement la même grille.
 * Les joueurs jouent chacun leur tour sur leur propre grille.
 *
 * @param[in,out] score Score du Joueur 1.
 * @param[in,out] score2 Score du Joueur 2.
 * @param[in,out] nombredep Déplacements Joueur 1.
 * @param[in,out] nombredep2 Déplacements Joueur 2.
 * @param[in,out] nombresupp Chiffres supprimés J1.
 * @param[in,out] nombresupp2 Chiffres supprimés J2.
 * @param[out] direction Direction du déplacement
 * @param[in,out] coord Position du joueur
 * @param[out] Nbligne Nombre de lignes.
 * @param[out] Nbcolonne Nombre de colonnes.
 * @param[out] KNbCandies Nombre de chiffres différents.
 * @param[in,out] joueur tour du joueur
 */
void modenormalpvp (unsigned long & score,unsigned long & score2, unsigned long & nombredep,unsigned long nombredep2, unsigned long & nombresupp ,unsigned long nombresupp2 , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & joueur) {
    size_t nbtour = 0;
    creategrille (KNbCandies, Nbligne,Nbcolonne,nbtour);
    mat grille1(Nbligne,line (Nbcolonne,0));
    initGrid(grille1,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu(grille1,Nbligne,Nbcolonne)) {
        initGrid (grille1,Nbligne,Nbcolonne, KNbCandies);
    }
    mat grille2 = grille1;
    while (!findujeu (grille1,Nbligne,Nbcolonne) && !findujeu (grille2,Nbligne,Nbcolonne) && !(nbtour == 0)) {
        tourjoueur(joueur);
        cout << endl;
        if (joueur % 2 == 0) {
            displayGrid(grille1, Nbligne,Nbcolonne,coord);
            makeAMove (grille1,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
            suppressiondoublons(grille1,coord,Nbligne,Nbcolonne,nombresupp);
            remonteval (grille1,Nbligne,Nbcolonne);
            displayGrid(grille1, Nbligne,Nbcolonne,coord);
            scorejeupvp(score,nombredep,nombresupp,nbtour,joueur);
            ++joueur;
            cout << joueur;
            coord.abs = 0;
            coord.ord = 0;
        }
        else {
            displayGrid(grille2, Nbligne,Nbcolonne,coord);
            makeAMove (grille2,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
            suppressiondoublons(grille2,coord,Nbligne,Nbcolonne,nombresupp);
            remonteval (grille2,Nbligne,Nbcolonne);
            displayGrid(grille2, Nbligne,Nbcolonne,coord);
            scorejeupvp(score2,nombredep2,nombresupp2,nbtour,joueur);
            ++joueur;
            cout << joueur;
            coord.abs = 0;
            coord.ord = 0;
        }
    }
    cout << endl << "Partie terminée !" << endl;
    scorejeufinal(score,score2,nombredep,nombredep2);
    return;
}

/**
 * @brief Lance une partie PvP en mode personnalisé.
 * Fonctionne exactement comme modenormalpvp mais utilise `creategrilleperso`
 * pour personaliser les paramètres de la grille.
 *
 * @param[in,out] score Score J1.
 * @param[in,out] score2 Score J2.
 * @param[in,out] nombredep Déplacements J1.
 * @param[in,out] nombredep2 Déplacements J2.
 * @param[in,out] nombresupp Suppressions J1.
 * @param[in,out] nombresupp2 Suppressions J2.
 * @param[out] direction Direction.
 * @param[in,out] coord Position.
 * @param[out] Nbligne Lignes.
 * @param[out] Nbcolonne Colonnes.
 * @param[out] KNbCandies Nombres de chiffres différents.
 * @param[in,out] joueur Identifiant joueur.
 */
void modepersopvp (unsigned long & score,unsigned long & score2, unsigned long & nombredep,unsigned long nombredep2, unsigned long & nombresupp ,unsigned long nombresupp2 , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & joueur) {
    size_t nbtour = 0;
    creategrilleperso (KNbCandies, Nbligne,Nbcolonne,nbtour);
    mat grille1(Nbligne,line (Nbcolonne,0));
    initGrid(grille1,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu(grille1,Nbligne,Nbcolonne)) {
        initGrid (grille1,Nbligne,Nbcolonne, KNbCandies);
    }
    mat grille2 = grille1;
    while (!findujeu (grille1,Nbligne,Nbcolonne) && !findujeu (grille2,Nbligne,Nbcolonne) && !(nbtour == 0)) {
        tourjoueur(joueur);
        cout << endl;
        if (joueur % 2 == 0) {
            displayGrid(grille1, Nbligne,Nbcolonne,coord);
            makeAMove (grille1,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
            suppressiondoublons(grille1,coord,Nbligne,Nbcolonne,nombresupp);
            remonteval (grille1,Nbligne,Nbcolonne);
            displayGrid(grille1, Nbligne,Nbcolonne,coord);
            scorejeupvp(score,nombredep,nombresupp,nbtour,joueur);
            ++joueur;
            coord.abs = 0;
            coord.ord = 0;
        }
        else {
            displayGrid(grille2, Nbligne,Nbcolonne,coord);
            makeAMove (grille2,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
            suppressiondoublons(grille2,coord,Nbligne,Nbcolonne,nombresupp);
            remonteval (grille2,Nbligne,Nbcolonne);
            displayGrid(grille2, Nbligne,Nbcolonne,coord);
            scorejeupvp(score2,nombredep2,nombresupp2,nbtour,joueur);
            ++joueur;
            coord.abs = 0;
            coord.ord = 0;
        }
    }
    cout << endl << "Partie terminée !" << endl;
    scorejeufinal(score,score2,nombredep,nombredep2);
    return;
}
/**
 * @brief Menu principal du mode PvP.
 * Permet de choisir entre le mode normal et le mode personnalisé.
 * Initialise les variables nécessaires a la partie 
 */
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
        cout << "(10 pour quitter)" << endl;
        cin >> mode;
        if (mode == 1) {
            modenormalpvp(score,score2,nombredep,nombredep2,nombresupp,nombresupp2,direction,coord,Nbligne,Nbcolonne,KNbCandies,joueur);
        }
        else if (mode == 2) {
            modepersopvp(score,score2,nombredep,nombredep2,nombresupp,nombresupp2,direction,coord,Nbligne,Nbcolonne,KNbCandies,joueur);
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

