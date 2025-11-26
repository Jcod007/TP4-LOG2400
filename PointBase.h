#pragma once

#include <tuple>
#include <string>
#include "GraphElement.h"

class PointBase : public GraphElement {
protected:
    std::tuple<int, int> m_xy;

public:
    virtual ~PointBase() = default;

    int getId() const override;
    virtual std::tuple<int, int> getXY() const;
    virtual std::string getTexture() const;
};
