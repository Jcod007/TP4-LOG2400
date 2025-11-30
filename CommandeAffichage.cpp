#include "CommandeAffichage.h"
using namespace std;

CommandeAffichage::CommandeAffichage(std::unique_ptr<Affichage> affichage, Plan& plan):m_affichage(std::move(affichage)), m_plan(plan)
{

}

void CommandeAffichage::executer()
{
    m_affichage->afficher(m_plan);
}