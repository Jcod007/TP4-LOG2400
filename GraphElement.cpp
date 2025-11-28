#include "GraphElement.h"

int GraphElement::m_nextId = 0;

GraphElement::GraphElement() {
    m_id = m_nextId;
    m_nextId++;
}

int GraphElement::getId() const {
    return m_id;
}
