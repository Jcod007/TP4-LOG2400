#include "UtilitairesGraphique.h"
#include "PointBase.h"
using namespace std;

bool obtenirPositionSiPoint(const std::shared_ptr<ElementGraphique>& elem, std::pair<int,int>& outPos)
{
    auto pb = std::dynamic_pointer_cast<PointBase>(elem);
    if (!pb) return false;
    outPos = pb->obtenirXY();
    return true;
}

bool definirPositionSiPoint(std::shared_ptr<ElementGraphique>& elem, int x, int y)
{
    auto pb = std::dynamic_pointer_cast<PointBase>(elem);
    if (!pb) return false;
    pb->definirXY(x, y);
    return true;
}
