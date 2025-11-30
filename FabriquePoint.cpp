#include "FabriquePoint.h"
#include "Point.h"
#include <sstream>
#include <algorithm>
using namespace std;

vector<shared_ptr<ElementGraphique>> FabriquePoint::creerPointsDepuisChaine(const string& ligne) {
    vector<shared_ptr<ElementGraphique>> points;
    
    // On crée un flux de lecture (istringstream) à partir de la chaîne ligne.
    istringstream iss(ligne);
    string token;
    
    // On lit chaque point de la ligne (séparé par des espaces).
    while (iss >> token) {
        // On vérifie que le point est entre parenthèses
        if (token.size() >= 3 && token.front() == '(' && token.back() == ')') {
            // On enlève les parenthèses au début et à la fin.
            token = token.substr(1, token.size() - 2);
            // On remplace la virgule par un espace.
            replace(token.begin(), token.end(), ',', ' ');
            // On crée un flux de lecture pour chaque point
            istringstream pair(token);
            int x, y;
            // On ajoute un point {x, y} au vecteur de points.
            if (pair >> x >> y) {
                points.push_back(make_shared<Point>(make_pair(x, y)));
            }
        }
    }
    
    // Convertit en vecteur de shared_ptr<ElementGraphique>
    return points;
}

shared_ptr<Point> FabriquePoint::creerPoint(int x, int y) {
    return make_shared<Point>(make_pair(x, y));
}
