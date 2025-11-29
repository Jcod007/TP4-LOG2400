#pragma once

#include <vector>
#include <memory>
#include "PointCloud.h"
#include "SurfaceBuilder.h"
#include "PointBase.h"
#include "Point.h"

using namespace std;

class Surface {
public:
    explicit Surface(shared_ptr<PointCloud> pointCloud);

    // Définit la stratégie de construction de la surface
    void setSurfaceBuilder(shared_ptr<SurfaceBuilder> builder);

    void build();

    const vector<shared_ptr<PointBase>>& getPoints() const;

    void clearPoints();
    void addPoint(const shared_ptr<PointBase>& point); //En fait c'est un composite de PointBase

private:
    shared_ptr<PointCloud> pointCloud_;
    shared_ptr<SurfaceBuilder> surfaceBuilderStrategie_;
    vector<shared_ptr<PointBase>> points_;
};
