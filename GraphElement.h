#pragma once

class GraphElement {
protected:
    int id_;
    static int nextId_;

public:
    GraphElement();
    virtual ~GraphElement() = default;

    virtual int getId() const;
};
