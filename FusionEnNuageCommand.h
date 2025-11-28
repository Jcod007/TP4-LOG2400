#pragma once

#include "Commande.h"
#include "Plan.h"
#include <vector>
#include <memory>

class FusionEnNuageCommand : public Commande {
private:
    Plan& m_plan;
    std::vector<int> m_ids;
    std::vector<string> m_textures;
    
public:
    FusionEnNuageCommand(Plan& plan, const std::vector<int>& ids, const std::vector<string>& textures);
    
    void executer() override;
    void undo() override;
};
