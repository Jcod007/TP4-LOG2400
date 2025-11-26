#include "GraphElement.h"

int GraphElement::nextId_ = 0;

GraphElement::GraphElement() {
    id_ = nextId_;
    nextId_++;
}

int GraphElement::getId() const {
    return id_;
}
