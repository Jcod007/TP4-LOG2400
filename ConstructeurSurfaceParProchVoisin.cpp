#include "ConstructeurSurfaceParProchVoisin.h"
#include "Surface.h"
#include "PointCloud.h"
#include "PointBase.h"

#include <vector>
#include <memory>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

/**
 * Construire la surface en suivant l'algorithme du plus proche voisin :
 * - on part d'un point de départ (ici le point avec le plus petit ID)
 * - à chaque étape, on ajoute le point non encore utilisé le plus proche du point courant (on calcule la distance euclidienne aux autres point et on prend le minimum)
 *   - on répète jusqu'à ce que tous les points soient utilisés
 */
void ConstructeurSurfaceParProchVoisin::construireSurface(Surface& surface, const PointCloud& nuage)
{
    surface.clearPoints();

    const auto& elements = nuage.getPoints();

    vector<shared_ptr<PointBase>> points;
    points.reserve(elements.size());

    
    for (const auto& element : elements) {
        auto point = dynamic_pointer_cast<PointBase>(element);
        if (point) {
            points.push_back(point);
        }
    }

    if (points.empty()) {
        return;
    }

    const std::size_t n = points.size();
    std::vector<bool> used(n, false);

    // Point de départ : le point avec le plus petit ID
    auto start_it = min_element(points.begin(), points.end(), 
        [](const shared_ptr<PointBase>& a, const shared_ptr<PointBase>& b) {
            return a->getId() < b->getId();
        });
    std::size_t currentIndex = distance(points.begin(), start_it);
    
    used[currentIndex] = true;
    surface.addPoint(points[currentIndex]);

    for (size_t step = 1; step < n; ++step) {
        size_t nextIndex = n;
        double bestDist2 = numeric_limits<double>::max();

        auto [cx, cy] = points[currentIndex]->getXY();

        for (size_t i = 0; i < n; ++i) {
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
            // on arrive à la fin du vecteur (tous les points utilisés)
            break;
        }

        used[nextIndex] = true;
        surface.addPoint(points[nextIndex]);
        currentIndex = nextIndex;
    }
}
