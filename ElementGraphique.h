#pragma once
#include <string>
#include <memory>
#include <vector>

using namespace std;

class ElementGraphique {
protected:
    int m_id;
    static int m_prochainId;

public:
    ElementGraphique();
    virtual ~ElementGraphique() = default;

    virtual int obtenirId() const;
    virtual string dessiner() const = 0;
    virtual void ajouterEnfant(shared_ptr<ElementGraphique> enfant) {}
    virtual void ajouterEnfants(const vector<shared_ptr<ElementGraphique>>& enfants) {}
};
