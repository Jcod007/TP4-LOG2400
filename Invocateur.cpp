#include "Invocateur.h"

void Invocateur::setCommande(shared_ptr<Commande> cmd)
{
    m_commande = cmd;
}

void Invocateur::executerCommande()
{
    if(m_commande)
    {
        m_commande->executer();
        m_historique.push_back(m_commande);
    }
}