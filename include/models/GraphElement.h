#pragma once
#include <string>

using namespace std;

class GraphElement {
protected:
    int m_id;
    static int m_nextId;

public:
    GraphElement();
    virtual ~GraphElement() = default;

    virtual int getId() const;
    virtual string dessiner() const = 0;
};
