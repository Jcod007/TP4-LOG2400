#pragma once

#include <vector>
#include <memory>
#include <string>
#include "Point.h"
#include "ElementGraphique.h"


class FabriquePoint {
public:
    // Crée un vecteur de shared_ptr<ElementGraphique> à partir d'une chaîne de points
    static std::vector<std::shared_ptr<ElementGraphique>> creerPointsDepuisChaine(const std::string& ligne);
    
    // Crée un seul Point
    static std::shared_ptr<Point> creerPoint(int x, int y);
};
