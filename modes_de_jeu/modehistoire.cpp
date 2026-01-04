#include "solo.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <limits>
#include "modeinfini.h"
using namespace std;

typedef vector <short int> line;
typedef vector <line> mat;
void verifnom(string & nom) {
    while (true) {
        if (nom == "&") {
            cout << "Entrez votre nom : " << endl;
            cin >> nom;
            cin.get();//Demande d'appuyer sur quelque chose
            if (nom == "&") {
                cout << "Entrez un autre nom." << endl;
            }
            else break;
        }
        else break;
    }
}
int condchap3(mat grille, long int & Nbligne,long int & Nbcolonne) {
    int nombrevide =0;
    for (long int i = 0; i < Nbligne; ++i) {
        for (long int j = 0; j < Nbcolonne; ++j) {
            if (grille[i][j] == -1) {
                ++nombrevide;
            }
        }
    }
    return nombrevide;
}
int condchap5(mat & grille, long int & Nbligne,long int & Nbcolonne) {
    int nombrevide = 0;
    for (long int i = 0; i < Nbligne; ++i) {
        for (long int j = 0; j < Nbcolonne; ++j) {
            if (grille[i][j] == -1) {
                ++nombrevide;
            }
        }
    }
    return nombrevide;
}
void niveau1(string & nom,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    cout << "Ton objectif, " << nom << ", est de seulement terminer la partie." << endl;
    cout << "Appuyez sur Entrée pour commencer." << endl;
    cin.get();
    score = 0;
    nombredep = 0;
    nombresupp = 0;
    coord.abs = 0;
    coord.ord = 0;
    Nbligne = 4;
    Nbcolonne = Nbligne;
    KNbCandies = 2;
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille, Nbligne,Nbcolonne,KNbCandies);
    while (findujeu (grille,Nbligne,Nbcolonne)) {
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille,Nbligne,Nbcolonne)) {
        makeAMoveinfini (grille,coord,direction,nombredep,Nbligne,Nbcolonne);
        suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
        remonteval (grille,Nbligne,Nbcolonne);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeuinfini(score,nombredep,nombresupp);
    }
    cout << "Partie terminée !" << endl;
    scorejeuinfini(score,nombredep,nombresupp);
}
void niveau2(string & nom,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    cout << "Ton objectif, " << nom << ", est de terminer la partie, mais la grille est bien plus complexe." << endl;
    cout << "Appuyez sur Entrée pour commencer." << endl;
    cin.get();
    score = 0;
    nombredep = 0;
    nombresupp = 0;
    coord.abs = 0;
    coord.ord = 0;
    Nbligne = 6;
    Nbcolonne = Nbligne;
    KNbCandies = 4;
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille, Nbligne,Nbcolonne,KNbCandies);
    while (findujeu (grille,Nbligne,Nbcolonne)) {
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille,Nbligne,Nbcolonne)) {
        makeAMoveinfini(grille,coord,direction,nombredep,Nbligne,Nbcolonne);
        suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
        remonteval (grille,Nbligne,Nbcolonne);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeuinfini(score,nombredep,nombresupp);
    }
    cout << "Partie terminée !" << endl;
    scorejeuinfini(score,nombredep,nombresupp);
}
bool niveau3(string & nom,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    cout << "Ton objectif, " << nom << ", est de terminer la partie, mais en éliminant au moins 15 chiffres." << endl;
    cout << "Appuyez sur Entrée pour commencer." << endl;
    cin.get();
    score = 0;
    nombredep = 0;
    nombresupp = 0;
    coord.abs = 0;
    coord.ord = 0;
    Nbligne = 6;
    Nbcolonne = Nbligne;
    KNbCandies = 3;
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille, Nbligne,Nbcolonne,KNbCandies);
    while (findujeu (grille,Nbligne,Nbcolonne)) {
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille,Nbligne,Nbcolonne)) {
        makeAMoveinfini (grille,coord,direction,nombredep,Nbligne,Nbcolonne);
        suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
        remonteval (grille,Nbligne,Nbcolonne);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeuinfini(score,nombredep,nombresupp);
    }
    cout << "Partie terminée !" << endl;
    if (condchap3(grille,Nbligne,Nbcolonne) >= 15) {
        cout << "Vous avez gagné !" << endl;
        return true;
    }
    else {
        cout << "Vous n'avez pas rempli la condition." << endl;
        return false;
    }
}
bool niveau4(string & nom,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & nbtour) {
    cout << "Ton objectif, " << nom << ", est de finir le niveau en moins de 10 tours." << endl;
    cout << "Appuyez sur Entrée pour commencer." << endl;
    cin.get();
    score = 0;
    nbtour = 10;
    nombredep = 0;
    nombresupp = 0;
    coord.abs = 0;
    coord.ord = 0;
    Nbligne = 6;
    Nbcolonne = 8;
    KNbCandies = 4;
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille, Nbligne,Nbcolonne,KNbCandies);
    while (findujeu (grille,Nbligne,Nbcolonne)) {
        initGrid (grille,Nbligne,Nbcolonne, KNbCandies);
    }
    displayGrid(grille, Nbligne,Nbcolonne,coord);
    while (!findujeu (grille,Nbligne,Nbcolonne)) {
        makeAMove (grille,coord,direction,nombredep,Nbligne,Nbcolonne,nbtour);
        suppressiondoublons(grille,coord,Nbligne,Nbcolonne,nombresupp);
        remonteval (grille,Nbligne,Nbcolonne);
        displayGrid(grille, Nbligne,Nbcolonne,coord);
        scorejeu(score,nombredep,nombresupp,nbtour);
        if (nbtour == 0) {
            cout << "Temps écoulé" << endl << "Vous avez perdu !" << endl;
            return false;
        }
    }
    cout << "Partie terminée !" << endl;
    cout << "Vous avez gagné !" << endl;
    scorejeu(score,nombredep,nombresupp,nbtour);
    return true;
}
bool niveau5(string & nom,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & nbtour) {
    cout << "Je vois tout... " << "Comment vaincre le démon... " << endl;
    cout << "Objectif : " << nom << " doit éliminer au moins 45 chiffres en moins de 16 tours !!" << endl;
    cout << "Appuyez sur Entrée pour commencer." << endl;
    cin.get();
    score = 0;
    nbtour = 16;
    nombredep = 0;
    nombresupp = 0;
    coord.abs = 0;
    coord.ord = 0;
    Nbligne = 8;
    Nbcolonne = 8;
    KNbCandies = 4;
    mat grille(Nbligne,line (Nbcolonne,0));
    initGrid(grille, Nbligne,Nbcolonne,KNbCandies);
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
        if (nbtour == 0) {
            cout << "Temps écoulé" << endl;
        }
    }
    cout << "Partie terminée !" << endl;
    if (condchap5(grille,Nbligne,Nbcolonne) >= 45) {
        cout << "Vous avez vaincu Mickaël !!" << endl;
        return true;
    }
    else {
        cout << "Vous avez perdu !";
        return false;
    }
}
void affichetxt(ifstream & fichier, int val) {
    string ligne;
    for(int i = 0; i< val; ++i){
        getline(fichier,ligne);
        if (fichier.eof())break;
        cout << ligne << endl;
    }

}
void ajourtxt(ifstream & fichier, int val) {
    string ligne;
    for(int i = 0; i< val; ++i){
        getline(fichier,ligne);
        if (fichier.eof())break;
    }

}
void chap5(string & nom,ifstream & fichier,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & nbtour) {
    int nombre;
    fichier.seekg(0);
    ajourtxt(fichier, 153);
    affichetxt(fichier,128);
    cout << "(Appuyez sur entrée)"<< endl;
    cin.get();
    affichetxt(fichier,6);
    while (true) {
        cout << "Appuyez sur 1 pour commencer le jeu, 2 pour voir les règles et 3 pour quitter."<< endl;
        cin >> nombre;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nombre == 1) {
            //if (niveau5(nom,score,nombredep,nombresupp , direction,coord,Nbligne,Nbcolonne,KNbCandies,nbtour)) break;
            break;
        }
        else if (nombre == 2) {
            reglesjeu();
        }
        else if (nombre == 3) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
    affichetxt(fichier,5);
    cout << "(Appuyez sur entrée)"<< endl;
    cin.get();
    affichetxt(fichier,13);
    cout << endl << "Merci d'avoir joué !!" << endl << endl;
}
void chap4(string & nom,ifstream & fichier,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & nbtour) {
    int nombre;
    fichier.seekg(0);
    ajourtxt(fichier, 137);
    affichetxt (fichier,9);
    while (true) {
        cout << "Appuyez sur 1 pour commencer le jeu, 2 pour voir les règles et 3 pour quitter."<< endl;
        cin >> nombre;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nombre == 1) {
            //if (niveau4(nom,score,nombredep,nombresupp , direction,coord,Nbligne,Nbcolonne,KNbCandies,nbtour)) break;
            break;
        }
        else if (nombre == 2) {
            reglesjeu();
        }
        else if (nombre == 3) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
    affichetxt (fichier,4);
    cout << endl;
    while (true) {
        cout << "Passez au prochain chapitre ?"<< endl << "1 : Oui" << endl << "2 : Non" << endl;
        cin >> nombre;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nombre == 1) {
            cout << endl;
            chap5(nom,fichier,score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies,nbtour);
            break;
        }
        else if (nombre == 2) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
}
void chap3(string & nom,ifstream & fichier,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    size_t nbtour = 0;
    int nombre;
    fichier.seekg(0);
    ajourtxt(fichier, 123);
    affichetxt (fichier,9);
    while (true) {
        cout << "Appuyez sur 1 pour commencer le jeu, 2 pour voir les règles et 3 pour quitter."<< endl;
        cin >> nombre;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nombre == 1) {
            //if (niveau3(nom,score,nombredep,nombresupp , direction,coord,Nbligne,Nbcolonne,KNbCandies)) break;
            break;
        }
        else if (nombre == 2) {
            reglesjeu();
        }
        else if (nombre == 3) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
    affichetxt (fichier,4);
    cout << endl;
    while (true) {
        cout << "Passez au prochain chapitre ?"<< endl << "1 : Oui" << endl << "2 : Non" << endl;
        cin >> nombre;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nombre == 1) {
            cout << endl;
            chap4(nom,fichier,score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies,nbtour);
            break;
        }
        else if (nombre == 2) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
}
void chap2(string & nom,ifstream & fichier,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    int nombre;
    fichier.seekg(0);
    ajourtxt(fichier, 107);
    affichetxt (fichier,11);
    while (true) {
        cout << "Appuyez sur 1 pour commencer le jeu, 2 pour voir les règles et 3 pour quitter."<< endl;
        cin >> nombre;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nombre == 1) {
            //niveau2 (nom,score,nombredep,nombresupp , direction,coord,Nbligne,Nbcolonne,KNbCandies,nbtour);
            break;
        }
        else if (nombre == 2) {
            reglesjeu();
        }
        else if (nombre == 3) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
    affichetxt (fichier,4);
    cout << endl;
    while (true) {
        cout << "Passez au prochain chapitre ?"<< endl << "1 : Oui" << endl << "2 : Non" << endl;
        cin >> nombre;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nombre == 1) {
            cout << endl;
            chap3(nom,fichier,score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
            break;
        }
        else if (nombre == 2) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
}


void chap1(string & nom,ifstream & fichier,unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies) {
    int nombre;
    fichier.seekg(0);
    affichetxt(fichier,8);
    cout << "(Appuyez sur entrée)"<< endl;
    cin.get();
    affichetxt(fichier,92);
    verifnom(nom);
    cout << "Tu t'appelles donc " << nom << "...";
    affichetxt(fichier,4);
    while (true) {
        cout << "Appuyez sur 1 pour commencer le jeu, 2 pour voir les règles et 3 pour quitter."<< endl;
        cin >> nombre;
        cin.get();
        if (nombre == 1) {
            //niveau1 (nom,score,nombredep,nombresupp , direction,coord,Nbligne,Nbcolonne,KNbCandies);
            break;
        }
        else if (nombre == 2) {
            reglesjeu();
        }
        else if (nombre == 3) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
    affichetxt(fichier,3);
    cout << endl;
    while (true) {
        cout << "Passez au prochain chapitre ?"<< endl << "1 : Oui" << endl << "2 : Non" << endl;
        cin >> nombre;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (nombre == 1) {
            cout << endl;
            chap2(nom,fichier,score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
            break;
        }
        else if (nombre == 2) {
            return;
        }
        else {
            cout << "Entrez quelque chose de valide." << endl;
        }
    }
}
void modehistoire() {
    ifstream fichier("../../modehistoirenarration.txt");
    if (!fichier) {
        cout << "Erreur ouverture fichier narration !" << endl;
        return;
    }
    int chap;
    size_t score = 0;
    size_t nbtour = 0;
    size_t nombredep = 0;
    size_t nombresupp = 0;
    char direction;
    maPosition coord;
    coord.abs = 0;
    coord.ord = 0;
    long int Nbligne;
    long int Nbcolonne;
    size_t KNbCandies;
    string nom = "&";
    while (true) {
        cout << "--------/!\\ Mettez en plein écran pour une expérience optimale /!\\--------" << endl;
    cout << "Sélectionnez un chapitre." << endl;
    cout << "1,2,3,4 ou 5." << endl << "(10 pour quitter)" << endl;
    cin >> chap;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (chap == 1) {
        chap1(nom,fichier,score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
    }
    else if (chap == 2) {
        verifnom(nom);
        chap2(nom,fichier,score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
    }
    else if (chap == 3) {
        verifnom(nom);
        chap3(nom,fichier,score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies);
    }
    else if (chap == 4) {
        verifnom(nom);
        chap4(nom,fichier,score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies,nbtour);
    }
    else if (chap == 5) {
        verifnom(nom);
        chap5(nom,fichier,score,nombredep,nombresupp,direction,coord,Nbligne,Nbcolonne,KNbCandies,nbtour);
    }
    else if (chap == 10) {
        return;
    }
    }
}
