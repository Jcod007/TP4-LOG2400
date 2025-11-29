#pragma once
#include "AffichageOrthese.h"

class AffichageAvecID : public AffichageOrthese {
protected:
    std::string getRepresentation(std::shared_ptr<GraphElement> element) const override;
    
};