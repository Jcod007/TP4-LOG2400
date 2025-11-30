#include "CreerSurfaceCommand.h"
#include <iostream>
#include "PointCloud.h" // Include PointCloud for dynamic_pointer_cast

CreerSurfaceCommand::CreerSurfaceCommand(Plan& plan, std::shared_ptr<ConstructeurSurface> builder)
    : m_plan(plan), m_builder(builder) {}

void CreerSurfaceCommand::executer() {
    bool surfaceCreated = false;
    const auto& elements = m_plan.getGraphElements();
    for (const auto& element : elements) {
        if (auto cloud = std::dynamic_pointer_cast<PointCloud>(element)) {
            m_plan.creerSurface(cloud->getId(), m_builder);
            surfaceCreated = true;
        }
    }

    if (surfaceCreated) {
        std::cout << "Surfaces creees avec succes !\n";
    } else {
        std::cout << "Aucun nuage de points trouve pour creer des surfaces.\n";
    }
}
