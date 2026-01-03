#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <modes_de_jeu/solo.h>
#include <modes_de_jeu/duo.h>
#include<cstdlib>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";//Définira la couleur de chaque chiffre
}
void souligner (const unsigned & chiffre) {//Souligne ou nous serons dans la matrice
    cout << "\033[4;" << chiffre << "m";
}
void creategrille (size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne,size_t & nbtour) {  //Crée une grille selon le nombre de chiffres possibles (commence à 3)
    cout << "Nombre max ?" << endl;
    while (true) {
        cin >> KNbCandies;
        if (KNbCandies < 3) {
            cout << "Il doit y avoir minimum 3 chiffres possibles." << endl;
        }
        else break;
    }
    Nbligne = KNbCandies*2;
    Nbcolonne= Nbligne;
    nbtour = KNbCandies*3;
    cout << "Taille de la grille : " << Nbligne << "*" << Nbcolonne << endl;
    cout << "Nombre de tours : " << nbtour << endl;
}
void creategrilleperso (size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne,size_t & nbtour) { //Crée une grille entièrement customisable (rectangulaire ou carrée)
    while (true) {
        cout << "Nombre max ?" << endl;
        cin >> KNbCandies;
        if (KNbCandies < 2) {
            cout << "Il doit y avoir minimum 2 chiffres possibles." << endl;
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
mat initGrid (mat & grille,const long int & Nbligne,const long int & Nbcolonne,const size_t & KNbCandies) { //Donne les valeurs aléatoirement dans chaque cases
    for (long int i = 0; i < Nbligne ; ++i) {
        for (long int j = 0; j < Nbcolonne;++j ) {
            grille[i][j] = rand()%KNbCandies + 1;
        }
    }
    return grille;
}
void displayGrid (mat & grille,const long int & Nbligne,const long int & Nbcolonne, const maPosition & coord) {//Affiche la grille sous forme de tableau
    for (long int i = 0; i < Nbligne ; ++i) {
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
void clearScreen () {
    cout << "\033[H\033[2J";
}
const unsigned KReset   (0);
const unsigned KNoir    (30);
const unsigned KRouge   (31);
const unsigned KVert    (32);
const unsigned KJaune   (33);
const unsigned KBleu    (34);
const unsigned KMAgenta (35);
const unsigned KCyan    (36);

void choixmode () {
    //menu principal qui permet le choix du mode voulu
    size_t mode;
    cout << "Bienvenue !" << endl << "Sélectionnez le nombre de joueur" << endl;
    cout << "1 : Solo" << endl << "2 : Duo" << endl;
    while (true) {
        cin >> mode;
        if (mode == 1) {
            modesolo();
        }
        else if (mode == 2) {
            modeduo();
        }
        else {
            cout << "Entrez quelque chose de valide.";
        }
    }
}
int main()
{
    srand(time(nullptr));
    choixmode();
    return 0;
}

