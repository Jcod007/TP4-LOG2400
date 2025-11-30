#include "CommandeAffichage.h"

CommandeAffichage::CommandeAffichage(unique_ptr<Affichage> affichage, Plan& plan):m_affichage(move(affichage)), m_plan(plan)
{

}

void CommandeAffichage::executer()
{
    m_affichage->afficher(m_plan);
}