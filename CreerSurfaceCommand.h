#pragma once

#include "Commande.h"
#include "Plan.h"
#include "SurfaceBuilder.h"
#include <memory>

class CreerSurfaceCommand : public Commande {
public:
    CreerSurfaceCommand(Plan& plan, std::shared_ptr<SurfaceBuilder> builder);
    void executer() override;

private:
    Plan& m_plan;
    std::shared_ptr<SurfaceBuilder> m_builder;
};
