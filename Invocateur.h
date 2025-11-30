#pragma once

#include "Commande.h"
#include <memory>
#include <vector>


class Invocateur
{
    public:
        void executer(std::shared_ptr<Commande> cmd);
        void annuler();
        void retablir();
        
    private:
        std::vector<std::shared_ptr<Commande>> m_pileAnnulation;
        std::vector<std::shared_ptr<Commande>> m_pileRetablissement;
};