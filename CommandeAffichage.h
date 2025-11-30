#pragma once

#include "Commande.h"
#include "Affichage.h"
#include <memory>

using namespace std;

class CommandeAffichage : public Commande
{

    public:
        void executer() override;
        ~CommandeAffichage() override = default;
        CommandeAffichage(unique_ptr<Affichage> affichage, Plan& plan);
    
    private:
        unique_ptr<Affichage> m_affichage;
        Plan& m_plan;
    
};