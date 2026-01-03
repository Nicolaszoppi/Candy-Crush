#include "solo.h"
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille

void chap1() {
}
void chap2() {
}
void chap3() {
}
void chap4() {
}
void chap5() {
}
void modehistoire() {
    int chap;
    while (true) {
    cout << "Sélectionnez un chapitre." << endl;
    cout << "1,2,3,4 ou 5." << endl << "(10 pour quitter)" << endl;
    cin >> chap;
    if (chap == 1) {
        chap1();
    }
    else if (chap == 2) {
        chap2();
    }
    else if (chap == 3) {
        chap3();
    }
    else if (chap == 4) {
        chap4();
    }
    else if (chap == 5) {
        chap5();
    }
    else if (chap == 10) {
        return;
    }
    }
}
