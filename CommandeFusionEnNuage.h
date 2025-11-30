#pragma once

#include "Commande.h"
#include "Plan.h"
#include <vector>
#include <memory>

class CommandeFusionEnNuage : public Commande {
private:
    Plan& m_plan;
    std::vector<int> m_ids;
    std::vector<std::string> m_textures;
    
public:
    CommandeFusionEnNuage(Plan& plan, const std::vector<int>& ids, const std::vector<std::string>& textures);
    
    void executer() override;
    void annuler() override;
};
