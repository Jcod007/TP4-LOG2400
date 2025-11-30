#pragma once

#include "ElementGraphique.h"
#include "NuagePoints.h"
#include "Surface.h"
#include "ConstructeurSurface.h"
#include <vector>
#include <memory>
#include <string>

using namespace std;


class Plan
{
    public:
        Plan() = default;
        ~Plan() = default;
        vector<shared_ptr<ElementGraphique>> obtenirElements() const;
        shared_ptr<NuagePoints> obtenirNuagesParTexture(const string& texture) const;
        shared_ptr<NuagePoints> obtenirOuCreerNuageParTexture(string texture);
        shared_ptr<ElementGraphique> obtenirElementGraphiqueParId(int id);
        void definirElementsGraphiques(vector<shared_ptr<ElementGraphique>> graphElements);
        void supprimerElementGraphiqueParId(int id);
        void deplacerElementGraphiqueParId(int id, const pair<int,int>& position);
        shared_ptr<NuagePoints> fusionnerEnNuage(vector<int> ids, vector<string> textures);
        void creerSurface(int cloudId, shared_ptr<ConstructeurSurface> builder);
        void ajouterElementGraphique(shared_ptr<ElementGraphique> element);

    
    private:
        vector<shared_ptr<ElementGraphique>> m_elementsGraphiques;
};