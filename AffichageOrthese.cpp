#include "AffichageOrthese.h"
#include "GraphUtils.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip> // Pour std::setw si nécessaire

using namespace std;

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

    // 3. REMPLIR LA GRILLE (APPEL AU HOOK)
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

    // 4. AFFICHER LA GRILLE
    // On affiche de haut en bas (l'axe Y grandit vers le haut en géométrie)
    // Donc on commence la boucle à (hauteur - 1)
    for (int y = hauteur - 1; y >= 0; --y) {
        for (int x = 0; x < largeur; ++x) {
            cout << grille[y][x];
        }
        cout << endl;
    }
}