#include "Texture_O.h"

Texture_O::Texture_O(std::shared_ptr<PointBase> component)
    : Texture(component) {}

std::string Texture_O::getTexture() const {
    return "O";
}
