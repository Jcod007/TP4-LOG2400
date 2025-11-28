#pragma once

#include "Commande.h"
#include <memory>
#include <vector>

using namespace std;

class Invocateur
{
    public:
        void setCommande(shared_ptr<Commande> cmd);
        void executerCommande();
        
    private:
        shared_ptr<Commande> m_commande;
        vector<shared_ptr<Commande>> m_historique;   
};