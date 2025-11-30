#include "CommandeSupprimer.h"
#include "NuagePoints.h"
#include <iostream>

using namespace std;

CommandeSupprimer::CommandeSupprimer(Plan& plan, int id) 
    : m_plan(plan), m_id(id) {
}

void CommandeSupprimer::executer() {
    // Sauvegarder l'élément pour undo
    m_sauvegarde = m_plan.obtenirElementGraphiqueParId(m_id);
    if (m_sauvegarde == nullptr) {
        cerr << "Element non trouvé" << endl;
        return;
    }
    
    // Sauvegarder les IDs des NuagePoints qui contiennent cet élément
    m_idsNuagesAffectes.clear();
    for (const auto& element : m_plan.obtenirElements()) {
        if (auto cloud = dynamic_pointer_cast<NuagePoints>(element)) {
            if (cloud->contientPoint(m_id)) {
                m_idsNuagesAffectes.push_back(cloud->obtenirId());
            }
        }
    }
    
    // Supprimer l'élément (du Plan ET des NuagePoints)
    m_plan.supprimerElementGraphiqueParId(m_id);
}

void CommandeSupprimer::annuler() {
    if (m_sauvegarde == nullptr) {
        cerr << "Aucun backup disponible pour undo" << endl;
        return;
    }
    
    // Remettre l'élément dans le Plan
    m_plan.ajouterElementGraphique(m_sauvegarde);
    
    // Remettre l'élément dans les NuagePoints qui le contenaient
    for (int cloudId : m_idsNuagesAffectes) {
        auto cloudElement = m_plan.obtenirElementGraphiqueParId(cloudId);
        if (auto cloud = dynamic_pointer_cast<NuagePoints>(cloudElement)) {
            cloud->ajouterEnfant(m_sauvegarde); // Use ajouterEnfant as per NuagePoints.h
        }
    }
}