#pragma once

#include <tuple>
#include <string>
#include <memory>
#include "PointBase.h"

class Texture : public PointBase {
protected:
    std::shared_ptr<PointBase> m_element;

public:
    explicit Texture(std::shared_ptr<PointBase> element);
    virtual ~Texture();

    int obtenirId() const override;
    std::pair<int, int> obtenirXY() const override;
    std::string obtenirTexture() const override;
    void definirXY(int x, int y) override;
};
