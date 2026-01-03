#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;
typedef vector<unsigned> line;
typedef vector<line> mat;
struct maPosition {
    unsigned abs;
    unsigned ord;
};

const unsigned KNbCandies = 9;
const unsigned KImpossible = 0;
const unsigned KMaxCoupsClassique = 20;

void couleur(const unsigned & coul) {
    cout << "\033[" << coul << "m";
}
void clearScreen() {
    cout << "\033[H\033[2J";
}

void initGrid(mat & grid, const size_t & matSize) {
    grid.assign(matSize, line(matSize));
    for (size_t i = 0; i < matSize; ++i) {
        for (size_t j = 0; j < matSize; ++j) {
            grid[i][j] = 1 + rand() % KNbCandies;
        }
    }
}

void displayGrid(const mat & grid) {
    clearScreen();
    cout << "    ";
    for(size_t j = 0; j < grid.size(); ++j) cout << j << " ";
    cout << endl << "   " << string(grid.size() * 2, '-') << endl;

    for (size_t i = 0; i < grid.size(); ++i) {
        if(i < 10) cout << i << " | ";
        else cout << i << "| ";
        for (size_t j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == KImpossible) cout << "  ";
            else {
                couleur(30 + grid[i][j]);
                cout << grid[i][j] << " ";
                couleur(0);
            }
        }
        cout << "|" << endl;
    }
    cout << "   " << string(grid.size() * 2, '-') << endl;
}

void refillColumn(mat & grid, unsigned col, unsigned startRow, unsigned howMany) {
    for (int i = (int)startRow - 1; i >= 0; --i) {
        grid[i + howMany][col] = grid[i][col];
    }
    for (unsigned i = 0; i < howMany; ++i) {
        grid[i][col] = 1 + rand() % KNbCandies;
    }
}

bool atLeastThreeInAColumn(const mat & grid, maPosition & pos, unsigned & howMany) {
    for (size_t j = 0; j < grid.size(); ++j) {
        for (size_t i = 0; i < grid.size() - 2; ++i) {
            if (grid[i][j] != KImpossible && grid[i][j] == grid[i+1][j] && grid[i][j] == grid[i+2][j]) {
                pos.ord = (unsigned)i;
                pos.abs = (unsigned)j;
                howMany = 3;
                while (i + howMany < grid.size() && grid[i + howMany][j] == grid[i][j]) howMany++;
                return true;
            }
        }
    }
    return false;
}

bool atLeastThreeInARow(const mat & grid, maPosition & pos, unsigned & howMany) {
    for (size_t i = 0; i < grid.size(); ++i) {
        for (size_t j = 0; j < grid.size() - 2; ++j) {
            if (grid[i][j] != KImpossible && grid[i][j] == grid[i][j+1] && grid[i][j] == grid[i][j+2]) {
                pos.ord = (unsigned)i;
                pos.abs = (unsigned)j;
                howMany = 3;
                while (j + howMany < grid.size() && grid[i][j + howMany] == grid[i][j]) howMany++;
                return true;
            }
        }
    }
    return false;
}

void makeAMove(mat & grid, const maPosition & pos, char direction) {
    size_t taille = grid.size();
    unsigned x = pos.abs;
    unsigned y = pos.ord;
    direction = (char)tolower(direction);

    if (direction == 'z' && y > 0) swap(grid[y][x], grid[y-1][x]);
    else if (direction == 's' && y < taille - 1) swap(grid[y][x], grid[y+1][x]);
    else if (direction == 'q' && x > 0) swap(grid[y][x], grid[y][x-1]);
    else if (direction == 'd' && x < taille - 1) swap(grid[y][x], grid[y][x+1]);
}



int displayMenu() {
    int choix;
    clearScreen();
    cout << "" << endl;
    cout << "CANDY CRUSH BUT1" << endl;
    cout << "1. Mode Classique" << endl;
    cout << "2. Mode Infini" << endl;
    cout << "0. Quitter" << endl;
    cout << "" << endl;
    cout << "Votre choix : ";
    cin >> choix;
    return choix;
}


int main() {
    srand((unsigned)time(NULL));
    mat grid;
    size_t taille;
    unsigned score = 0, coups = 0;

    // Appel de la fonction menu
    int mode = displayMenu();

    if (mode == 0) return 0;

    cout << "Taille de la grille ? ";
    cin >> taille;
    if (taille < 4) taille = 4;
    initGrid(grid, taille);

    while (mode == 2 || (mode == 1 && coups < KMaxCoupsClassique)) {
        displayGrid(grid);
        cout << "Score : " << score;
        if (mode == 1) cout << " | Coups : " << coups << "/" << KMaxCoupsClassique;
        else cout << " | Mode : INFINI (999 pour quitter)";
        cout << endl;

        maPosition p;
        char dir;

        cout << "Ligne : ";
        cin >> p.ord;
        if (p.ord == 999) break;

        cout << "Colonne : ";
        cin >> p.abs;

        cout << "Direction (Z,Q,S,D) : ";
        cin >> dir;

        if (cin.fail() || p.ord >= taille || p.abs >= taille) {
            cin.clear(); cin.ignore(100, '\n');
            continue;
        }

        makeAMove(grid, p, dir);
        coups++;

        bool encore = true;
        while (encore) {
            encore = false;
            maPosition matchP; unsigned nb;
            if (atLeastThreeInAColumn(grid, matchP, nb)) {
                score += nb;
                refillColumn(grid, matchP.abs, matchP.ord, nb);
                encore = true;
            } else if (atLeastThreeInARow(grid, matchP, nb)) {
                score += nb;
                for (unsigned k = 0; k < nb; ++k) refillColumn(grid, matchP.abs + k, matchP.ord, 1);
                encore = true;
            }
            if(encore) displayGrid(grid);
        }
    }

    displayGrid(grid);
    cout << "PARTIE TERMINEE ! Score : " << score << endl;
    return 0;
}
