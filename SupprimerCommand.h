#pragma once

#include "Commande.h"
#include "Plan.h"
#include "GraphElement.h"
#include <memory>
#include <vector>

using namespace std;

class SupprimerCommand : public Commande {
public:
    SupprimerCommand(Plan& plan, int id);
    void executer() override;
void NewFunction();
    //void undo() override;
private:
    Plan& m_plan;
    int m_id;
    shared_ptr<GraphElement> m_backup;
    vector<int> m_affectedCloudIds;  // IDs des PointClouds qui contenaient cet élément
};
