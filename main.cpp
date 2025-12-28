#include <iostream>
#include <vector>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
struct maPosition
{
    long int abs;
    long int ord;
}; // une position dans la grille

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";
}
void surligner (const unsigned & truc) {
    cout << "\033[4;" << truc << "m";
}
void creategrille (size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne) {
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
}

void initGrid (mat & grille,const long int & Nbligne,const long int & Nbcolonne,const size_t & KNbCandies) {
    for (long int i = 0; i < Nbligne ; ++i) {
        for (long int j = 0; j < Nbcolonne;++j ) {
            grille[i][j] = rand()%KNbCandies + 1;
        }
    }
}
void displayGrid (mat & grille,const long int & Nbligne,const long int & Nbcolonne, const maPosition & coord) {
    for (long int i = 0; i < Nbligne ; ++i) {
        for (long int j = 0; j < Nbcolonne; ++j ) {
            if (j == coord.abs && i == coord.ord) {
                cout << "| ";
                surligner(4);
                couleur(30+grille[i][j]);
                if (grille[i][j] == -1) {
                    cout << " ";
                    surligner(24);
                    cout << " ";
                }
                else {
                    cout << grille[i][j];
                    surligner(24);
                    cout << " ";
                }
                couleur(0);
            }
            else if (grille[i][j] == -1) {
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

void makeAMove (mat & grille,maPosition & coord,char & direction,const long int & Nbligne,const long int & Nbcolonne ) {
    cout << "coordonnées ? (x,y)" << endl;
    while (true) {
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
        if (grille[coord.ord][coord.abs] == (-1)) {
            cout << "il n'y a rien ici.";
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
bool litdoublon (const mat & grille, maPosition & coord, unsigned & nombrechaine,const long int & Nbligne,const long int & Nbcolonne) {
    nombrechaine = 0;
    long int i = coord.ord;
    while (i <= Nbcolonne) {
        if (grille[i][coord.abs] == grille[coord.ord][coord.abs]){
            nombrechaine = nombrechaine + 1;
            ++i;
        }
        else break;
    }
    i = coord.ord;
    while (i >= 0) {
        if (grille[i][coord.abs] == grille[coord.ord][coord.abs]){
            nombrechaine = nombrechaine + 1;
            --i;
        }
        else break;
    }
    i = coord.abs;
    while (i <= Nbligne) {
        if (grille[coord.ord][i] == grille[coord.ord][coord.abs]){
            nombrechaine = nombrechaine + 1;
            ++i;
        }
        else break;
    }
    i = coord.abs;
    while (i >= 0) {
        if (grille[coord.ord][i] == grille[coord.ord][coord.abs]){
            nombrechaine = nombrechaine + 1;
            --i;
        }
        else break;
    }
    if (nombrechaine - 3 >= 3) {
        return true;
    }
    else return false;
}
void suppressiondoublons (mat & grille, const maPosition & coord,const long int & Nbligne,const long int & Nbcolonne) {
    long int doublon = grille[coord.ord][coord.abs];
    /**size_t valeurtrans;
    */
    long int i = coord.ord;
    while (i <= Nbcolonne) {
        if (grille[i][coord.abs] == doublon){
            grille[i][coord.abs] = (-1);
            ++i;
        }
        else if (grille[i][coord.abs] == (-1)) {
            ++i;
        }
        else break;
    }
    i = coord.ord;
    while (i >= 0) {
        if (grille[i][coord.abs] == doublon){
            grille[i][coord.abs] = (-1);
            --i;
        }
        else if (grille[i][coord.abs] == (-1)) {
            --i;
        }
        else break;
    }
    i = coord.abs;
    while (i <= Nbligne) {
        if (grille[coord.ord][i] == doublon){
            grille[coord.ord][i] = (-1);
            ++i;
        }
        else if (grille[coord.ord][i] == (-1)) {
            ++i;
        }
        else break;
    }
    i = coord.abs;
    while (i >= 0) {
        if (grille[coord.ord][i] == doublon){
            grille[coord.ord][i] = (-1);
            --i;
        }
        else if (grille[coord.ord][i] == (-1)) {
            --i;
        }
        else break;
    }
    i = 0;
}
void remonteval (mat & grille, const maPosition & coord,const long int & Nbligne,const long int & Nbcolonne) {
    long int i = Nbligne;
    while (i >= 0) {
        long int j = Nbcolonne;
        while (j >= 0) {
            if (j == 0) {
                --j;
            }
            else if (grille[i][j] == (-1)) {
                cout << "tg";
            }
        }


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

/**
 * @brief main
 * @return
 */
int main()
{
    unsigned nombrechaine = 0;
    char direction = 'a';
    maPosition coord;
    long int Nbligne;
    long int Nbcolonne;
    size_t KNbCandies;
    creategrille (KNbCandies, Nbligne,Nbcolonne);
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille,Nbligne,Nbcolonne, KNbCandies);
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (true) {
        makeAMove (grille,coord,direction,Nbligne,Nbcolonne);
        if (litdoublon(grille,coord,nombrechaine,Nbligne,Nbcolonne)) {
            suppressiondoublons(grille,coord,Nbligne,Nbcolonne);
            displayGrid(grille, Nbligne,Nbcolonne,coord);
            break;
        }
        displayGrid(grille, Nbligne,Nbcolonne,coord);
    }
    return 0;
}
/**
    unsigned litdoubloncolonne (const mat & grille, maPosition & coord, unsigned & nombrechaine,const size_t & Nbcolonne) {
    nombrechaine = 0;
    int i = coord.ord;
    while (i <= Nbcolonne) {
        if (grille[i][coord.abs] == grille[coord.ord][coord.abs]){
            nombrechaine = nombrechaine + 1;
            ++i;
            cout << i << endl;
        }
        else break;
    }
    i = coord.ord;
    while (i >= 0) {
        if (grille[i][coord.abs] == grille[coord.ord][coord.abs]){
            nombrechaine = nombrechaine + 1;
            --i;
            cout << i << endl;
        }
        else break;
    }
    return nombrechaine - 1;
}
unsigned litdoublonligne (const mat & grille, maPosition & coord, unsigned & nombrechaine,const size_t & Nbligne) {
    nombrechaine = 0;
    size_t i = coord.abs;
    while (i <= Nbligne) {
        if (grille[coord.ord][i] == grille[coord.ord][coord.abs]){
            nombrechaine = nombrechaine + 1;
            ++i;
            cout << i << endl;
        }
        else break;
    }
    i = coord.abs;
    while (i >= 0) {
        if (grille[coord.ord][i] == grille[coord.ord][coord.abs]){
            nombrechaine = nombrechaine + 1;
            --i;
            cout << i << endl;
        }
        else break;
    }
    return nombrechaine - 1;
}
*/
