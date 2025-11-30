#include "CommandeDeplacer.h"
#include "UtilitairesGraphique.h"

CommandeDeplacer::CommandeDeplacer(Plan& plan, int id, const pair<int,int>& position):m_plan(plan), m_id(id), m_position(position)
{

}

void CommandeDeplacer::executer()
{
    // Sauvegarder l'ancienne position pour undo
    auto element = m_plan.obtenirElementGraphiqueParId(m_id);
    if (element) {
        // Supposons que ElementGraphique a une méthode obtenirPosition()
        obtenirPositionSiPoint(element, m_anciennePosition);
        // Comme obtenirPosition n'existe pas, on laisse m_anciennePosition inchangé pour l'instant
    }
    m_plan.deplacerElementGraphiqueParId(m_id, m_position);
}

void CommandeDeplacer::annuler()
{
    m_plan.deplacerElementGraphiqueParId(m_id, m_anciennePosition);
}