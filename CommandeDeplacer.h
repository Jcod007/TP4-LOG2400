#pragma once

#include "Commande.h"
#include "Plan.h"

class CommandeDeplacer : public Commande
{
    public:
        CommandeDeplacer(Plan& plan, int id, const pair<int,int>& position);
        void executer() override;
        void annuler() override;
    private:
        Plan& m_plan;
        int m_id;
        pair<int,int> m_position;
        pair<int,int> m_anciennePosition;
};
