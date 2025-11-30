#include "CommandeDeplacer.h"
#include "UtilitairesGraphique.h"
using namespace std;

CommandeDeplacer::CommandeDeplacer(Plan& plan, int id, const std::pair<int,int>& position):m_plan(plan), m_id(id), m_position(position)
{

}

void CommandeDeplacer::executer()
{
    // Sauvegarder l'ancienne position pour undo
    auto element = m_plan.obtenirElementGraphiqueParId(m_id);
    if (element) {
        obtenirPositionSiPoint(element, m_anciennePosition);
    }
    m_plan.deplacerElementGraphiqueParId(m_id, m_position);
}

void CommandeDeplacer::annuler()
{
    m_plan.deplacerElementGraphiqueParId(m_id, m_anciennePosition);
}