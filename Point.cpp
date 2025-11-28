#include "Point.h"

Point::Point(const std::pair<int, int>& xy) {
    m_xy = xy;
}

int Point::getId() const {
    return m_id;
}

std::pair<int, int> Point::getXY() const {
    return m_xy;
}

std::string Point::getTexture() const {
    return "";
}
