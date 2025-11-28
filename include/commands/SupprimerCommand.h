#pragma once

#include "Commande.h"
#include "../models/Plan.h"
#include "../models/GraphElement.h"
#include <memory>

using namespace std;

class SupprimerCommand : public Commande {
public:
    SupprimerCommand(Plan& plan, int id);
    void execute() override;
    void undo() override;
private:
    Plan& m_plan;
    int m_id;
    shared_ptr<GraphElement> m_backup;
};
