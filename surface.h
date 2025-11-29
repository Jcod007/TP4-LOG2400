#pragma once

#include <vector>
#include <memory>
#include "PointCloud.h"
#include "PointBase.h"
#include "Point.h"


class SurfaceBuilder;

class Surface {
public:
    explicit Surface(std::shared_ptr<PointCloud> pointCloud);

    // Définit la stratégie de construction de la surface
    void setSurfaceBuilder(std::shared_ptr<SurfaceBuilder> builder);

    void build();

    const std::vector<std::shared_ptr<PointBase>>& getPoints() const;

    void clearPoints();
    void addPoint(const std::shared_ptr<PointBase>& point);

private:
    std::shared_ptr<PointCloud> pointCloud_;
    std::shared_ptr<SurfaceBuilder> surfaceBuilderStrategie_;
    std::vector<std::shared_ptr<PointBase>> points_;
};
