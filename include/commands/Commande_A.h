#pragma once

#include "Commande.h"
#include "Affichage.h"
#include <memory>

using namespace std;

class Commande_A : public Commande
{

    public:
        void executer() const override;
        ~Commande_A() override = default;
        Commande_A(unique_ptr<Affichage> affichage, Plan& plan);
    
    private:
        unique_ptr<Affichage> m_affichage;
        Plan& m_plan;
    
};