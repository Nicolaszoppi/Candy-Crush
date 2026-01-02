#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
struct maPosition //Permet de définir les coordonnées dans la matrice
{
    long int abs;
    long int ord;
}; // une position dans la grille

void couleur (const unsigned & coul) {
    cout << "\033[" << coul <<"m";//Définira la couleur de chaque chiffre
}
void souligner (const unsigned & truc) {//Souligne ou nous serons dans la matrice
    cout << "\033[4;" << truc << "m";
}
void creategrille (size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne) {  //Crée une grille selon le nombre de chiffres possibles (commence à 3)
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
}
void creategrilleperso (size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne) { //Crée une grille entièrement customisable (rectangulaire ou carrée)
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
}

void initGrid (mat & grille,const long int & Nbligne,const long int & Nbcolonne,const size_t & KNbCandies) { //Donne les valeurs aléatoirement dans chaque cases
    for (long int i = 0; i < Nbligne ; ++i) {
        for (long int j = 0; j < Nbcolonne;++j ) {
            grille[i][j] = rand()%KNbCandies + 1;
        }
    }
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

void makeAMove (mat & grille,maPosition & coord,char & direction,unsigned long & nombredep,const long int & Nbligne,const long int & Nbcolonne ) {
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
                coord.ord = coord.ord - 1;
                valeurtrans = grille[coord.ord][coord.abs];
                grille[coord.ord][coord.abs] = grille[coord.ord + 1][coord.abs];
                grille[coord.ord + 1][coord.abs] = valeurtrans;
                ++nombredep;
                break;
            }
        }
        if (directionmin == 's') {
            if (coord.ord >= Nbligne - 1) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                coord.ord = coord.ord + 1;
                valeurtrans = grille[coord.ord][coord.abs];
                grille[coord.ord][coord.abs] = grille[coord.ord - 1][coord.abs];
                grille[coord.ord - 1][coord.abs] = valeurtrans;
                ++nombredep;
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
                ++nombredep;
                break;
            }
        }
        if (directionmin == 'd') {
            if (coord.abs >= Nbcolonne - 1) {
                cout << "Vous ne pouvez pas avancer plus" << endl;
            }
            else {
                coord.abs = coord.abs + 1;
                valeurtrans = grille[coord.ord][coord.abs];
                grille[coord.ord][coord.abs] = grille[coord.ord][coord.abs - 1];
                grille[coord.ord][coord.abs - 1] = valeurtrans;
                ++nombredep;
                break;
            }
        }
        if (directionmin == 'r') {//revient en arrière en cas d'erreur
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
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }

    }

}
bool litalign (const mat & grille, maPosition & coord,const long int & Nbligne,const long int & Nbcolonne) {
    //permet de trouver si il y a un alignement vertical ou horizontal de minimum trois mêmes chiffre d'affilée
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
void scorejeu (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp) {
    //affiche le score après chaque déplacement et aussi le nombre de déplacement
    cout << "Nombre de déplacements : " << nombredep << endl;
    if (nombredep < 3) {//méthode du calcul du score
        score = score + (nombresupp * 10 * (4 - nombredep));
    }
    else {
        score = score + (nombresupp * 10);
    }
    cout << "Score : " << score << endl;
    nombresupp = 0;

}
bool findujeu (mat & grille,size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne) {
    //vérifie après chaque déplacement si il est possible de continuer (si non, le jeu est terminé)
    long int nombregal = 0;
    for (size_t val = 1; val < KNbCandies; ++val){
        for (long int i = 0; i < Nbcolonne; ++i) {
            for (long int j = 0; j < Nbligne - 1; ++j){
                for (long int k = 1; k < Nbligne - j; ++k) {
                    if (grille[j][i] == grille[j+k][i]) {
                        ++nombregal;
                        if (nombregal >= 3) {
                            return false;
                        }
                    }
                }
            }
        }
        nombregal = 0;
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

/**
 * @brief main
 * @return
 */
void modenormal (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    creategrille (KNbCandies, Nbligne,Nbcolonne);
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu (grille, KNbCandies, Nbligne,Nbcolonne)) {
        srand(time(nullptr));
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille, KNbCandies, Nbligne,Nbcolonne)) {
        makeAMove (grille,coord,direction,nombredep,Nbligne,Nbcolonne);
        if (litalign(grille,coord,Nbligne,Nbcolonne)== true) {
            suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
            remonteval (grille,Nbligne,Nbcolonne);
            displayGrid(grille, Nbligne,Nbcolonne,coord);
            scorejeu(score,nombredep,nombresupp);
        }
        else {
            displayGrid(grille, Nbligne,Nbcolonne,coord);
        }
    }
    cout << "Partie terminée !" << endl;
    scorejeu(score,nombredep,nombresupp);
}
void modeperso (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    creategrilleperso (KNbCandies, Nbligne,Nbcolonne);
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille,Nbligne,Nbcolonne, KNbCandies);
    while (findujeu (grille, KNbCandies, Nbligne,Nbcolonne)) {
        srand(time(nullptr));
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille, KNbCandies, Nbligne,Nbcolonne)) {
        makeAMove (grille,coord,direction,nombredep,Nbligne,Nbcolonne);
        if (litalign(grille,coord,Nbligne,Nbcolonne)== true) {
            suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
            remonteval (grille,Nbligne,Nbcolonne);
            displayGrid(grille, Nbligne,Nbcolonne,coord);
            scorejeu(score,nombredep,nombresupp);
        }
        else {
            displayGrid(grille, Nbligne,Nbcolonne,coord);
        }
    }
    cout << "Partie terminée !" << endl;
    scorejeu(score,nombredep,nombresupp);

}
void choixmode () {
    //menu principal qui permet le choix du mode voulu
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
    cout << "Bienvenue !" << endl << "Quel mode choisir ?" << endl;
    cout << "1 : Mode normal" << endl << "2 : Mode personnalisé" << endl;
    while (true) {
        cin >> mode;
        if (mode == 1) {
            modenormal(score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
        }
        else if (mode == 2) {
            modeperso (score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
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

