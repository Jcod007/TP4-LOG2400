#pragma once
#include "Affichage.h"
#include <string>
#include <vector>
#include <memory>
#include "GraphElement.h"

class AffichageOrthese : public Affichage {
public:
    // Le "Template Method" : l'algorithme principal
    void afficher(Plan& plan) const override;

protected:
    // LE HOOK (Méthode primitive) : À implémenter par les enfants
    // Retourne ce qu'on doit écrire dans la case (ex: "o", "#", "12")
    virtual std::string getRepresentation(std::shared_ptr<GraphElement> element) const = 0;
};