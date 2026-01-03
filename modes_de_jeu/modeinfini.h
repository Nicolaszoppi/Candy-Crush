#ifndef MODEINFINI_H
#define MODEINFINI_H
#include "solo.h"

#include <vector>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille
int makeAMoveinfini (mat & grille,maPosition & coord,char & direction,unsigned long & nombredep,const long int & Nbligne,const long int & Nbcolonne);
void scorejeuinfini (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp);
void rempliColonne(mat & grille, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies);
void modenormalinfini (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies);
#endif
