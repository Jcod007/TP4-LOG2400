#include "Plan.h"
#include "PointBase.h"
#include "PointCloud.h"
#include <algorithm>
#include <iostream>

using namespace std;

vector<shared_ptr<GraphElement>> Plan::getGraphElements() const {
    return m_graphElements;
}

void Plan::setGraphElements(vector<shared_ptr<GraphElement>> graphElements) {
    m_graphElements = graphElements;
}

shared_ptr<GraphElement> Plan::getGraphElementById(int id) {
    for (auto& element : m_graphElements) {
        if (element->getId() == id) {
            return element;
        }
    }
    return nullptr;
}