#pragma once

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
    virtual void setXY(int x, int y);
    virtual std::string getTexture() const;
    virtual std::string dessiner() const override;
};
