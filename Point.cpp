#include "Point.h"

Point::Point(const std::pair<int, int>& xy) {
    m_xy = xy;
}

int Point::obtenirId() const {
    return m_id;
}

std::pair<int, int> Point::obtenirXY() const {
    return m_xy;
}

std::string Point::obtenirTexture() const {
    return "";
}
