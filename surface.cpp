#include "Surface.h"
#include "ConstructeurSurface.h"
#include "NuagePoints.h"
#include "PointBase.h"

using namespace std;

Surface::Surface(shared_ptr<NuagePoints> pointCloud)
    : ElementGraphique(), m_nuagePoints(move(pointCloud))
{
}

void Surface::definirConstructeurSurface(shared_ptr<ConstructeurSurface> builder)
{
    m_constructeurStrategie = move(builder);
}

void Surface::construire()
{
    if (!m_constructeurStrategie || !m_nuagePoints) {
        // si il n'y a pas de nuage de point ou de stratégie, on ne fait rien
        return;
    }

    // La stratégie fait le taf
    m_constructeurStrategie->construireSurface(*this, *m_nuagePoints);
}

const vector<shared_ptr<PointBase>>& Surface::obtenirPoints() const
{
    return m_points;
}

void Surface::viderPoints()
{
    m_points.clear();
}

void Surface::ajouterPoint(const shared_ptr<PointBase>& point)
{
    m_points.push_back(point);
}

std::shared_ptr<NuagePoints> Surface::obtenirNuage() const
{
    return m_nuagePoints;
}
