#pragma once

#include "Commande.h"
#include "Affichage.h"
#include <memory>

class Commande_O : public Commande
{
    public:
        void executer() const override;
    
    private:
        unique_ptr<Affichage> m_affichage;
        Plan& m_plan;
};  