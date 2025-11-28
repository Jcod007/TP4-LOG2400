#include "SupprimerCommand.h"
#include "PointCloud.h"
#include <iostream>

using namespace std;

SupprimerCommand::SupprimerCommand(Plan& plan, int id) 
    : m_plan(plan), m_id(id) {
}

void SupprimerCommand::execute() {
    // Sauvegarder l'élément pour undo
    m_backup = m_plan.getGraphElementById(m_id);
    if (m_backup == nullptr) {
        cerr << "Element non trouvé" << endl;
        return;
    }
    
    // Sauvegarder les IDs des PointClouds qui contiennent cet élément
    m_affectedCloudIds.clear();
    for (const auto& element : m_plan.getGraphElements()) {
        if (auto cloud = dynamic_pointer_cast<PointCloud>(element)) {
            if (cloud->containsPoint(m_id)) {
                m_affectedCloudIds.push_back(cloud->getId());
            }
        }
    }
    
    // Supprimer l'élément (du Plan ET des PointClouds)
    m_plan.supprimerGraphElementById(m_id);
}

void SupprimerCommand::undo() {
    if (m_backup == nullptr) {
        cerr << "Aucun backup disponible pour undo" << endl;
        return;
    }
    
    // Remettre l'élément dans le Plan
    auto elements = m_plan.getGraphElements();
    elements.push_back(m_backup);
    m_plan.setGraphElements(elements);
    
    // Remettre l'élément dans les PointClouds qui le contenaient
    for (int cloudId : m_affectedCloudIds) {
        auto cloudElement = m_plan.getGraphElementById(cloudId);
        if (auto cloud = dynamic_pointer_cast<PointCloud>(cloudElement)) {
            cloud->addElement(m_backup);
        }
    }
}