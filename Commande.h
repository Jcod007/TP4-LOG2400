#pragma once

class Commande
{
    public:
        virtual void executer() = 0;
        virtual void undo() {}
        virtual ~Commande() = default;
};