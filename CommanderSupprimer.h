#pragma once

#include "Commande.h"
#include "Plan.h"
#include "GraphElement.h"
#include <memory>
#include <vector>

using namespace std;

class CommanderSupprimer : public Commande {
public:
    CommanderSupprimer(Plan& plan, int id);
    void executer() override;
    void undo() override;
private:
    Plan& m_plan;
    int m_id;
    shared_ptr<GraphElement> m_sauvegarde;
    vector<int> m_idsNuagesAffectés;  // IDs des PointClouds qui contenaient cet élément
};
