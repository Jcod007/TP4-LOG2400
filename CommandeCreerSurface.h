#pragma once

#include "Commande.h"
#include "Plan.h"
#include "ConstructeurSurface.h"
#include <memory>

class CommandeCreerSurface : public Commande {
public:
    CommandeCreerSurface(Plan& plan, std::shared_ptr<ConstructeurSurface> builder);
    void executer() override;

private:
    Plan& m_plan;
    std::shared_ptr<ConstructeurSurface> m_builder;
};
