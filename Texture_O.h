#pragma once

#include "Texture.h"
#include <memory>

class Texture_O : public Texture {
public:
    explicit Texture_O(std::shared_ptr<PointBase> component);

    std::string obtenirTexture() const override;
};

