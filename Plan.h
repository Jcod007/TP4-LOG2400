#pragma once

#include "GraphElement.h"
#include <vector>
#include <memory>

using namespace std;


class Plan
{
    public:
        Plan() = default;
        ~Plan() = default;
        vector<shared_ptr<GraphElement>> getGraphElements() const;
        shared_ptr<GraphElement> getGraphElementById(int id);
        void setGraphElements(vector<shared_ptr<GraphElement>> graphElements);
        void supprimerGraphElementById(int id);
        void deplacerGraphElementById(int id, const pair<int,int>& position);
        vector<shared_ptr<GraphElement>> fusionEnNuage(vector<int> ids);
    
    private:
        vector<shared_ptr<GraphElement>> m_graphElements;
}; 