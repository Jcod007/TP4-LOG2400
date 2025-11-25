#pragma once

#include "Commande.h"
#include <memory>
#include <vector>

using namespace std;

class Invocateur
{
    public:
        void setCommande(unique_ptr<Commande> cmd);
        void executerCommande();
        
    private:
        unique_ptr<Commande> commande_;
        vector<unique_ptr<Commande>> historique_;   
};