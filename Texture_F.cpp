#include "Texture_F.h"
using namespace std;

Texture_F::Texture_F(std::shared_ptr<PointBase> component)
    : Texture(component) {}

std::string Texture_F::obtenirTexture() const {
    return m_element->obtenirTexture() + "#";
}
