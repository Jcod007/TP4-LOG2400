#include "Invocateur.h"

void Invocateur::setCommande(unique_ptr<Commande> cmd)
{
    commande_ = move(cmd);
}

void Invocateur::executerCommande()
{
    if(commande_)
    {
        commande_->executer();
        historique_.push_back(move(commande_));
    }
}