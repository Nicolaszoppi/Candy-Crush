#ifndef SOLO_H
#define SOLO_H

#include <vector>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
struct maPosition //Permet de définir les coordonnées dans la matrice
{
    long int abs;
    long int ord;
}; // une position dans la grille
void couleur (const unsigned & coul);
void souligner (const unsigned & chiffre);
void creategrille (size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne, size_t & nbtour);
void creategrilleperso (size_t & KNbCandies, long int & Nbligne, long int & Nbcolonne,size_t & nbtour);
bool litalign (const mat & grille, maPosition & coord,const long int & Nbligne,const long int & Nbcolonne);
mat initGrid (mat & grille,const long int & Nbligne,const long int & Nbcolonne,const size_t & KNbCandies);
void displayGrid (mat & grille,const long int & Nbligne,const long int & Nbcolonne, const maPosition & coord);
bool possmove (mat & grille, maPosition & coord,char & direction,const long int & Nbligne,const long int & Nbcolonne);
void initmove (mat & grille,maPosition & coord,const long int & Nbligne,const long int & Nbcolonne );
void makeAMove (mat & grille,maPosition & coord,char & direction,unsigned long & nombredep,const long int & Nbligne,const long int & Nbcolonne,size_t & nbtour );
void suppressiondoublons (mat & grille, const maPosition & coord,const long int & Nbligne,const long int & Nbcolonne,unsigned long & nombresupp);
void remonteval (mat & grille,const long int & Nbligne,const long int & Nbcolonne);
void scorejeu (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp,size_t & nbtour);
bool verifiecoups (mat & grille, long int & Nbligne, long int & Nbcolonne, long int ordonnee, long int abscisse);
bool findujeu (mat & grille, long int & Nbligne, long int & Nbcolonne);
void clearScreen ();
void modenormalsolo (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies);
void modepersosolo (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies);
void modesolo();
#endif
