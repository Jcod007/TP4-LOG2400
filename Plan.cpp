#include "Plan.h"
#include "PointBase.h"
#include "PointCloud.h"
#include <algorithm>
#include <iostream>
#include "GraphUtils.h"

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