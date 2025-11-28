#pragma once

#include "Affichage.h"

class AffichageOrthese : public Affichage
{
    public: 
        void afficher(Plan& plan) const override;
        
};
