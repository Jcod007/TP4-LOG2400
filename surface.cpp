#pragma once

#include "graphElement.h"
#include "tpaffichage.h"
#include "PointCloud.h"
#include <vector>
#include <tuple>
#include <cmath>
#include <iostream>
#include <sstream>
#include <algorithm>



class SurfaceBuilder {
protected:
    PointCloud* pointCloud_;  

public:
   
    explicit SurfaceBuilder(PointCloud* pointCloud)
        : pointCloud_(pointCloud) {}

    virtual ~SurfaceBuilder() = default;

    
    void setPointCloud(PointCloud* pointCloud) {
        pointCloud_ = pointCloud;
    }

    virtual void build() = 0; 
};



class InOrderSurfaceBuilder : public SurfaceBuilder {
public:

    using SurfaceBuilder::SurfaceBuilder;

    void build() override { 
        //Ajouter l'implémentation ici
    }
};




class NearestNeighborSurfaceBuilder : public SurfaceBuilder {
public:
    using SurfaceBuilder::SurfaceBuilder;

    void build() override {
        // Ajouter l'implémentation ici
    }
};




class Surface {
private:
    SurfaceBuilder* surfaceBuilderStrategie_;   

public:
    
    Surface(SurfaceBuilder* strategie = nullptr)
        : surfaceBuilderStrategie_(strategie) {}

   
    void setSurfaceBuilder(SurfaceBuilder* strategie) {
        surfaceBuilderStrategie_ = strategie;
    }

    
    void build() {
        if (surfaceBuilderStrategie_ != nullptr) {
            surfaceBuilderStrategie_->build();
        }
    
    }
};
 
