#pragma once
#include "AffichageOrthese.h"
#include "PointBase.h"

class AffichageAvecTexture : public AffichageOrthese {
protected:
    std::string obtenirRepresentation(std::shared_ptr<GraphElement> element) const override;
    
};