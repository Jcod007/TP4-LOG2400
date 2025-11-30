#include "Surface.h"
#include "ConstructeurSurface.h"
#include "NuagePoints.h"
#include "PointBase.h"

using namespace std;

Surface::Surface(shared_ptr<NuagePoints> pointCloud)
    : ElementGraphique(), nuagePoints_(move(pointCloud))
{
}

void Surface::definirConstructeurSurface(shared_ptr<ConstructeurSurface> builder)
{
    constructeurStrategie_ = move(builder);
}

void Surface::construire()
{
    if (!constructeurStrategie_ || !nuagePoints_) {
        // si il n'y a pas de nuage de point ou de stratégie, on ne fait rien
        return;
    }

    // La stratégie fait le taf
    constructeurStrategie_->construireSurface(*this, *nuagePoints_);
}

const vector<shared_ptr<PointBase>>& Surface::obtenirPoints() const
{
    return points_;
}

void Surface::viderPoints()
{
    points_.clear();
}

void Surface::ajouterPoint(const shared_ptr<PointBase>& point)
{
    points_.push_back(point);
}
