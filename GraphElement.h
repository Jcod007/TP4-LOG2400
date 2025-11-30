#pragma once
#include <string>
#include <memory>
#include <vector>

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
    virtual void addChild(shared_ptr<GraphElement> child) {}
    virtual void addChildren(const vector<shared_ptr<GraphElement>>& children) {}
};
