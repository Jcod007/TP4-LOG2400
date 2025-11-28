#pragma once

#include "Plan.h"

class Affichage
{
    public:
        virtual void afficher(Plan& plan) const = 0;
        virtual ~Affichage() = default;
};