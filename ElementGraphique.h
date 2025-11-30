#pragma once
#include <string>
#include <memory>
#include <vector>


class ElementGraphique {
protected:
    int m_id;
    static int m_prochainId;

public:
    ElementGraphique();
    virtual ~ElementGraphique() = default;

    virtual int obtenirId() const;
    virtual std::string dessiner() const = 0;
    virtual void ajouterEnfant(std::shared_ptr<ElementGraphique> enfant) {}
    virtual void ajouterEnfants(const std::vector<std::shared_ptr<ElementGraphique>>& enfants) {}
};
