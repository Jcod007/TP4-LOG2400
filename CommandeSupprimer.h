#pragma once

#include "Commande.h"
#include "Plan.h"
#include "ElementGraphique.h"
#include <memory>
#include <vector>


class CommandeSupprimer : public Commande {
public:
    CommandeSupprimer(Plan& plan, int id);
    void executer() override;
    void annuler() override;
private:
    Plan& m_plan;
    int m_id;
    std::shared_ptr<ElementGraphique> m_sauvegarde;
    std::vector<int> m_idsNuagesAffectes;  // IDs des NuagePoints qui contenaient cet élément
};
