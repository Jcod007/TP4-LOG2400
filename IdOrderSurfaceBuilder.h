#pragma once

#include "SurfaceBuilder.h"

// Stratégie : créer une surface en reliant les points selon l'ordre croissant des IDs.

class IdOrderSurfaceBuilder : public SurfaceBuilder {
public:
    void buildSurface(Surface& surface, const PointCloud& pointCloud) override;
};
