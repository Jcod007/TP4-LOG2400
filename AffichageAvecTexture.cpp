#include "AffichageAvecTexture.h"
#include "PointBase.h"
using namespace std;

std::string AffichageAvecTexture::obtenirRepresentation(std::shared_ptr<ElementGraphique> element) const {
    if (auto point = dynamic_pointer_cast<PointBase>(element)) {
        string texture = point->obtenirTexture();
        // Si la texture est vide ou contient seulement des espaces, retourner "."
        if (texture.empty() || texture == " " || texture == "") {
            return ".";
        }
        return texture;
    }
    return " "; // Default representation for non-point elements
}