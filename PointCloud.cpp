#include "PointCloud.h"
#include <algorithm>

PointCloud::PointCloud() {
}

PointCloud::PointCloud(const std::vector<std::shared_ptr<GraphElement>>& points)
    : m_points(points) {
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

int PointCloud::getId() const {
    return m_id;
}

std::string PointCloud::dessiner() const {
    return "PointCloud (ID: " + std::to_string(getId()) + ") with " + std::to_string(m_points.size()) + " points";
}
