#pragma once

#include <vector>
#include <memory>
#include <string>
#include "GraphElement.h"

class PointCloud : public GraphElement {
private:
    std::vector<std::shared_ptr<GraphElement>> m_points;
    std::string m_texture;

public:
    PointCloud(string texture);
    PointCloud(const std::vector<std::shared_ptr<GraphElement>>& points, string texture);

    const std::vector<std::shared_ptr<GraphElement>>& getPoints() const;
    void addElement(std::shared_ptr<GraphElement> element);
    void removePointById(int id);
    bool containsPoint(int id) const;
    std::string getTexture() const;

    int getId() const override;
    std::string dessiner() const override;
};
