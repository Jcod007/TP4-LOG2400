#pragma once

#include "ConstructeurSurface.h"

// Stratégie : créer une surface en reliant les points selon l'ordre croissant des IDs.

class ConstructeurSurfaceParOrdreId : public ConstructeurSurface {
public:
    void construireSurface(Surface& surface, const PointCloud& nuage) override;
};
