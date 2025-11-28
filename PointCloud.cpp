#include "PointCloud.h"
#include <algorithm>
#include <sstream>

PointCloud::PointCloud(string texture) : m_texture(texture) {
}

PointCloud::PointCloud(const std::vector<std::shared_ptr<GraphElement>>& points, string texture)
    : m_points(points), m_texture(texture) {
}

const std::vector<std::shared_ptr<GraphElement>>& PointCloud::getPoints() const {
    return m_points;
}

void PointCloud::addElement(std::shared_ptr<GraphElement> element) {
    m_points.push_back(element);
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

std::string PointCloud::dessiner() const {
    string pointsStr;
    for (size_t i = 0; i < m_points.size(); ++i) {
        pointsStr += to_string(m_points[i]->getId());
        if (i < m_points.size() - 1) {
            pointsStr += ", ";
        }
    }
    return "Nuage '" + m_texture + "' contient les points : " + pointsStr;
}
