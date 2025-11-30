#pragma once

class Surface;
class NuagePoints;

// Interface du patron Strategy pour construire des surfaces à partir d'un NuagePoints.
class ConstructeurSurface {
public:
    virtual ~ConstructeurSurface() = default;

    virtual void construireSurface(Surface& surface, const NuagePoints& nuage) = 0;
};
