#include "CommandeCreerSurface.h"
#include <iostream>
#include "NuagePoints.h" // Include NuagePoints for dynamic_pointer_cast

CommandeCreerSurface::CommandeCreerSurface(Plan& plan, std::shared_ptr<ConstructeurSurface> builder)
    : m_plan(plan), m_builder(builder) {}

void CommandeCreerSurface::executer() {
    bool surfaceCreated = false;
    const auto& elements = m_plan.obtenirElements();
    for (const auto& element : elements) {
        if (auto cloud = std::dynamic_pointer_cast<NuagePoints>(element)) {
            m_plan.creerSurface(cloud->obtenirId(), m_builder);
            surfaceCreated = true;
        }
    }

    if (surfaceCreated) {
        std::cout << "Surfaces creees avec succes !\n";
    } else {
        std::cout << "Aucun nuage de points trouve pour creer des surfaces.\n";
    }
}
