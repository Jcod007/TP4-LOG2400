#pragma once

class Surface;
class PointCloud;

// Interface du patron Strategy pour construire des surfaces à partir d'un PointCloud.
class SurfaceBuilder {
public:
    virtual ~SurfaceBuilder() = default;

    virtual void buildSurface(Surface& surface, const PointCloud& pointCloud) = 0;
};
