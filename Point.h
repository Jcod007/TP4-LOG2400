#pragma once

#include <tuple>
#include "PointBase.h"

class Point : public PointBase {
public:
    Point(const std::pair<int, int>& xy);

    int getId() const override;
    std::pair<int, int> getXY() const override;
    std::string getTexture() const override;
};
