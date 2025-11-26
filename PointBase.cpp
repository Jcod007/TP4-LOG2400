#include "PointBase.h"

int PointBase::getId() const {
    return id_;
}

std::tuple<int, int> PointBase::getXY() const {
    return m_xy;
}

std::string PointBase::getTexture() const {
    return "Aucune";
}
