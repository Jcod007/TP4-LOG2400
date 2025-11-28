#pragma once

class Commande
{
    public:
        virtual void execute() = 0;
        virtual void undo() = 0;
        virtual ~Commande() = default;
};