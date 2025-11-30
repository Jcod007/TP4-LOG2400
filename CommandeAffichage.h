#pragma once

#include "Commande.h"
#include "Affichage.h"
#include <memory>


class CommandeAffichage : public Commande
{

    public:
        void executer() override;
        bool estAnnulable() const override { return false; }
        ~CommandeAffichage() override = default;
        CommandeAffichage(std::unique_ptr<Affichage> affichage, Plan& plan);
    
    private:
        std::unique_ptr<Affichage> m_affichage;
        Plan& m_plan;
    
};