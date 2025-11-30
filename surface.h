#pragma once

#include "ElementGraphique.h"
#include <memory>
#include <vector>

class NuagePoints;
class ConstructeurSurface;
class PointBase;

class Surface : public ElementGraphique {
public:
    Surface(std::shared_ptr<NuagePoints> pointCloud);

    void definirConstructeurSurface(std::shared_ptr<ConstructeurSurface> builder);
    void construire();

    const std::vector<std::shared_ptr<PointBase>>& obtenirPoints() const;
    void viderPoints();
    void ajouterPoint(const std::shared_ptr<PointBase>& point);

    std::string dessiner() const override {
        return "Surface"; // Placeholder
    }

private:
    std::shared_ptr<NuagePoints> nuagePoints_;
    std::shared_ptr<ConstructeurSurface> constructeurStrategie_;
    std::vector<std::shared_ptr<PointBase>> points_;
};
