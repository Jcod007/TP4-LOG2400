#include "Texture.h"
using namespace std;

Texture::Texture(std::shared_ptr<PointBase> element)
    : m_element(element) {
}

Texture::~Texture() = default;

int Texture::obtenirId() const {
    return m_element->obtenirId();
}

std::pair<int, int> Texture::obtenirXY() const {
    return m_element->obtenirXY();
}

std::string Texture::obtenirTexture() const {
    return m_element->obtenirTexture();
}

void Texture::definirXY(int x, int y){
    m_element->definirXY(x, y); 
}
