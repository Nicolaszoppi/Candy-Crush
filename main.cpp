/**
*@file main.cpp
*@author ZOPPI Nicolas, KEOKHAM Rayan, LONGO Matys ; BUT1 Informatique GROUPE 
*@date 31-12-2025
*@brief Fichier principal de notre Projet de SAE 1.01 - "Candy Crush"

 * Ce fichier permet de lancer le jeu et d'accéder aux différents modes de jeu
 * avec un menu principal.
*/

#include <iostream>
#include <vector>
#include <ctime>
#include <modes_de_jeu/solo.h>
#include <modes_de_jeu/duo.h>
#include <modes_de_jeu/pvp.h>
#include <modes_de_jeu/modeinfini.h>
#include <modes_de_jeu/modehistoire.h>
#include<cstdlib>
#include <fstream>
using namespace std;
/**
 * @typedef line
 * @brief Représente une ligne de la grille
 */
typedef vector <short int> line; // un type représentant une ligne de la grille

/**
 * @typedef mat
 * @brief Représente la grille de jeu
 */
typedef vector <line> mat; // un type représentant la grille
/**
 * @brief Affiche les règles du jeu à partir d'un fichier externe.
 *
 * Lit le fichier "reglesdujeu.txt" et l'affiche ligne par ligne les règles du jeudans la console.
 */
void reglesjeu () {
    string ligne;
    ifstream fichier("../../reglesdujeu.txt");
    while (true){
        getline(fichier,ligne);
        if (fichier.eof())break;
        cout << ligne << endl;
    }
}

/**
 * @brief Change la couleur du texte dans la console.
 * @param[in] coul Le code ANSI de la couleur que l'on veut.
 */
void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";//Définira la couleur de chaque chiffre
}
/**
 * @brief Souligne le texte dans la console.
 *
 * Utilisé pour mettre en évidence la position dans la matrice
 * @param[in] chiffre Code de style (4 pour souligner).
 */
void souligner (const unsigned & chiffre) {//Souligne ou nous serons dans la matrice
    cout << "\033[4;" << chiffre << "m";
}

/**
 * @brief Initialise les paramètres de la grille
 * Demande à l'utilisateur le nombre de types de chiffres différents et calcule automatiquementla taille de la grille et le nombre de tours.
 *
 * @param[out] KNbCandies Nombre de types de chiffres différents.
 * @param[out] Nbligne Nombre de lignes de la grille 
 * @param[out] Nbcolonne Nombre de colonnes de la grille
 * @param[out] nbtour Nombre de tours maximum 
 */
void creategrille (size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne,size_t & nbtour) {  //Crée une grille selon le nombre de chiffres possibles (commence à 3)
    while (true) {
        cout << "Nombre max ?" << endl;
        cin >> KNbCandies;
        if ((KNbCandies < 3) || (KNbCandies > 9)) {
            cout << "Il ne peut y avoir qu'un minimum de 3 et un maximum de 9 possibilités." << endl;
        }
        else break;
    }
    Nbligne = KNbCandies*2;
    Nbcolonne= Nbligne;
    nbtour = KNbCandies*3;
    cout << "Taille de la grille : " << Nbligne << "*" << Nbcolonne << endl;
    cout << "Nombre de tours : " << nbtour << endl;
}


/**
 * @brief Initialise les paramètres de la grille personnalisé.
 * L'utilisateur choisit manuellement toutes les dimensions et contraintes du jeu.
 * @param[out] KNbCandies Nombre de types de bonbons(chiffres).
 * @param[out] Nbligne Nombre de lignes.
 * @param[out] Nbcolonne Nombre de colonnes.
 * @param[out] nbtour Nombre de tours.
 */
void creategrilleperso (size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne,size_t & nbtour) { //Crée une grille entièrement customisable (rectangulaire ou carrée)
    while (true) {
        cout << "Nombre max ?" << endl;
        cin >> KNbCandies;
        if ((KNbCandies < 2) || (KNbCandies > 9)) {
            cout << "Il ne peut y avoir qu'un minimum de 2 et un maximum de 9 possibilités." << endl;
        }
        else break;
    }
    cout << "Lignes ?" << endl;
    while (true) {
        cin >> Nbligne;
        if (Nbligne < 5 ) {
            cout << "Il doit y avoir minimum 5 lignes." << endl;
        }
        else break;
    }
    cout << "Colonnes?" << endl;
    while (true) {
        cin >> Nbcolonne;
        if (Nbcolonne < 5 ) {
            cout << "Il doit y avoir minimum 5 colonne." << endl;
        }
        else break;
    }
    cout << "Nombre de tour?" << endl;
    while (true) {
        cin >> nbtour;
        if (nbtour < 2 ) {
            cout << "Il doit y avoir au moins 3 tours." << endl;
        }
        else break;
    }
}

/**
 * @brief Vérifie si on a un alignement de 3 chiffres identique.
 *  * Vérifie horizontalement et verticalement autour de la position donnée s'il y a
 * une suite de 3 nombres identiques.
 *
 * @param[in] grille La grille de jeu actuelle.
 * @param[in] coord La position à verifier.
 * @param[in] Nbligne Nombre total de lignes.
 * @param[in] Nbcolonne Nombre total de colonnes.
 * @return true Si un alignement de 3 chiffres identiques.
 * @return false Sinon.
 */
bool litalign (const mat & grille, maPosition & coord,const long int & Nbligne,const long int & Nbcolonne) {
    //permet de trouver si il y a un alignement vertical ou horizontal de minimum trois mêmes chiffre d'affilée par raport à la position
    long int i = 0;
    long int val = 1;
    //en abscisse
    while (i < Nbcolonne - 1) {
        if (grille[coord.ord][i] >= 0 && grille[coord.ord][i] == grille[coord.ord][i + 1]) {
            ++val;
            if (val == 3) {
                return true;
            }
        }
        else {
            val = 1;
        }
        ++i;
    }
    i = 0;
    val = 1;
    //en ordonnée
    while (i < Nbligne - 1) {
        if (grille[i][coord.abs] >= 0 && grille[i][coord.abs] == grille[i + 1][coord.abs]) {
            ++val;
            if (val == 3) {
                return true;
            }
        }
        else {
            val = 1;
        }
        ++i;
    }
    return false;
}

/**
 * @brief Initialise et remplis la grille avec des valeurs aléatoires.
 *
 * @param[in,out] grille La matrice à remplir.
 * @param[in] Nbligne Nombre de lignes.
 * @param[in] Nbcolonne Nombre de colonnes.
 * @param[in] KNbCandies Nombre maximum de types de chiffres (pour le modulo).
 * @return mat La grille remplie.
 */
mat initGrid (mat & grille,const long int & Nbligne,const long int & Nbcolonne,const size_t & KNbCandies) { //Donne les valeurs aléatoirement dans chaque cases
    for (long int i = 0; i < Nbligne ; ++i) {
        for (long int j = 0; j < Nbcolonne;++j ) {
            grille[i][j] = rand()%KNbCandies + 1;
        }
    }
    return grille;
}


/**
 * @brief Affiche la grille dans la console.
 * Gère l'affichage des bordures, des couleurs des chiffres et du curseur de sélection.
 * Les cases vides (-1 ou -2) sont affichées comme des espaces.
 *
 * @param[in,out] grille La grille à afficher
 * @param[in] Nbligne Nombre de lignes
 * @param[in] Nbcolonne Nombre de colonnes
 * @param[in] coord Position actuelle
 */
void displayGrid (mat & grille,const long int & Nbligne,const long int & Nbcolonne, const maPosition & coord) {//Affiche la grille sous forme de tableau
    cout << endl << "   ";
    for (long int abs = 0; abs < 10 ; ++abs) {
        cout << "  " << abs << " ";
    }
    cout << endl;
    for (long int i = 0; i < Nbligne ; ++i) {
        if (i < 10) {
            cout << " " << i << " ";
        }
        else cout << "   ";
        for (long int j = 0; j < Nbcolonne; ++j ) {
            if (j == coord.abs && i == coord.ord) {
                cout << "| ";
                souligner(4);
                couleur(30+grille[i][j]);
                if (grille[i][j] == -1 || grille[i][j] == -2) {
                    cout << " ";
                    souligner(24);
                    cout << " ";
                }
                else {
                    cout << grille[i][j];
                    souligner(24);
                    cout << " ";
                }
                couleur(0);
            }
            else if (grille[i][j] == -1 || grille[i][j] == -2) {
                cout << "| ";
                cout << "  ";
                couleur(0);
            }
            else {
                cout << "| ";
                couleur(30+grille[i][j]);
                cout << grille[i][j] << " ";
                couleur(0);
            }
        }
        cout << "|" << endl;
    }
}

/**
 * @brief Vérifie si un mouvement est possible
 * Verifie l'échange de deux cases selon la direction donnée. Si alignement via litalign, le mouvement est validé. Sinon, l'échange est annulé.
 * *
 * @param[in,out] grille La grille de jeu.
 * @param[in] coord La position de départ.
 * @param[in] direction Direction du mouvement (Z,Q,S,D).
 * @param[in] Nbligne Nombre de lignes
 * @param[in] Nbcolonne Nombre de colonnes
 * @return true Si le mouvement provoque un alignement (mouvement valide).
 * @return false Si le mouvement ne fait rien (mouvement invalide).
 */
bool possmove (mat & grille, maPosition & coord,char & direction,const long int & Nbligne,const long int & Nbcolonne) {
    maPosition coordtest;
    coordtest.abs = coord.abs;
    coordtest.ord = coord.ord;
    size_t valeurtrans;
    if (direction == 'z') {
        --coordtest.ord;
        valeurtrans = grille[coordtest.ord][coordtest.abs];
        grille[coordtest.ord][coordtest.abs] = grille[coordtest.ord + 1][coordtest.abs];
        grille[coordtest.ord + 1][coordtest.abs] = valeurtrans;
        if (litalign(grille,coordtest,Nbligne,Nbcolonne)) {
            grille[coordtest.ord + 1][coordtest.abs] = grille[coordtest.ord][coordtest.abs];
            grille[coordtest.ord][coordtest.abs] = valeurtrans;
            return true;
        }
        else {
            grille[coordtest.ord + 1][coordtest.abs] = grille[coordtest.ord][coordtest.abs];
            grille[coordtest.ord][coordtest.abs] = valeurtrans;
            return false;
        }
    }
    if (direction == 's') {
        ++coordtest.ord;
        valeurtrans = grille[coordtest.ord][coordtest.abs];
        grille[coordtest.ord][coordtest.abs] = grille[coordtest.ord - 1][coordtest.abs];
        grille[coordtest.ord - 1][coordtest.abs] = valeurtrans;
        if (litalign(grille,coordtest,Nbligne,Nbcolonne)) {
            grille[coordtest.ord - 1][coordtest.abs] = grille[coordtest.ord][coordtest.abs];
            grille[coordtest.ord][coordtest.abs] = valeurtrans;
            return true;
        }
        else {
            grille[coordtest.ord - 1][coordtest.abs] = grille[coordtest.ord][coordtest.abs];
            grille[coordtest.ord][coordtest.abs] = valeurtrans;
            return false;
        }
    }
    if (direction == 'q') {
        --coordtest.abs;
        valeurtrans = grille[coordtest.ord][coordtest.abs];
        grille[coordtest.ord][coordtest.abs] = grille[coordtest.ord][coordtest.abs + 1];
        grille[coordtest.ord][coordtest.abs + 1] = valeurtrans;
        if (litalign(grille,coordtest,Nbligne,Nbcolonne)) {
            grille[coordtest.ord][coordtest.abs + 1] = grille[coordtest.ord][coordtest.abs];
            grille[coordtest.ord][coordtest.abs] = valeurtrans;
            return true;
        }
        else {
            grille[coordtest.ord][coordtest.abs + 1] = grille[coordtest.ord][coordtest.abs];
            grille[coordtest.ord][coordtest.abs] = valeurtrans;
            return false;
        }
    }
    if (direction == 'd') {
        ++coordtest.abs;
        valeurtrans = grille[coordtest.ord][coordtest.abs];
        grille[coordtest.ord][coordtest.abs] = grille[coordtest.ord][coordtest.abs - 1];
        grille[coordtest.ord][coordtest.abs - 1] = valeurtrans;
        if (litalign(grille,coordtest,Nbligne,Nbcolonne)) {
            grille[coordtest.ord][coordtest.abs - 1] = grille[coordtest.ord][coordtest.abs];
            grille[coordtest.ord][coordtest.abs] = valeurtrans;
            return true;
        }
        else {
            grille[coordtest.ord][coordtest.abs - 1] = grille[coordtest.ord][coordtest.abs];
            grille[coordtest.ord][coordtest.abs] = valeurtrans;
            return false;
        }
    }
    return false;
}

/**
 * @brief Demande à l'utilisateur de sélectionner une case.
 * Vérifie que les coordonnées entrées sont possible et que la case n'est pas vide.
 * @param[in] grille La grille actuelle.
 * @param[out] coord Les coordonnées choisies par l'utilisateur.
 * @param[in] Nbligne Nombre de lignes.
 * @param[in] Nbcolonne Nombre de colonnes.
 */
void initmove (mat & grille,maPosition & coord,const long int & Nbligne,const long int & Nbcolonne ) {
    //Donne les coordonnées du départ du déplacement
    cout << "coordonnées ? (x,y)" << endl;
    while (true) {
        while (true) {
            cin >> coord.abs;
            if ((coord.abs >= Nbcolonne) | (coord.abs < 0)) {
                cout << "La position doit appartenir au tableau." << endl;
            }
            else break;
        }
        while (true) {
            cin >> coord.ord;
            if ((coord.ord >= Nbligne) | (coord.ord < 0)) {
                cout << "La position doit appartenir au tableau." << endl;
            }
            else break;
        }
        if (grille[coord.ord][coord.abs] == (-1)) {
            cout << "il n'y a rien ici.";
        }
        else break;
    }
}

/**
 * @brief Gère le tour de jeu (sélection et déplacement).
 * Appelle initmove pour la sélection, demande une direction puis vérifie la validité via possmove et effectue l'échange si valide.
 * Et retire 1 tours aux nombre de tours restants.
 * @param[in,out] grille La grille de jeu.
 * @param[in,out] coord Coordonnées de la case sélectionnée.
 * @param[out] direction Direction choisie.
 * @param[in,out] nombredep Compteur de déplacements effectués (statistiques).
 * @param[in] Nbligne Nombre de lignes.
 * @param[in] Nbcolonne Nombre de colonnes.
 * @param[in,out] nbtour Nombre de tours restants.
 */
void makeAMove (mat & grille,maPosition & coord,char & direction,unsigned long & nombredep,const long int & Nbligne,const long int & Nbcolonne,size_t & nbtour ) {
    initmove(grille,coord,Nbligne,Nbcolonne);
    size_t valeurtrans;
    //Demande la directon du déplacement (de 1 case seulement)
    while (true) {
        cout << "Entrez votre direction. (ZQSD) ou R pour revenir en arrière" << endl;
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
                    --nbtour;
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
                    --nbtour;
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
                    ++nombredep;
                    --nbtour;
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
                    --nbtour;
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
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
}

/**
 * @brief Supprime les alignements et met à jour le score.
 * Parcourt la grille autour de la position donnée pour trouver les alignements de 3 ou plus.
 * Les cases alignées sont remplacées par -1 càd case vide.
 * @param[in,out] grille La grille de jeu.
 * @param[in] coord Position pour ou on vérifie les alignements
 * @param[in] Nbligne Nombre de lignes
 * @param[in] Nbcolonne Nombre de colonnes
 * @param[in,out] nombresupp Compteur total de chiffres supprimés pour le score
 */

void suppressiondoublons (mat & grille, const maPosition & coord,const long int & Nbligne,const long int & Nbcolonne,unsigned long & nombresupp) {
    //applique la suppression des alignements de même chiffres d'affilée
    long int valeurmilieu = grille[coord.ord][coord.abs];
    long int nombre;
    long int dep = 0;
    long int i = 0;
    bool cond;
    //en abscisse
    while (i < Nbcolonne - 2) {
        if ((grille[coord.ord][i] >= 0) && (grille[coord.ord][i] == grille[coord.ord][i+1]) && (grille[coord.ord][i] == grille[coord.ord][i+2])) {
            nombre = grille[coord.ord][i];
            dep = 0;
            while ((dep + i < Nbcolonne) && (grille[coord.ord][i + dep] == nombre)) {
                grille[coord.ord][i + dep] = -1;
                ++nombresupp;
                ++dep;
            }
        }
        ++i;
    }
    //en ordonnée
    if (grille[coord.ord][coord.abs] == -1) {
        grille[coord.ord][coord.abs] = valeurmilieu;
        cond = true;
    }
    i = 0;
    while (i < Nbligne - 2) {
        if ((grille[i][coord.abs] >= 0) && (grille[i][coord.abs] == grille[i+1][coord.abs]) && (grille[i+1][coord.abs] == grille[i+2][coord.abs])) {
            nombre = grille[i][coord.abs];
            dep = 0;
            while ((dep + i < Nbligne) && (grille[i + dep][coord.abs] == nombre)) {
                grille[i + dep][coord.abs] = -1;
                ++nombresupp;
                ++dep;
            }
        }
        ++i;
    }
    if (grille[coord.ord][coord.abs] != -1 && cond == true) {
        grille[coord.ord][coord.abs] = -1;
    }
}

/**
 * @brief Remonte les chiffres sur la grille.
 * Fait remonter les valeurs pour combler les trous (-1) après la supression des alignements.
 * @param[in,out] grille La grille de jeu.
 * @param[in] Nbligne Nombre de lignes.
 * @param[in] Nbcolonne Nombre de colonnes.
 */
void remonteval (mat & grille,const long int & Nbligne,const long int & Nbcolonne) {
    //remonte de BAS EN HAUT les chiffres
    long int i = 0;
    long int j = 0;
    long int k;
    while( i < Nbcolonne ) {
        while (j < Nbligne) {
            k = j + 1;
            while ((k < Nbligne ) && (grille[j][i] == (-1))) {
                grille[j][i] = grille[k][i];
                grille[k][i] = (-1);
                ++k;
            }
            ++j;
        }
        ++i;
        j = 0;
    }
}

/**
 * @brief Vérifie s'il existe au moins un coup possible à partir d'une case.
 * @param[in,out] grille La grille
 * @param[in] Nbligne Nombre de lignes
 * @param[in] Nbcolonne Nombre de colonnes
 * @param[in] ordonnee Ligne de la case à verifier 
 * @param[in] abscisse Colonne de la case à verifier 
 * @return true Si un coup est possible depuis cette case.
 * @return false Sinon.
 */
bool verifiecoups (mat & grille, long int & Nbligne, long int & Nbcolonne, long int ordonnee, long int abscisse) {
    maPosition coord;
    char direction = 'a';
    coord.abs = abscisse;
    coord.ord = ordonnee;
    if (!(coord.abs <= 0)) {
        direction = 'q';
        if (possmove (grille,coord,direction,Nbligne,Nbcolonne)) {
            return true;
        }
    }
    if (!(coord.abs >= Nbcolonne - 1)) {
        direction = 'd';
        if (possmove (grille,coord,direction,Nbligne,Nbcolonne)) {
            return true;
        }
    }
    if (!(coord.ord <= 0)) {
        direction = 'z';
        if (possmove (grille,coord,direction,Nbligne,Nbcolonne)) {
            return true;
        }
    }
    if (!(coord.ord >= Nbligne - 1)) {
        direction = 's';
        if (possmove (grille,coord,direction,Nbligne,Nbcolonne)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Vérifie si le jeu est bloqué (aucun coup possible sur toute la grille).
 * @param[in,out] grille La grille
 * @param[in] Nbligne Nombre de lignes
 * @param[in] Nbcolonne Nombre de colonnes
 * @return true Si AUCUN coup possible donc fin du jeu
 * @return false Si au moins un coup est possible.
 */
bool findujeu (mat & grille, long int & Nbligne, long int & Nbcolonne){
    for (long int i = 0;i < Nbligne;++i) {
        for (long int j = 0 ; j < Nbcolonne; ++j) {
            if (verifiecoups (grille,Nbligne,Nbcolonne,i,j)) {
                return false;
            }
        }
    }
    return true;
}
/**
 * @brief Efface le contenu de la console.
 */
void clearScreen () {
    cout << "\033[H\033[2J";
}

/**
 * @brief Codes de couleurs ANSI pour la console
 * Reset la couleur
 */
const unsigned KReset   (0);
/**
 * @brief Codes de couleurs ANSI pour la console
 * Couleur Noir
 */
const unsigned KNoir    (30);
/**
 * @brief Codes de couleurs ANSI pour la consolec
 * Couleur Rouge
 */
const unsigned KRouge   (31);
/**
 * @brief Codes de couleurs ANSI pour la console
 * Couleur Vert
 */
const unsigned KVert    (32);
/**
 * @brief Codes de couleurs ANSI pour la console
 * Couleur Jaune
 */
const unsigned KJaune   (33);
/**
 * @brief Codes de couleurs ANSI pour la console
 * Couleur Bleu
 */
const unsigned KBleu    (34);
/**
 * @brief Codes de couleurs ANSI pour la console
 * Couleur Magenta
 */
const unsigned KMAgenta (35);
/**
 * @brief Codes de couleurs ANSI pour la console
 * Couleur Cyan
 */
const unsigned KCyan    (36);


/**
 * @brief Menu principal pour les modes Solo.
 * Propose au joueur de choisir entre les différents modes de jeu disponibles en solo.
 */
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
    while (true) {
        cout << "Quel mode choisir ?" << endl;
        cout << "1 : Mode normal" << endl << "2 : Mode personnalisé" << endl << "3 : Mode infini" << endl << "4 : Mode campagne" << endl << "5 : Règles du jeu" << endl;
        cout << "(ou 10 pour quitter)" << endl;
        cin >> mode;
        if (mode == 1) {
            modenormalsolo(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
        }
        else if (mode == 2) {
            modepersosolo(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
        }
        else if (mode == 3) {
            modenormalinfini(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
        }
        else if (mode == 4) {
            modehistoire();
        }
        else if (mode == 5) {
            reglesjeu();
        }
        else if (mode == 10) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide.";
        }
    }
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

/**
 * @brief Affiche le menu principal et lance le mode de jeu choisi
 * Permet de choisir entre Solo, Duo, ou quitter.
 */
void choixmode () {
    //menu principal qui permet le choix du mode voulu
    size_t mode;
    while (true) {
        cout << "Bienvenue !" << endl << "Sélectionnez le nombre de joueur" << endl;
        cout << "1 : Solo" << endl << "2 : Duo" << endl;
        cout << "(10 pour quitter)" << endl;
        cin >> mode;
        if (mode == 1) {
            modesolo();
        }
        else if (mode == 2) {
            modeduo();
        }
        else if (mode == 10) {
            break;
        }
        else {
            cout << "Entrez quelque chose de valide.";
        }
    }
}
/**
 * @brief main
 * Lance le menu pour jouer
 */
int main()
{
    srand(time(nullptr));
    choixmode();
    return 0;
}

