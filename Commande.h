#pragma once

class Commande
{
    public:
        virtual void executer() = 0;
        virtual void annuler() {}
        virtual bool estAnnulable() const { return true; }
        virtual ~Commande() = default;

};