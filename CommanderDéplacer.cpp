#include "CommanderDéplacer.h"
#include "GraphUtils.h"

CommanderDéplacer::CommanderDéplacer(Plan& plan, int id, const pair<int,int>& position):m_plan(plan), m_id(id), m_position(position)
{

}

void CommanderDéplacer::executer()
{
    // Sauvegarder l'ancienne position pour undo
    auto element = m_plan.getGraphElementById(m_id);
    if (element) {
        // Supposons que GraphElement a une méthode getPosition()
        getPositionIfPoint(element, m_anciennePosition);
        // Comme getPosition n'existe pas, on laisse m_anciennePosition inchangé pour l'instant
    }
    m_plan.deplacerGraphElementById(m_id, m_position);
}

void CommanderDéplacer::undo()
{
    m_plan.deplacerGraphElementById(m_id, m_anciennePosition);
}