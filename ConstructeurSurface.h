#pragma once

class Surface;
class PointCloud;

// Interface du patron Strategy pour construire des surfaces à partir d'un PointCloud.
class ConstructeurSurface {
public:
    virtual ~ConstructeurSurface() = default;

    virtual void construireSurface(Surface& surface, const PointCloud& nuage) = 0;
};
