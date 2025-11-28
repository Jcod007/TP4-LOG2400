#include "DeplacerCommand.h"
#include "GraphUtils.h"

DeplacerCommand::DeplacerCommand(Plan& plan, int id, const pair<int,int>& position):m_plan(plan), m_id(id), m_position(position)
{

}

void DeplacerCommand::executer()
{
    // Sauvegarder l'ancienne position pour undo
    auto element = m_plan.getGraphElementById(m_id);
    if (element) {
        // Supposons que GraphElement a une méthode getPosition()
        getPositionIfPoint(element, m_oldPosition);
        // Comme getPosition n'existe pas, on laisse m_oldPosition inchangé pour l'instant
    }
    m_plan.deplacerGraphElementById(m_id, m_position);
}

void DeplacerCommand::undo()
{
    m_plan.deplacerGraphElementById(m_id, m_oldPosition);
}