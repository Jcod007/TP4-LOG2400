#include "PointCloud.h"
#include <algorithm>
#include <sstream>
#include "PointBase.h"
#include "Texture_O.h"
#include "Texture_F.h"

PointCloud::PointCloud(string texture) : m_texture(texture) {
}

PointCloud::PointCloud(const std::vector<std::shared_ptr<GraphElement>>& points, string texture)
    : m_points(points), m_texture(texture) {
}

const std::vector<std::shared_ptr<GraphElement>>& PointCloud::getPoints() const {
    return m_points;
}

void PointCloud::removePointById(int id) {
    auto it = std::find_if(m_points.begin(), m_points.end(),
        [id](const std::shared_ptr<GraphElement>& element) {
            return element->getId() == id;
        });
    
    if (it != m_points.end()) {
        m_points.erase(it);
    }
}

bool PointCloud::containsPoint(int id) const {
    return std::find_if(m_points.begin(), m_points.end(),
        [id](const std::shared_ptr<GraphElement>& element) {
            return element->getId() == id;
        }) != m_points.end();
}


std::string PointCloud::getTexture() const {
    return m_texture;
}

int PointCloud::getId() const {
    return m_id;
}

void PointCloud::addChild(shared_ptr<GraphElement> child) {
    // Essayer de caster en Point
    if (auto point = dynamic_pointer_cast<PointBase>(child)) {
        if (containsPoint(point->getId())) {
            return; // Déjà présent, on ne fait rien
        }

        shared_ptr<PointBase> pointDecore = point; // Par défaut, pas de décoration
        if (getTexture() == "o") {
            pointDecore = make_shared<Texture_O>(point);
        } else if (getTexture() == "#") {
            pointDecore = make_shared<Texture_F>(point);
        }
        
        child = pointDecore; // Mettre à jour child pour l'ajouter décoré
        m_points.push_back(pointDecore);
    }
    // Si ce n'est pas un point, essayer de caster en PointCloud
    else if (auto cloud = dynamic_pointer_cast<PointCloud>(child)) {
        // C'est un nuage, on ajoute ses enfants récursivement
        for (const auto& grandChild : cloud->getPoints()) {
            this->addChild(grandChild); // Appel récursif !
        }
    }
    // Sinon, c'est un autre type de GraphElement
    else {
        if (!containsPoint(child->getId())) {
            m_points.push_back(child); // On l'ajoute tel quel
        }
    }
}

void PointCloud::addChildren(const vector<shared_ptr<GraphElement>>& children) {
        for (const auto& child : children) {
            addChild(child);
        }
    }
std::string PointCloud::dessiner() const {
    string pointsStr;
    for (size_t i = 0; i < m_points.size(); ++i) {
        pointsStr += to_string(m_points[i]->getId());
        if (i < m_points.size() - 1) {
            pointsStr += ", ";
        }
    }
    return to_string(getId())+": Nuage '" + m_texture + "' contient les points : " + pointsStr;
}
