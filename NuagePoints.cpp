#include "NuagePoints.h"
#include <algorithm>
#include <sstream>
#include "PointBase.h"
#include "Texture_O.h"
#include "Texture_F.h"

NuagePoints::NuagePoints(string texture) : m_texture(texture) {
}

std::vector<int> NuagePoints::obtenirTousIdsPointsRecursivement() const {
    std::vector<int> ids;
    for (const auto& child : m_points) {
        // Cas feuille (PointBase)
        if (auto point = std::dynamic_pointer_cast<PointBase>(child)) {
            ids.push_back(point->obtenirId());
        } 
        // Cas noeud composite (NuagePoints) -> Appel récursif
        else if (auto cloud = std::dynamic_pointer_cast<NuagePoints>(child)) {
            std::vector<int> childIds = cloud->obtenirTousIdsPointsRecursivement();
            ids.insert(ids.end(), childIds.begin(), childIds.end());
        }
    }
    return ids;
}
NuagePoints::NuagePoints(const std::vector<std::shared_ptr<ElementGraphique>>& points, string texture)
    : m_points(points), m_texture(texture) {
}

const std::vector<std::shared_ptr<ElementGraphique>>& NuagePoints::obtenirPoints() const {
    return m_points;
}

void NuagePoints::supprimerPointParId(int id) {
    auto it = std::find_if(m_points.begin(), m_points.end(),
        [id](const std::shared_ptr<ElementGraphique>& element) {
            return element->obtenirId() == id;
        });
    
    if (it != m_points.end()) {
        m_points.erase(it);
    }
}

bool NuagePoints::contientPoint(int id) const {
    return std::find_if(m_points.begin(), m_points.end(),
        [id](const std::shared_ptr<ElementGraphique>& element) {
            return element->obtenirId() == id;
        }) != m_points.end();
}


std::string NuagePoints::obtenirTexture() const {
    return m_texture;
}

int NuagePoints::obtenirId() const {
    return m_id;
}

void NuagePoints::ajouterEnfant(shared_ptr<ElementGraphique> child) {
    // Essayer de caster en Point
    if (auto point = dynamic_pointer_cast<PointBase>(child)) {
        if (contientPoint(point->obtenirId())) {
            return; // Déjà présent, on ne fait rien
        }

        shared_ptr<PointBase> pointDecore = point; // Par défaut, pas de décoration
        if (obtenirTexture() == "o") {
            pointDecore = make_shared<Texture_O>(point);
        } else if (obtenirTexture() == "#") {
            pointDecore = make_shared<Texture_F>(point);
        }
        
        child = pointDecore; // Mettre à jour child pour l'ajouter décoré
        m_points.push_back(pointDecore);
    }
    // Si ce n'est pas un point, essayer de caster en NuagePoints
    else if (auto cloud = dynamic_pointer_cast<NuagePoints>(child)) {
        // C'est un nuage, on ajoute ses enfants récursivement
        for (const auto& grandChild : cloud->obtenirPoints()) {
            this->ajouterEnfant(grandChild); // Appel récursif !
        }
    }
    // Sinon, c'est un autre type de ElementGraphique
    else {
        if (!contientPoint(child->obtenirId())) {
            m_points.push_back(child); // On l'ajoute tel quel
        }
    }
}

void NuagePoints::ajouterEnfants(const vector<shared_ptr<ElementGraphique>>& children) {
        for (const auto& child : children) {
            ajouterEnfant(child);
        }
    }
std::string NuagePoints::dessiner() const {
    string pointsStr;
    for (size_t i = 0; i < m_points.size(); ++i) {
        pointsStr += to_string(m_points[i]->obtenirId());
        if (i < m_points.size() - 1) {
            pointsStr += ", ";
        }
    }
    return to_string(obtenirId())+": Nuage '" + m_texture + "' contient les points : " + pointsStr;
}
