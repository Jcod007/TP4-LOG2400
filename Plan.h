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
        bool supprimerGraphElementById(int id);
        bool deplacerGraphElementById(int id, int newX, int newY);
        vector<shared_ptr<GraphElement>> fusionEnNuage(vector<int> ids);
    
    private:
        vector<shared_ptr<GraphElement>> m_graphElements;
}; 