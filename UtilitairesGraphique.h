#pragma once

#include <memory>
#include <utility>
#include "ElementGraphique.h"

// Retourne true et écrit la position dans outPos si l'élément est un PointBase
bool obtenirPositionSiPoint(const std::shared_ptr<ElementGraphique>& elem, std::pair<int,int>& outPos);

// Retourne true et définit la position si l'élément est un PointBase
bool definirPositionSiPoint(std::shared_ptr<ElementGraphique>& elem, int x, int y);
