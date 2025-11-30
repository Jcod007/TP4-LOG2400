#include "PointBase.h"

int PointBase::obtenirId() const {
    return m_id;
}

std::pair<int, int> PointBase::obtenirXY() const {
    return m_xy;
}

void PointBase::definirXY(int x, int y) {
    m_xy = {x, y};
}

std::string PointBase::obtenirTexture() const {
    return "\"\"";
}

std::string PointBase::dessiner() const {
    string texture = obtenirTexture();
    string textureDisplay = texture.empty() ? "''" : texture;
    return to_string(obtenirId())+": ("+to_string(obtenirXY().first)+", "+to_string(obtenirXY().second)+") texture: "+textureDisplay;
}
