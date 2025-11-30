#pragma once

#include <string>
#include "ElementGraphique.h"


class PointBase : public ElementGraphique {
protected:
    std::pair<int, int> m_xy;

public:
    virtual ~PointBase() = default;

    int obtenirId() const override;
    virtual std::pair<int, int> obtenirXY() const;
    virtual void definirXY(int x, int y);
    virtual std::string obtenirTexture() const;
    virtual std::string dessiner() const override;
};
