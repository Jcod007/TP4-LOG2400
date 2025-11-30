#include "Invocateur.h"
#include <iostream>

void Invocateur::executer(shared_ptr<Commande> cmd)
{
    if (cmd)
    {
        cmd->executer();
        pile_annulation_.push_back(cmd);
        // A new command clears the redo stack
        pile_rétablissement_.clear();
    }
}

void Invocateur::annuler()
{
    if (!pile_annulation_.empty())
    {
        shared_ptr<Commande> last_cmd = pile_annulation_.back();
        pile_annulation_.pop_back();
        last_cmd->undo();
        pile_rétablissement_.push_back(last_cmd);
        cout << "Commande annulee." << endl;
    }
    else
    {
        cout << "Rien a annuler." << endl;
    }
}

void Invocateur::rétablir()
{
    if (!pile_rétablissement_.empty())
    {
        shared_ptr<Commande> last_undone_cmd = pile_rétablissement_.back();
        pile_rétablissement_.pop_back();
        last_undone_cmd->executer();
        pile_annulation_.push_back(last_undone_cmd);
        cout << "Commande retablie." << endl;
    }
    else
    {
        cout << "Rien a retablir." << endl;
    }
}
