#pragma once
#include <string>
#include <vector>

const int LARGEUR = 30;
const int HAUTEUR = 20;

struct Point2D {
    int x, y;
};

std::vector<Point2D> creerPoints(const std::string& ligne);
void tracerLigne(std::vector<std::vector<char>>& grille, int x0, int y0, int x1, int y1);
void imprimerGrille(const std::vector<Point2D>& points);
