#pragma once

#include "Commande.h"
#include "Plan.h"

class CommanderDéplacer : public Commande
{
    public:
        CommanderDéplacer(Plan& plan, int id, const pair<int,int>& position);
        void executer() override;
        void undo() override;
    private:
        Plan& m_plan;
        int m_id;
        pair<int,int> m_position;
        pair<int,int> m_anciennePosition;
};
