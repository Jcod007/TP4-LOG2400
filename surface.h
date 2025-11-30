#pragma once

#include "GraphElement.h"
#include <memory>
#include <vector>

class PointCloud;
class SurfaceBuilder;
class PointBase;

class Surface : public GraphElement {
public:
    Surface(std::shared_ptr<PointCloud> pointCloud);

    void setSurfaceBuilder(std::shared_ptr<SurfaceBuilder> builder);
    void build();

    const std::vector<std::shared_ptr<PointBase>>& getPoints() const;
    void clearPoints();
    void addPoint(const std::shared_ptr<PointBase>& point);

    std::string dessiner() const override {
        return "Surface"; // Placeholder
    }

private:
    std::shared_ptr<PointCloud> pointCloud_;
    std::shared_ptr<SurfaceBuilder> surfaceBuilderStrategie_;
    std::vector<std::shared_ptr<PointBase>> points_;
};
