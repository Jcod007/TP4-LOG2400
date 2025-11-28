#include "Texture.h"

Texture::Texture(std::shared_ptr<PointBase> element)
    : m_element(element) {
    m_xy = m_element->getXY();
}

Texture::~Texture() = default;

int Texture::getId() const {
    return m_element->getId();
}

std::pair<int, int> Texture::getXY() const {
    return m_element->getXY();
}

std::string Texture::getTexture() const {
    return m_element->getTexture();
}
