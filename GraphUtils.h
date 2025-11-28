#pragma once

#include <memory>
#include <utility>
#include "GraphElement.h"

// Retourne true et écrit la position dans outPos si l'élément est un PointBase
bool getPositionIfPoint(const std::shared_ptr<GraphElement>& elem, std::pair<int,int>& outPos);

// Retourne true et définit la position si l'élément est un PointBase
bool setPositionIfPoint(const std::shared_ptr<GraphElement>& elem, int x, int y);
