#include "PointBase.h"

int PointBase::getId() const {
    return m_id;
}

std::pair<int, int> PointBase::getXY() const {
    return m_xy;
}

void PointBase::setXY(int x, int y) {
    m_xy = {x, y};
}

std::string PointBase::getTexture() const {
    return "\"\"";
}

std::string PointBase::dessiner() const {
    return to_string(getId())+": ("+to_string(getXY().first)+", "+to_string(getXY().second)+") texture: "+getTexture();
}
