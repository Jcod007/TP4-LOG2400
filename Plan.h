#pragma once

#include "GraphElement.h"
#include "PointCloud.h"
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
        vector<shared_ptr<GraphElement>> getGraphElements() const;
        shared_ptr<PointCloud> getNuagesByTexture(const string& texture) const;
        shared_ptr<PointCloud> getOrCreateNuageByTexture(string texture);
        shared_ptr<GraphElement> getGraphElementById(int id);
        void setGraphElements(vector<shared_ptr<GraphElement>> graphElements);
        void supprimerGraphElementById(int id);
        void deplacerGraphElementById(int id, const pair<int,int>& position);
        shared_ptr<PointCloud> fusionEnNuage(vector<int> ids, vector<string> textures);
        void creerSurface(int cloudId, shared_ptr<ConstructeurSurface> builder);
        void addGraphElement(shared_ptr<GraphElement> element);

    
    private:
        vector<shared_ptr<GraphElement>> m_graphElements;
};