#include "AffichageListe.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Plan.h"
#include "Point.h"
#include "PointFactory.h"
#include <memory>
#include "Invocateur.h"
#include "Commande_A.h"
#include "SupprimerCommand.h"

using namespace std;

int main(int argc, char* argv[]) {
    string args;
    // On accepte des points en entrée.
    if (argc > 1) {
        ostringstream oss;
        for (int i = 1; i < argc; ++i) oss << argv[i] << " ";
        args = oss.str();
    } else {
        cout << "Entrez les points au format (x,y) :\n> ";
        getline(cin, args);
    }
    
    // Voici des fonctions utiles pour réaliser le TP. 
    // TODO: Il faudrait les placer dans des classes appropriées.
    Plan plan;
    Invocateur invocateur;
    
    
    plan.setGraphElements(PointFactory::creerPointsDepuisChaine(args));
    
    
  
    
    // Ce sont différentes textures possibles. Seules les 2 premières sont utilisées dans les scénarios du TP.
    vector<char> texturesNuages = {'o', '#', '$'};
    string cmd;
    
    // Menu
    while (true) {
        cout << "\nCommandes:\n"
                  << "a  - Afficher les points et les nuages\n"
                  << "o1 - Afficher l'orthèse avec les textures des points\n"
                  << "o2 - Afficher l'orthèse avec les IDs des points\n"
                  << "f  - Fusionner des points dans un nuage (et appliquer texture)\n"
                  << "d  - Deplacer un point (ID)\n"
                  << "s  - Supprimer un point (ID)\n"
                  << "c1 - Creer les surfaces selon l'ordre des IDs\n"
                  << "c2 - Creer les surfaces selon la distance minimale\n"
                  << "q  - Quitter\n> ";
        getline(std::cin, cmd);

        if (cmd == "q") break;
        if (cmd == "a") {
            shared_ptr<Commande> commande = make_shared<Commande_A>(make_unique<AffichageListe>(),plan);
            invocateur.setCommande(commande);
            invocateur.executerCommande();
        }
        else if (cmd == "s")
        {
            cout << "Entrez l'ID du point a supprimer : ";
            string idStr;
            getline(cin, idStr);
            int id = stoi(idStr);
            shared_ptr<Commande> commande = make_shared<SupprimerCommand>(plan, id);
            invocateur.setCommande(commande);
            invocateur.executerCommande();
        }
        
    }

    return 0;
}