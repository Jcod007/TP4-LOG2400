#include "AffichageAvecID.h"
using namespace std;
std::string AffichageAvecID::obtenirRepresentation(std::shared_ptr<ElementGraphique> element) const {
    return std::to_string(element->obtenirId());
}