#include "IdOrderSurfaceBuilder.h"
#include "Surface.h"
#include "PointCloud.h"
#include "PointBase.h"
#include "Point.h"
#include "GraphElement.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * Construire la surface dans l'ordre des IDs :
 * - on récupère tous les PointBase du nuage
 * - on les trie par getId()
 * - on les ajoute à la Surface
 */
void IdOrderSurfaceBuilder::buildSurface(Surface& surface, const PointCloud& pointCloud)
{
    cout << "IdOrderSurfaceBuilder::buildSurface called" << std::endl;
}
