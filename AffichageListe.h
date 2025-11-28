#pragma once

#include "Affichage.h"
#include "Plan.h"

class AffichageListe : public Affichage
{
    public: 
        void afficher(Plan& plan) const override;
        ~AffichageListe() override = default;
   

};