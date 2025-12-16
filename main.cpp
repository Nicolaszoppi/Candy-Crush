#include <iostream>
#include <vector>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
struct maPosition
{
    unsigned abs;
    unsigned ord;
}; // une position dans la grille

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}
void surligner (const unsigned & truc) {
    cout << "\033[4;" << truc << "m";
}

void initGrid (mat & grille,const size_t & Nbligne,const size_t & Nbcolonne,const unsigned & KNbCandies) {
    for (size_t i = 0; i < Nbligne ; ++i) {
        for (size_t j = 0; j < Nbcolonne;++j ) {
            grille[i][j] = rand()%KNbCandies + 1;
        }
    }
}
void displayGrid (mat & grille,const size_t & Nbligne,const size_t & Nbcolonne, const maPosition & coord) {
    for (size_t i = 0; i < Nbligne ; ++i) {
        for (size_t j = 0; j < Nbcolonne; ++j ) {
            if (j == coord.abs && i == coord.ord) {
                cout << "| ";
                surligner(31);
                couleur(30+grille[i][j]);
                cout << grille[i][j] << " ";
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

void makeAMove (mat & grille,maPosition & coord,char & direction,const size_t & Nbligne,const size_t & Nbcolonne ) {
    cout << "coordonnées ? (x,y)" << endl;
    while (true) {
        cin >> coord.abs;
        if ((coord.abs > Nbcolonne) | (coord.abs < 0)) {
            cout << "La position doit appartenir au tableau." << endl;
        }
        else break;
    }
    while (true) {
        cin >> coord.ord;
        if ((coord.ord > Nbligne) | (coord.ord < 0)) {
            cout << "La position doit appartenir au tableau." << endl;
        }
        else break;
    }
    size_t valeurtrans;
    while (true) {
        cout << "Entrez votre direction. (ZQSD) ou R pour revenir en arrière" << endl;
        cin >> direction;
        char directionmin = tolower(direction);
        if (directionmin == 'z') {
            if (coord.ord <= 0) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                coord.ord = coord.ord - 1;
                valeurtrans = grille[coord.ord][coord.abs];
                grille[coord.ord][coord.abs] = grille[coord.ord + 1][coord.abs];
                grille[coord.ord + 1][coord.abs] = valeurtrans;
                break;
            }
        }
        if (directionmin == 's') {
            if (coord.ord >= Nbligne) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                coord.ord = coord.ord + 1;
                valeurtrans = grille[coord.ord][coord.abs];
                grille[coord.ord][coord.abs] = grille[coord.ord - 1][coord.abs];
                grille[coord.ord - 1][coord.abs] = valeurtrans;
                break;
            }
        }
        if (directionmin == 'q') {
            if (coord.abs <= 0) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                coord.abs = coord.abs - 1;
                valeurtrans = grille[coord.ord][coord.abs];
                grille[coord.ord][coord.abs] = grille[coord.ord][coord.abs + 1];
                grille[coord.ord][coord.abs + 1] = valeurtrans;
                break;
            }
        }
        if (directionmin == 'd') {
            if (coord.abs >= Nbcolonne) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                coord.abs = coord.abs + 1;
                valeurtrans = grille[coord.ord][coord.abs];
                grille[coord.ord][coord.abs] = grille[coord.ord][coord.abs - 1];
                grille[coord.ord][coord.abs - 1] = valeurtrans;
                break;
            }
        }
        if (directionmin == 'r') break;

    }

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


int main()
{
    char direction = 'a';
    maPosition coord;
    size_t Nbligne;
    size_t Nbcolonne;
    unsigned int KNbCandies;
    cout << "Nombre max ?" << endl;
    cin >> KNbCandies;
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
    Nbcolonne = Nbcolonne + 1;
    Nbligne = Nbligne + 1;
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille,Nbligne,Nbcolonne, KNbCandies);
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (true) {
        makeAMove (grille,coord,direction,Nbligne,Nbcolonne);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
    }



}
