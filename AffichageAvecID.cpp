#include "AffichageAvecID.h"

std::string AffichageAvecID::obtenirRepresentation(std::shared_ptr<ElementGraphique> element) const {
        // On retourne simplement l'ID
        return std::to_string(element->obtenirId());
}