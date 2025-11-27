#pragma once

#include <tuple>
#include <string>
#include "GraphElement.h"

using namespace std;

class PointBase : public GraphElement {
protected:
    std::pair<int, int> m_xy;

public:
    virtual ~PointBase() = default;

    int getId() const override;
    virtual std::pair<int, int> getXY() const;
    virtual std::string getTexture() const;
    virtual std::string dessiner() const override;
};
