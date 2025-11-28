#pragma once

#include "Texture.h"
#include <memory>

class Texture_F : public Texture {
public:
    explicit Texture_F(std::shared_ptr<PointBase> component);

    std::string getTexture() const override;
};
