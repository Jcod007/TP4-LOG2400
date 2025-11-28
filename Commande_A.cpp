#include "Commande_A.h"

Commande_A::Commande_A(unique_ptr<Affichage> affichage, Plan& plan):m_affichage(move(affichage)), m_plan(plan)
{

}

void Commande_A::executer()
{
    m_affichage->afficher(m_plan);
}