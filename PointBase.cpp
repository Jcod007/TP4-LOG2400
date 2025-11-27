#include "PointBase.h"

int PointBase::getId() const {
    return m_id;
}

std::pair<int, int> PointBase::getXY() const {
    return m_xy;
}

std::string PointBase::getTexture() const {
    return " ";
}

std::string PointBase::dessiner() const
{
    return m_id + ": (" + to_string(m_xy.first) + "," + to_string(m_xy.second) +") texture: "+getTexture(); ;
}

