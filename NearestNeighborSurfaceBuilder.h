#pragma once

#include "SurfaceBuilder.h"

// Stratégie : créer une surface en reliant les points selon l'algorithme du plus proche voisin.
class NearestNeighborSurfaceBuilder : public SurfaceBuilder {
public:
    void buildSurface(Surface& surface, const PointCloud& pointCloud) override;
};
