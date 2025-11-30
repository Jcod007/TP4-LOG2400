#pragma once

class Commande
{
    public:
        virtual void executer() = 0;
        virtual void annuler() {}
        virtual ~Commande() = default;
};