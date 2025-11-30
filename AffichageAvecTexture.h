#pragma once
#include "AffichageOrthese.h"
#include "PointBase.h"

class AffichageAvecTexture : public AffichageOrthese {
protected:
    std::string obtenirRepresentation(std::shared_ptr<ElementGraphique> element) const override;
    
};