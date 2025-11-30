#include "ElementGraphique.h"

int ElementGraphique::m_prochainId = 0;

ElementGraphique::ElementGraphique() {
    m_id = m_prochainId;
    m_prochainId++;
}

int ElementGraphique::obtenirId() const {
    return m_id;
}
