#pragma once

#include "Commande.h"
#include <memory>
#include <vector>

using namespace std;

class Invocateur
{
    public:
        void executer(shared_ptr<Commande> cmd);
        void annuler();
        void retablir();
        
    private:
        vector<shared_ptr<Commande>> pile_annulation_;
        vector<shared_ptr<Commande>> pile_retablissement_;
};