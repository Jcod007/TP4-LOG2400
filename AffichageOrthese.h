#pragma once
#include "Affichage.h"
#include <string>
#include <vector>
#include <memory>
#include "ElementGraphique.h"

class AffichageOrthese : public Affichage {
public:
    // Le "Template Method" : l'algorithme principal
    void afficher(Plan& plan) const override;

protected:
    // LE HOOK (Méthode primitive) : À implémenter par les enfants
    // Retourne ce qu'on doit écrire dans la case (ex: "o", "#", "12")
    virtual std::string obtenirRepresentation(std::shared_ptr<ElementGraphique> element) const = 0;
};