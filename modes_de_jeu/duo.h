#ifndef DUO_H
#define DUO_H
#include "solo.h"
#include <vector>
using namespace std;

typedef vector <short int> line; // un type représentant une ligne de la grille
typedef vector <line> mat; // un type représentant la grille

void tourjoueur (size_t joueur);
void modenormalduo (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & joueur);
void modepersoduo (unsigned long & score, unsigned long & nombredep, unsigned long & nombresupp , char & direction, maPosition & coord, long int & Nbligne,long int & Nbcolonne, size_t & KNbCandies,size_t & joueur);
#endif
