#include "AffichageOrthese.h"
#include "GraphUtils.h"
#include "Surface.h" // Added include for Surface
#include "PointBase.h" // Added include for PointBase
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip> // Pour std::setw si nécessaire

using namespace std;

// Helper function to draw a line on the grid
void drawLine(vector<vector<string>>& grille, int x1, int y1, int x2, int y2, char lineChar) {
    bool steep = abs(y2 - y1) > abs(x2 - x1);
    if (steep) {
        swap(x1, y1);
        swap(x2, y2);
    }
    if (x1 > x2) {
        swap(x1, x2);
        swap(y1, y2);
    }

    int dx = x2 - x1;
    int dy = abs(y2 - y1);
    int error = dx / 2;
    int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;

    for (int x = x1; x <= x2; ++x) {
        if (steep) {
            if (y >= 0 && y < grille.size() && x >= 0 && x < grille[0].size()) {
                if (grille[y][x] == " ") grille[y][x] = lineChar;
            }
        }
        else {
            if (x >= 0 && x < grille.size() && y >= 0 && y < grille[0].size()) {
                if (grille[y][x] == " ") grille[y][x] = lineChar;
            }
        }
        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}

void AffichageOrthese::afficher(Plan& plan) const {
    // 1. CALCULER LES DIMENSIONS NÉCESSAIRES
    int maxX = 0;
    int maxY = 0;
    bool pointTrouve = false;

    for (const auto& element : plan.getGraphElements()) {
        pair<int, int> pos;
        if (getPositionIfPoint(element, pos)) {
            if (pos.first > maxX) maxX = pos.first;
            if (pos.second > maxY) maxY = pos.second;
            pointTrouve = true;
        }
        // Also consider points within surfaces for grid dimensions
        if (auto surface = dynamic_pointer_cast<Surface>(element)) {
            for (const auto& p : surface->getPoints()) {
                pair<int, int> p_pos;
                if (getPositionIfPoint(static_pointer_cast<GraphElement>(p), p_pos)) {
                    if (p_pos.first > maxX) maxX = p_pos.first;
                    if (p_pos.second > maxY) maxY = p_pos.second;
                    pointTrouve = true;
                }
            }
        }
    }

    // Si aucun point, on arrête ou on affiche une grille vide minimale
    if (!pointTrouve) {
        cout << "(Grille vide)" << endl;
        return;
    }

    // On ajoute une marge de +1 car les coordonnées commencent à 0
    // (ex: si le point est à x=5, il faut une largeur de 6 : indices 0 à 5)
    int largeur = maxX + 1;
    int hauteur = maxY + 1;

    // 2. INITIALISER LA GRILLE (Matrice de chaînes de caractères)
    // On remplit d'espaces " " par défaut
    vector<vector<string>> grille(hauteur, vector<string>(largeur, " "));

    // 3. REMPLIR LA GRILLE AVEC LES POINTS (APPEL AU HOOK)
    for (const auto& element : plan.getGraphElements()) {
        pair<int, int> pos;
        // Si c'est un élément affichable (un point ou décorateur de point)
        if (getPositionIfPoint(element, pos)) {
            int x = pos.first;
            int y = pos.second;
            
            // Sécurité : on s'assure qu'on ne dépasse pas (même si calculé au dessus)
            if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
                // APPEL POLYMORPHE : C'est ici que la magie opère !
                // La sous-classe décide du texte à afficher.
                grille[y][x] = getRepresentation(element);
            }
        }
    }

    // 4. DESSINER LES SURFACES
    for (const auto& element : plan.getGraphElements()) {
        if (auto surface = dynamic_pointer_cast<Surface>(element)) {
            const auto& surfacePoints = surface->getPoints();
            if (surfacePoints.size() > 1) {
                for (size_t i = 0; i < surfacePoints.size(); ++i) {
                    const auto& p1 = surfacePoints[i];
                    const auto& p2 = surfacePoints[(i + 1) % surfacePoints.size()]; // Connect last to first

                    pair<int, int> pos1, pos2;
                    if (getPositionIfPoint(static_pointer_cast<GraphElement>(p1), pos1) && getPositionIfPoint(static_pointer_cast<GraphElement>(p2), pos2)) {
                        char lineChar = ' ';
                        if (pos1.first == pos2.first) { // Vertical line
                            lineChar = '|';
                        } else if (pos1.second == pos2.second) { // Horizontal line
                            lineChar = '-';
                        } else if ((pos2.second - pos1.second) / (double)(pos2.first - pos1.first) > 0) { // Positive slope
                            lineChar = '/';
                        } else { // Negative slope
                            lineChar = '\\';
                        }
                        drawLine(grille, pos1.first, pos1.second, pos2.first, pos2.second, lineChar);
                    }
                }
            }
        }
    }

    // 5. AFFICHER LA GRILLE
    // On affiche de haut en bas (l'axe Y grandit vers le haut en géométrie)
    // Donc on commence la boucle à (hauteur - 1)
    for (int y = hauteur - 1; y >= 0; --y) {
        for (int x = 0; x < largeur; ++x) {
            cout << grille[y][x];
        }
        cout << endl;
    }
}