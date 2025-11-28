#pragma once

#include <vector>
#include <memory>
#include "GraphElement.h"

class PointCloud : public GraphElement {
private:
    std::vector<std::shared_ptr<GraphElement>> m_points;

public:
    PointCloud();
    PointCloud(const std::vector<std::shared_ptr<GraphElement>>& points);

    const std::vector<std::shared_ptr<GraphElement>>& getPoints() const;
    void addElement(std::shared_ptr<GraphElement> element);
    void removePointById(int id);
    bool containsPoint(int id) const;

    int getId() const override;
    std::string dessiner() const override;
};
