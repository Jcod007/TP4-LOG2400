#include "AffichageListe.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Plan.h"
#include "Point.h"
#include "PointFactory.h"
#include <memory>
#include "Invocateur.h"
#include "Commande_A.h"
#include "SupprimerCommand.h"
#include "DeplacerCommand.h"
#include "FusionEnNuageCommand.h"
#include "AffichageAvecTexture.h"
#include "AffichageAvecID.h"

using namespace std;

pair<int,int> parsingPosition(string& posStr)
{
            posStr.erase(remove(posStr.begin(), posStr.end(), '('), posStr.end());
            posStr.erase(remove(posStr.begin(), posStr.end(), ')'), posStr.end());
            
            
            int x, y;
            size_t commaPos = posStr.find(',');
            if (commaPos != string::npos) {
                x = stoi(posStr.substr(0, commaPos));
                y = stoi(posStr.substr(commaPos + 1));
            } else {
                istringstream iss(posStr);
                iss >> x >> y;
            }   
            pair<int,int> newPos = {x, y};
            return newPos;
}

void affichageMenu()
{
    cout << "Commandes :\n"
         << "a - Afficher les points et les nuages\n"
         << "o1 - Afficher l'orthèse avec les textures des points\n"
         << "o2 - Afficher l'orthèse avec les IDs des points\n"
         << "f - Fusionner des points dans un nuage (et appliquer texture)\n"
         << "d - Deplacer un point (ID)\n"
         << "s - Supprimer un point (ID)\n" // Rétablissement de la description pour 's'
         << "c1 - Creer les surfaces selon l'ordre des IDs\n"
         << "c2 - Creer les surfaces selon la distance minimale\n"
         << "q - Quitter\n"
         << "> ";
}

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
    vector<string> texturesNuages = {"o", "#", "$"};
    string cmd;    

    // Menu
    while (true) {
        affichageMenu();
        getline(std::cin, cmd);

        if (cmd == "q") break;
        if (cmd == "a") {
            shared_ptr<Commande> commande = make_shared<Commande_A>(make_unique<AffichageListe>(),plan);
            invocateur.setCommande(commande);
            invocateur.executerCommande();
        }

        else if (cmd == "o1") {
            shared_ptr<Commande> commande = make_shared<Commande_A>(make_unique<AffichageAvecTexture>(),plan);
            invocateur.setCommande(commande);
            invocateur.executerCommande();
        }
        else if (cmd == "o2") {
            shared_ptr<Commande> commande = make_shared<Commande_A>(make_unique<AffichageAvecID>(),plan);
            invocateur.setCommande(commande);
            invocateur.executerCommande();
        }

        else if (cmd == "f")
        {
            cout << "Entrez les IDs des points a fusionner (separes par des espaces) : ";
            string idsStr;
            getline(cin, idsStr);
            
            // Utiliser istringstream pour lire plusieurs entiers
            istringstream iss(idsStr);
            int id;
            vector<int> ids;
            while (iss >> id) {
                ids.push_back(id);
            }
            
            // Utiliser la commande FusionEnNuageCommand
            shared_ptr<Commande> commande = make_shared<FusionEnNuageCommand>(plan, ids, texturesNuages);
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
        
        else if (cmd == "d")
        {
            cout << "Entrez l'ID du point a deplacer : ";
            string idStr;
            getline(cin, idStr);
            int id = stoi(idStr);
            
            cout << "Entrez la nouvelle position (x y) ou (x,y) : ";
            int x, y;
            cin>>x>>y;
            cin.ignore(10000, '\n');
            
            pair<int,int> newPos = {x,y};
            
            shared_ptr<Commande> commande = make_shared<DeplacerCommand>(plan, id, newPos);
            invocateur.setCommande(commande);
            invocateur.executerCommande();
        }
        
    }

    return 0;
}