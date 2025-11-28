#include "Texture_F.h"

Texture_F::Texture_F(std::shared_ptr<PointBase> component)
    : Texture(component) {}

std::string Texture_F::getTexture() const {
    return m_element->getTexture() + "#";
}
