#pragma once

#include "Commande.h"
#include "Plan.h"
#include "ConstructeurSurface.h"
#include <memory>

class CreerSurfaceCommand : public Commande {
public:
    CreerSurfaceCommand(Plan& plan, std::shared_ptr<ConstructeurSurface> builder);
    void executer() override;

private:
    Plan& m_plan;
    std::shared_ptr<ConstructeurSurface> m_builder;
};
