#pragma once

#include "ElementGraphique.h"
#include "NuagePoints.h"
#include "Surface.h"
#include "ConstructeurSurface.h"
#include <vector>
#include <memory>
#include <string>


class Plan
{
    public:
        Plan() = default;
        ~Plan() = default;
        std::vector<std::shared_ptr<ElementGraphique>> obtenirElements() const;
        std::shared_ptr<NuagePoints> obtenirNuagesParTexture(const std::string& texture) const;
        std::shared_ptr<NuagePoints> obtenirOuCreerNuageParTexture(std::string texture);
        std::shared_ptr<ElementGraphique> obtenirElementGraphiqueParId(int id);
        void definirElementsGraphiques(std::vector<std::shared_ptr<ElementGraphique>> graphElements);
        void supprimerElementGraphiqueParId(int id);
        void deplacerElementGraphiqueParId(int id, const std::pair<int,int>& position);
        std::shared_ptr<NuagePoints> fusionnerEnNuage(std::vector<int> ids, std::vector<std::string> textures);
        void creerSurface(int cloudId, std::shared_ptr<ConstructeurSurface> builder);
        void ajouterElementGraphique(std::shared_ptr<ElementGraphique> element);

    
    private:
        std::vector<std::shared_ptr<ElementGraphique>> m_elementsGraphiques;
};