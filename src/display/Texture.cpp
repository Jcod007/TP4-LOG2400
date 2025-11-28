#include "Texture.h"

Texture::Texture(std::shared_ptr<PointBase> element)
    : element_(element) {
    m_xy = element_->getXY();
}

Texture::~Texture() = default;

int Texture::getId() const {
    return element_->getId();
}

std::pair<int, int> Texture::getXY() const {
    return element_->getXY();
}

std::string Texture::getTexture() const {
    return element_->getTexture();
}
