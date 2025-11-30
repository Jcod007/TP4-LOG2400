#pragma once

#include "ConstructeurSurface.h"

// Stratégie : créer une surface en reliant les points selon l'algorithme du plus proche voisin.
class ConstructeurSurfaceParProchVoisin : public ConstructeurSurface {
public:
    void construireSurface(Surface& surface, const PointCloud& nuage) override;
};
