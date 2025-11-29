#include "AffichageAvecID.h"

std::string AffichageAvecID::getRepresentation(std::shared_ptr<GraphElement> element) const {
        // On retourne simplement l'ID
        return std::to_string(element->getId());
}