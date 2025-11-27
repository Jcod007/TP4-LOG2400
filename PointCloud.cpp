#include "PointCloud.h"

PointCloud::PointCloud() {
}

PointCloud::PointCloud(const std::vector<std::shared_ptr<GraphElement>>& points)
    : points_(points) {
}

const std::vector<std::shared_ptr<GraphElement>>& PointCloud::getPoints() const {
    return points_;
}

void PointCloud::addElement(std::shared_ptr<GraphElement> element) {
    points_.push_back(element);
}

int PointCloud::getId() const {
    return id_;
}

void PointCloud::dessiner() const {
    for (const auto& e : points_) {
        e->dessiner();
    }
}
