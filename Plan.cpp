#include "Plan.h"
#include "PointBase.h"
#include "NuagePoints.h"
#include <algorithm>
#include <iostream>
#include <map>
#include "UtilitairesGraphique.h"
#include "Texture.h"
#include "Texture_O.h"
#include "Texture_F.h"
#include "Surface.h"

using namespace std;

void Plan::deplacerElementGraphiqueParId(int id, const pair<int,int>& position) {
    auto element = obtenirElementGraphiqueParId(id);
    if (element) {
        definirPositionSiPoint(element,position.first, position.second);
    }
}

vector<shared_ptr<ElementGraphique>> Plan::obtenirElements() const {
    return m_elementsGraphiques;
}

shared_ptr<NuagePoints> Plan::obtenirNuagesParTexture(const string& texture) const {
    for (const auto& element : m_elementsGraphiques) {
        // Vérifier si l'élément est un NuagePoints
        if (auto nuage = dynamic_pointer_cast<NuagePoints>(element)) {
            // Vérifier si la texture correspond
            if (nuage->obtenirTexture() == texture) {
                return nuage;
            }
        }
    }
    
    return nullptr;
}

shared_ptr<NuagePoints> Plan::obtenirOuCreerNuageParTexture(string texture) {
    
    // Chercher si un nuage avec cette texture existe déjà
    auto nuageExistant = obtenirNuagesParTexture(texture);
    
    if (nuageExistant != nullptr) {
        // Le nuage existe déjà, le retourner
        return nuageExistant;
    }
    
    // Le nuage n'existe pas, le créer avec string
    auto nouveauNuage = make_shared<NuagePoints>(texture);
    
    // L'ajouter au plan
    m_elementsGraphiques.push_back(nouveauNuage);
    
    return nouveauNuage;
}

void Plan::definirElementsGraphiques(vector<shared_ptr<ElementGraphique>> graphElements) {
    m_elementsGraphiques = graphElements;
}

shared_ptr<ElementGraphique> Plan::obtenirElementGraphiqueParId(int id) {
    for (auto& element : m_elementsGraphiques) {
        if (element->obtenirId() == id) {
            return element;
        }
    }
    return nullptr;
}

void Plan::supprimerElementGraphiqueParId(int id) {
    // Étape 1 : Retirer le point de tous les NuagePoints qui le contiennent
    for (auto& element : m_elementsGraphiques) {
        // Vérifier si c'est un NuagePoints
        if (auto cloud = dynamic_pointer_cast<NuagePoints>(element)) {
            if (cloud->contientPoint(id)) {
                cloud->supprimerPointParId(id);
            }
        }
    }
    
    // Étape 2 : Retirer l'élément du Plan
    auto it = find_if(m_elementsGraphiques.begin(), m_elementsGraphiques.end(), 
        [id](const shared_ptr<ElementGraphique>& element) {
            return element->obtenirId() == id;
        });
   
    if (it != m_elementsGraphiques.end()) {
        m_elementsGraphiques.erase(it);
    }
}

shared_ptr<NuagePoints> Plan::fusionnerEnNuage(vector<int> ids, vector<string> textures)
{
    if (ids.empty() || textures.empty()) {
        return nullptr;
    }
    
    // Parcourir les textures pour trouver la première qui n'existe pas
    string textureACreer = "";
    
    for (string texture : textures) {
        auto nuageExistant = obtenirNuagesParTexture(texture);
        
        if (nuageExistant == nullptr) {
            // Cette texture n'existe pas encore, on s'arrête ici
            textureACreer = texture;
            break;
        }
        // Sinon, on continue à la texture suivante
    }
    
    // Si toutes les textures existent déjà, on ne crée rien
    if (textureACreer == "") {
        return nullptr;
    }
    
    // Créer le nuage pour cette texture
   auto nouveauNuage = obtenirOuCreerNuageParTexture(textureACreer);
    
    // Étape 1 : Collecter tous les IDs de points à décorer et ajouter les éléments de plus haut niveau au nouveau nuage
    std::vector<int> allPointIdsToDecorate;
    
    // Parcourir les IDs donnés pour trouver les éléments dans le Plan
    for (int id : ids) {
        auto it = std::find_if(m_elementsGraphiques.begin(), m_elementsGraphiques.end(), 
            [id](const std::shared_ptr<ElementGraphique>& elem){ return elem->obtenirId() == id; });

        if (it != m_elementsGraphiques.end()) {
            auto& elementDuPlan = *it; // Référence à l'élément dans la liste principale

            if (auto point = std::dynamic_pointer_cast<PointBase>(elementDuPlan)) {
                // Si c'est un point, on l'ajoute à la liste à décorer (sera décoré à l'étape 2)
                allPointIdsToDecorate.push_back(id);
            } 
            else if (auto childCloud = std::dynamic_pointer_cast<NuagePoints>(elementDuPlan)) {
                // Si c'est un nuage, on récupère récursivement les IDs de ses points internes
                std::vector<int> childrenPointsIds = childCloud->obtenirTousIdsPointsRecursivement();
                allPointIdsToDecorate.insert(allPointIdsToDecorate.end(), childrenPointsIds.begin(), childrenPointsIds.end());
                // Note : Pas besoin de filtrer les doublons d'IDs de points ici, la décoration sera idempotente.
            }
            
            // On ajoute l'élément (point ou nuage) au nouveau nuage parent (Composite)
            nouveauNuage->ajouterEnfant(elementDuPlan);
        }
    }

    // Étape 2 : Décorer tous les points collectés et mettre à jour les pointeurs dans le Plan
    for (int pointId : allPointIdsToDecorate) {
        // Trouver le point dans le Plan par référence (pour pouvoir modifier le shared_ptr)
        auto pointIt = std::find_if(m_elementsGraphiques.begin(), m_elementsGraphiques.end(), 
            [pointId](const std::shared_ptr<ElementGraphique>& elem){ return elem->obtenirId() == pointId; });

        if (pointIt != m_elementsGraphiques.end()) {
            auto& pointDuPlan = *pointIt; // Référence au shared_ptr dans m_elementsGraphiques
            
            if (auto currentPoint = std::dynamic_pointer_cast<PointBase>(pointDuPlan)) {
                
                // Création du nouveau décorateur
                std::shared_ptr<PointBase> pointDecore;
                if (textureACreer == "o") pointDecore = std::make_shared<Texture_O>(currentPoint);
                else if (textureACreer == "#") pointDecore = std::make_shared<Texture_F>(currentPoint);
                else pointDecore = currentPoint;
                
                // CRUCIAL : Mettre à jour le pointeur dans le Plan pour que l'affichage soit correct
                pointDuPlan = pointDecore;
            }
        }
    }

    return nouveauNuage;
}





void Plan::ajouterElementGraphique(shared_ptr<ElementGraphique> element) {
    if (element) {
        m_elementsGraphiques.push_back(element);
    }
}
void Plan::creerSurface(int cloudId, shared_ptr<ConstructeurSurface> builder) {

    shared_ptr<NuagePoints> targetCloud = nullptr;

    for (const auto& element : m_elementsGraphiques) {

        if (auto cloud = dynamic_pointer_cast<NuagePoints>(element)) {

            if (cloud->obtenirId() == cloudId) {

                targetCloud = cloud;

                break;

            }

        }

    }



    if (targetCloud) {

        auto surface = make_shared<Surface>(targetCloud);

        surface->definirConstructeurSurface(builder);

        surface->construire();

        m_elementsGraphiques.push_back(surface);

    }

}