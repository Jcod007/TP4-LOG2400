#include "FusionEnNuageCommand.h"
#include <iostream>

using namespace std;

FusionEnNuageCommand::FusionEnNuageCommand(Plan& plan, const vector<int>& ids, const vector<string>& textures)
    : m_plan(plan), m_ids(ids), m_textures(textures) {
}

void FusionEnNuageCommand::executer() {
    // Appeler la méthode fusionEnNuage du plan
    m_plan.fusionEnNuage(m_ids, m_textures);
    
}

void FusionEnNuageCommand::undo() {
    // TODO: Implémenter l'annulation
    // Il faudrait retirer le nuage créé et restaurer les points
    cout << "Undo de FusionEnNuageCommand pas encore implémenté" << endl;
}
