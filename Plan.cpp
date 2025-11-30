#include "Plan.h"
#include "PointBase.h"
#include "PointCloud.h"
#include <algorithm>
#include <iostream>
#include <map>
#include "GraphUtils.h"
#include "Texture.h"
#include "Texture_O.h"
#include "Texture_F.h"

using namespace std;

void Plan::deplacerGraphElementById(int id, const pair<int,int>& position) {
    auto element = getGraphElementById(id);
    if (element) {
        setPositionIfPoint(element,position.first, position.second);
    }
}

vector<shared_ptr<GraphElement>> Plan::getGraphElements() const {
    return m_graphElements;
}

shared_ptr<PointCloud> Plan::getNuagesByTexture(const string& texture) const {
    for (const auto& element : m_graphElements) {
        // Vérifier si l'élément est un PointCloud
        if (auto nuage = dynamic_pointer_cast<PointCloud>(element)) {
            // Vérifier si la texture correspond
            if (nuage->getTexture() == texture) {
                return nuage;
            }
        }
    }
    
    return nullptr;
}

shared_ptr<PointCloud> Plan::getOrCreateNuageByTexture(string texture) {
    
    // Chercher si un nuage avec cette texture existe déjà
    auto nuageExistant = getNuagesByTexture(texture);
    
    if (nuageExistant != nullptr) {
        // Le nuage existe déjà, le retourner
        return nuageExistant;
    }
    
    // Le nuage n'existe pas, le créer avec string
    auto nouveauNuage = make_shared<PointCloud>(texture);
    
    // L'ajouter au plan
    m_graphElements.push_back(nouveauNuage);
    
    return nouveauNuage;
}

void Plan::setGraphElements(vector<shared_ptr<GraphElement>> graphElements) {
    m_graphElements = graphElements;
}

shared_ptr<GraphElement> Plan::getGraphElementById(int id) {
    for (auto& element : m_graphElements) {
        if (element->getId() == id) {
            return element;
        }
    }
    return nullptr;
}

void Plan::supprimerGraphElementById(int id) {
    // Étape 1 : Retirer le point de tous les PointClouds qui le contiennent
    for (auto& element : m_graphElements) {
        // Vérifier si c'est un PointCloud
        if (auto cloud = dynamic_pointer_cast<PointCloud>(element)) {
            if (cloud->containsPoint(id)) {
                cloud->removePointById(id);
            }
        }
    }
    
    // Étape 2 : Retirer l'élément du Plan
    auto it = find_if(m_graphElements.begin(), m_graphElements.end(), 
        [id](const shared_ptr<GraphElement>& element) {
            return element->getId() == id;
        });
   
    if (it != m_graphElements.end()) {
        m_graphElements.erase(it);
    }
}

shared_ptr<PointCloud> Plan::fusionEnNuage(vector<int> ids, vector<string> textures)
{
    if (ids.empty() || textures.empty()) {
        return nullptr;
    }
    
    // Parcourir les textures pour trouver la première qui n'existe pas
    string textureACreer = "";
    
    for (string texture : textures) {
        auto nuageExistant = getNuagesByTexture(texture);
        
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
   auto nouveauNuage = getOrCreateNuageByTexture(textureACreer);
    
    // Étape 1 : Collecter tous les IDs de points à décorer et ajouter les éléments de plus haut niveau au nouveau nuage
    std::vector<int> allPointIdsToDecorate;
    
    // Parcourir les IDs donnés pour trouver les éléments dans le Plan
    for (int id : ids) {
        auto it = std::find_if(m_graphElements.begin(), m_graphElements.end(), 
            [id](const std::shared_ptr<GraphElement>& elem){ return elem->getId() == id; });

        if (it != m_graphElements.end()) {
            auto& elementDuPlan = *it; // Référence à l'élément dans la liste principale

            if (auto point = std::dynamic_pointer_cast<PointBase>(elementDuPlan)) {
                // Si c'est un point, on l'ajoute à la liste à décorer (sera décoré à l'étape 2)
                allPointIdsToDecorate.push_back(id);
            } 
            else if (auto childCloud = std::dynamic_pointer_cast<PointCloud>(elementDuPlan)) {
                // Si c'est un nuage, on récupère récursivement les IDs de ses points internes
                std::vector<int> childrenPointsIds = childCloud->getAllPointIdsRecursively();
                allPointIdsToDecorate.insert(allPointIdsToDecorate.end(), childrenPointsIds.begin(), childrenPointsIds.end());
                // Note : Pas besoin de filtrer les doublons d'IDs de points ici, la décoration sera idempotente.
            }
            
            // On ajoute l'élément (point ou nuage) au nouveau nuage parent (Composite)
            nouveauNuage->addChild(elementDuPlan);
        }
    }

    // Étape 2 : Décorer tous les points collectés et mettre à jour les pointeurs dans le Plan
    for (int pointId : allPointIdsToDecorate) {
        // Trouver le point dans le Plan par référence (pour pouvoir modifier le shared_ptr)
        auto pointIt = std::find_if(m_graphElements.begin(), m_graphElements.end(), 
            [pointId](const std::shared_ptr<GraphElement>& elem){ return elem->getId() == pointId; });

        if (pointIt != m_graphElements.end()) {
            auto& pointDuPlan = *pointIt; // Référence au shared_ptr dans m_graphElements
            
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