#include "GraphUtils.h"
#include "PointBase.h"

bool getPositionIfPoint(const std::shared_ptr<GraphElement>& elem, std::pair<int,int>& outPos)
{
    auto pb = std::dynamic_pointer_cast<PointBase>(elem);
    if (!pb) return false;
    outPos = pb->getXY();
    return true;
}

bool setPositionIfPoint(const std::shared_ptr<GraphElement>& elem, int x, int y)
{
    auto pb = std::dynamic_pointer_cast<PointBase>(elem);
    if (!pb) return false;
    pb->setXY(x, y);
    return true;
}
