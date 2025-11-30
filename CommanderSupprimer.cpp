#include "CommanderSupprimer.h"
#include "PointCloud.h"
#include <iostream>

using namespace std;

CommanderSupprimer::CommanderSupprimer(Plan& plan, int id) 
    : m_plan(plan), m_id(id) {
}

void CommanderSupprimer::executer() {
    // Sauvegarder l'élément pour undo
    m_sauvegarde = m_plan.getGraphElementById(m_id);
    if (m_sauvegarde == nullptr) {
        cerr << "Element non trouvé" << endl;
        return;
    }
    
    // Sauvegarder les IDs des PointClouds qui contiennent cet élément
    m_idsNuagesAffectés.clear();
    for (const auto& element : m_plan.getGraphElements()) {
        if (auto cloud = dynamic_pointer_cast<PointCloud>(element)) {
            if (cloud->containsPoint(m_id)) {
                m_idsNuagesAffectés.push_back(cloud->getId());
            }
        }
    }
    
    // Supprimer l'élément (du Plan ET des PointClouds)
    m_plan.supprimerGraphElementById(m_id);
}

void CommanderSupprimer::undo() {
    if (m_sauvegarde == nullptr) {
        cerr << "Aucun backup disponible pour undo" << endl;
        return;
    }
    
    // Remettre l'élément dans le Plan
    m_plan.addGraphElement(m_sauvegarde);
    
    // Remettre l'élément dans les PointClouds qui le contenaient
    for (int cloudId : m_idsNuagesAffectés) {
        auto cloudElement = m_plan.getGraphElementById(cloudId);
        if (auto cloud = dynamic_pointer_cast<PointCloud>(cloudElement)) {
            cloud->addChild(m_sauvegarde); // Use addChild as per PointCloud.h
        }
    }
}