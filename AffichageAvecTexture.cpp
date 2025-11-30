#include "AffichageAvecTexture.h"

std::string AffichageAvecTexture::obtenirRepresentation(std::shared_ptr<ElementGraphique> element) const {
        // Tenter de convertir en PointBase pour avoir la texture
        auto ptr = std::dynamic_pointer_cast<PointBase>(element);
        
        if (ptr) {
            std::string txt = ptr->obtenirTexture();
            // Si texture vide, on met un point par défaut (selon convention)
            if (txt.empty() || txt == "\"\"") return ".";
            return txt;
        }
        return "?";
}