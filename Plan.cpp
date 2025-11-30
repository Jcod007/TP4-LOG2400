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
    auto nuage = getOrCreateNuageByTexture(textureACreer);

    // Ajouter tous les éléments (points ou autres nuages) au nouveau nuage.
    // La méthode addChild s'occupera de la décoration et de la fusion.
    for (int id : ids) {
        auto element = getGraphElementById(id);
        if (element) {
            nuage->addChild(element);
        }
    }

    return nuage;
}