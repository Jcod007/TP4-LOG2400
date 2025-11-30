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
    std::shared_ptr<NuagePoints> obtenirNuage() const;

    std::string dessiner() const override {
        return "";
    }

private:
    std::shared_ptr<NuagePoints> m_nuagePoints;
    std::shared_ptr<ConstructeurSurface> m_constructeurStrategie;
    std::vector<std::shared_ptr<PointBase>> m_points;
};
