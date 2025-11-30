#include "CommandeFusionEnNuage.h"
#include <iostream>

using namespace std;

CommandeFusionEnNuage::CommandeFusionEnNuage(Plan& plan, const vector<int>& ids, const vector<string>& textures)
    : m_plan(plan), m_ids(ids), m_textures(textures) {
}

void CommandeFusionEnNuage::executer() {
    // Appeler la méthode fusionnerEnNuage du plan
    m_plan.fusionnerEnNuage(m_ids, m_textures);
    
}

void CommandeFusionEnNuage::annuler() {
    // TODO: Implémenter l'annulation
    // Il faudrait retirer le nuage créé et restaurer les points
    cout << "Undo de CommandeFusionEnNuage pas encore implémenté" << endl;
}
