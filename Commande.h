#pragma once

class Commande
{
    public:
        virtual void executer() const = 0;
        virtual ~Commande() = default;
};