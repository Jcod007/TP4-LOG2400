#include "NearestNeighborSurfaceBuilder.h"
#include "Surface.h"
#include "PointCloud.h"
#include "PointBase.h"

#include <vector>
#include <memory>
#include <limits>
#include <cmath>

/**
 * Construire la surface en suivant l'algorithme du plus proche voisin :
 * - on part d'un point de départ (ici le premier de la liste)
 * - à chaque étape, on ajoute le point non encore utilisé le plus proche
 *   du point courant.
 */
void NearestNeighborSurfaceBuilder::buildSurface(Surface& surface,
                                                 const PointCloud& pointCloud)
{
    surface.clearPoints();

    const auto& elements = pointCloud.getPoints();

    std::vector<std::shared_ptr<PointBase>> points;
    points.reserve(elements.size());

    // On ne garde que les PointBase
    for (const auto& element : elements) {
        auto point = std::dynamic_pointer_cast<PointBase>(element);
        if (point) {
            points.push_back(point);
        }
    }

    if (points.empty()) {
        return;
    }

    const std::size_t n = points.size();
    std::vector<bool> used(n, false);

    // Point de départ : le premier
    std::size_t currentIndex = 0;
    used[currentIndex] = true;
    surface.addPoint(points[currentIndex]);

    for (std::size_t step = 1; step < n; ++step) {
        std::size_t nextIndex = n;
        double bestDist2 = std::numeric_limits<double>::max();

        auto [cx, cy] = points[currentIndex]->getXY();

        for (std::size_t i = 0; i < n; ++i) {
            if (used[i]) continue;

            auto [x, y] = points[i]->getXY();
            const int dx = cx - x;
            const int dy = cy - y;
            const double dist2 = static_cast<double>(dx * dx + dy * dy);

            if (dist2 < bestDist2) {
                bestDist2 = dist2;
                nextIndex = i;
            }
        }

        if (nextIndex == n) {
            // plus aucun point disponible (sécurité)
            break;
        }

        used[nextIndex] = true;
        surface.addPoint(points[nextIndex]);
        currentIndex = nextIndex;
    }
}
