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