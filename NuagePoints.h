#pragma once

#include <vector>
#include <memory>
#include <string>
#include "ElementGraphique.h"

class NuagePoints : public ElementGraphique {
private:
    std::vector<std::shared_ptr<ElementGraphique>> m_points;
    std::string m_texture;

public:
    NuagePoints(std::string texture);
    NuagePoints(const std::vector<std::shared_ptr<ElementGraphique>>& points, std::string texture);
    std::vector<int> obtenirTousIdsPointsRecursivement() const;
    const std::vector<std::shared_ptr<ElementGraphique>>& obtenirPoints() const;
    void ajouterEnfant(std::shared_ptr<ElementGraphique> enfant) override;
    void ajouterEnfants(const std::vector<std::shared_ptr<ElementGraphique>>& enfants) override;
    void supprimerPointParId(int id);
    bool contientPoint(int id) const;
    std::string obtenirTexture() const;

    int obtenirId() const override;
    std::string dessiner() const override;
};
