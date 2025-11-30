#pragma once
#include "AffichageOrthese.h"

class AffichageAvecID : public AffichageOrthese {
protected:
    std::string obtenirRepresentation(std::shared_ptr<GraphElement> element) const override;
    
};