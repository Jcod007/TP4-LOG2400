#include "Point.h"

Point::Point(const std::tuple<int, int>& xy) {
    xy_ = xy;
}

int Point::getId() const {
    return id_;
}

std::tuple<int, int> Point::getXY() const {
    return xy_;
}

std::string Point::getTexture() const {
    return "Aucune";
}
