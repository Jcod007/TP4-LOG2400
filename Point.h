#pragma once

#include "PointBase.h"

class Point : public PointBase {
public:
    Point(const std::pair<int, int>& xy);

    int obtenirId() const override;
    std::pair<int, int> obtenirXY() const override;
    std::string obtenirTexture() const override;
};
