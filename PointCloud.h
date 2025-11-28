#pragma once

#include <vector>
#include <memory>
#include "GraphElement.h"

class PointCloud : public GraphElement {
private:
    std::vector<std::shared_ptr<GraphElement>> points_;

public:
    PointCloud();
    PointCloud(const std::vector<std::shared_ptr<GraphElement>>& points);

    const std::vector<std::shared_ptr<GraphElement>>& getPoints() const;
    void addElement(std::shared_ptr<GraphElement> element);

    int getId() const override;
    std::string dessiner() const override;
};
