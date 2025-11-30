#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Point.h"
#include "ElementGraphique.h"


using namespace std;

class FabriquePoint {
public:
    // Crée un vecteur de shared_ptr<ElementGraphique> à partir d'une chaîne de points
    static vector<shared_ptr<ElementGraphique>> creerPointsDepuisChaine(const string& ligne);
    
    // Crée un seul Point
    static shared_ptr<Point> creerPoint(int x, int y);
};
