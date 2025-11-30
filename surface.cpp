#include "Surface.h"
#include "SurfaceBuilder.h"
#include "PointCloud.h"
#include "PointBase.h"

using namespace std;

Surface::Surface(shared_ptr<PointCloud> pointCloud)
    : GraphElement(), pointCloud_(move(pointCloud))
{
}

void Surface::setSurfaceBuilder(shared_ptr<SurfaceBuilder> builder)
{
    surfaceBuilderStrategie_ = move(builder);
}

void Surface::build()
{
    if (!surfaceBuilderStrategie_ || !pointCloud_) {
        // si il n'y a pas de nuage de point ou de stratégie, on ne fait rien
        return;
    }

    // La stratégie fait le taf
    surfaceBuilderStrategie_->buildSurface(*this, *pointCloud_);
}

const vector<shared_ptr<PointBase>>& Surface::getPoints() const
{
    return points_;
}

void Surface::clearPoints()
{
    points_.clear();
}

void Surface::addPoint(const shared_ptr<PointBase>& point)
{
    points_.push_back(point);
}
