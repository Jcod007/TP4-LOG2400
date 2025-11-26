#pragma once

#include <tuple>
#include "PointBase.h"

class Point : public PointBase {
public:
    Point(const std::tuple<int, int>& xy);

    int getId() const override;
    std::tuple<int, int> getXY() const override;
    std::string getTexture() const override;
};
