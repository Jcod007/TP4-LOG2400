#include "IdOrderSurfaceBuilder.h"
#include "Surface.h"
#include "PointCloud.h"
#include "PointBase.h"
#include "Point.h"
#include "GraphElement.h"

#include <vector>
#include <memory>
#include <algorithm>
/**
 * Construire la surface dans l'ordre des IDs :
 * - on récupère tous les PointBase du nuage
 * - on les trie par getId()
 * - on les ajoute à la Surface
 */
void IdOrderSurfaceBuilder::buildSurface(Surface& surface, const PointCloud& pointCloud)
{
    surface.clearPoints();

    const auto& elements = pointCloud.getPoints();

    std::vector<std::shared_ptr<PointBase>> points;
    points.reserve(elements.size());

    // On ne garde que les éléments qui sont des points
    for (const auto& element : elements) {
        auto point = std::dynamic_pointer_cast<PointBase>(element);
        if (point) {
            points.push_back(point);
        }
    }

    // Tri par ID croissant
    std::sort(points.begin(), points.end(),
              [](const std::shared_ptr<PointBase>& a,
                 const std::shared_ptr<PointBase>& b) {
                  return a->getId() < b->getId();
              });

    // Ajout dans la surface dans l'ordre trié
    for (const auto& p : points) {
        surface.addPoint(p);
    }
}
