#pragma once

#include <tuple>
#include <string>
#include <memory>
#include "PointBase.h"

class Texture : public PointBase {
protected:
    std::shared_ptr<PointBase> element_;

public:
    explicit Texture(std::shared_ptr<PointBase> element);
    virtual ~Texture();

    int getId() const override;
    std::pair<int, int> getXY() const override;
    std::string getTexture() const override;
};
