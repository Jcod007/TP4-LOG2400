#pragma once

#include "GraphElement.h"
#include <memory>
#include <vector>

class PointCloud;
class ConstructeurSurface;
class PointBase;

class Surface : public GraphElement {
public:
    Surface(std::shared_ptr<PointCloud> pointCloud);

    void setConstructeurSurface(std::shared_ptr<ConstructeurSurface> builder);
    void construire();

    const std::vector<std::shared_ptr<PointBase>>& getPoints() const;
    void clearPoints();
    void addPoint(const std::shared_ptr<PointBase>& point);

    std::string dessiner() const override {
        return "Surface"; // Placeholder
    }

private:
    std::shared_ptr<PointCloud> pointCloud_;
    std::shared_ptr<ConstructeurSurface> constructeurStrategie_;
    std::vector<std::shared_ptr<PointBase>> points_;
};
