#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Point.h"
#include "GraphElement.h"
#include "tpAffichage.h"

using namespace std;

class PointFactory {
public:
    // Crée un vecteur de shared_ptr<GraphElement> à partir d'une chaîne de points
    static vector<shared_ptr<GraphElement>> creerPointsDepuisChaine(const string& ligne);
    
    // Crée un seul Point
    static shared_ptr<Point> creerPoint(int x, int y);
};
