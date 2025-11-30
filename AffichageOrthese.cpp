#include "AffichageOrthese.h"
#include "UtilitairesGraphique.h"
#include "Surface.h" // Added include for Surface
#include "PointBase.h" // Added include for PointBase
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip> // Pour std::setw si nécessaire

using namespace std;

// Fonction utilitaire pour tracer une ligne sur la grille en utilisant l'algorithme de Bresenham modifié
// qui sélectionne le caractère approprié pour chaque segment de la ligne.
void tracerLigne(vector<vector<string>>& grille, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;  // valeur erreur e_xy
    int x = x1;
    int y = y1;

    while (true) {
        int pos_prec_x = x;
        int pos_prec_y = y;

        if (x == x2 && y == y2) break;

        int e2 = 2 * err;
        bool deplace_x = false;
        bool deplace_y = false;

        if (e2 >= dy) { // e_xy+e_x > 0
            err += dy;
            x += sx;
            deplace_x = true;
        }
        if (e2 <= dx) { // e_xy+e_y < 0
            err += dx;
            y += sy;
            deplace_y = true;
        }

        // Déterminer le caractère basé sur le mouvement
        char caracterLigne = ' ';
        if (deplace_x && deplace_y) {
            // Mouvement diagonal
            if ((sx > 0 && sy > 0) || (sx < 0 && sy < 0)) {
                caracterLigne = '/'; // Pente positive
            } else {
                caracterLigne = '\\'; // Pente négative
            }
        } else if (deplace_x) {
            caracterLigne = '-'; // Mouvement horizontal
        } else if (deplace_y) {
            caracterLigne = '|'; // Mouvement vertical
        }
        
        // Dessiner le caractère pour le segment commençant à pos_prec_x, pos_prec_y
        if (pos_prec_x >= 0 && pos_prec_x < grille[0].size() && pos_prec_y >= 0 && pos_prec_y < grille.size()) {
             if (grille[pos_prec_y][pos_prec_x] == " ") {
                grille[pos_prec_y][pos_prec_x] = caracterLigne;
            }
        }
    }
}

void AffichageOrthese::afficher(Plan& plan) const {
    // 1. CALCULER LES DIMENSIONS NÉCESSAIRES
    int maxX = 0;
    int maxY = 0;
    bool pointTrouve = false;

    for (const auto& element : plan.obtenirElements()) {
        pair<int, int> pos;
        if (obtenirPositionSiPoint(element, pos)) {
            if (pos.first > maxX) maxX = pos.first;
            if (pos.second > maxY) maxY = pos.second;
            pointTrouve = true;
        }
        // Also consider points within surfaces for grid dimensions
        if (auto surface = dynamic_pointer_cast<Surface>(element)) {
            for (const auto& p : surface->obtenirPoints()) {
                pair<int, int> p_pos;
                if (obtenirPositionSiPoint(static_pointer_cast<ElementGraphique>(p), p_pos)) {
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
    for (const auto& element : plan.obtenirElements()) {
        pair<int, int> pos;
        // Si c'est un élément affichable (un point ou décorateur de point)
        if (obtenirPositionSiPoint(element, pos)) {
            int x = pos.first;
            int y = pos.second;
            
            // Sécurité : on s'assure qu'on ne dépasse pas (même si calculé au dessus)
            if (x >= 0 && x < largeur && y >= 0 && y < hauteur) {
                // APPEL POLYMORPHE : C'est ici que la magie opère !
                // La sous-classe décide du texte à afficher.
                grille[y][x] = obtenirRepresentation(element);
            }
        }
    }

    // 4. DESSINER LES SURFACES
    for (const auto& element : plan.obtenirElements()) {
        if (auto surface = dynamic_pointer_cast<Surface>(element)) {
            const auto& surfacePoints = surface->obtenirPoints();
            if (surfacePoints.size() > 1) {
                for (size_t i = 0; i < surfacePoints.size(); ++i) {
                    const auto& p1 = surfacePoints[i];
                    const auto& p2 = surfacePoints[(i + 1) % surfacePoints.size()]; // Connect last to first

                    pair<int, int> pos1, pos2;
                    if (obtenirPositionSiPoint(static_pointer_cast<ElementGraphique>(p1), pos1) && obtenirPositionSiPoint(static_pointer_cast<ElementGraphique>(p2), pos2)) {
                        tracerLigne(grille, pos1.first, pos1.second, pos2.first, pos2.second);
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