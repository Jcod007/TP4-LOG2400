#include "PointFactory.h"
#include "Point.h"
#include <sstream>
#include <algorithm>

vector<shared_ptr<GraphElement>> PointFactory::creerPointsDepuisChaine(const string& ligne) {
    vector<shared_ptr<GraphElement>> points;
    
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
    
    // Convertit en vecteur de shared_ptr<GraphElement>
    return points;
}

shared_ptr<Point> PointFactory::creerPoint(int x, int y) {
    return make_shared<Point>(make_pair(x, y));
}
