#include "Invocateur.h"
#include <iostream>
using namespace std;

void Invocateur::executer(shared_ptr<Commande> cmd)
{
    if (cmd)
    {
        cmd->executer();
        // Only add to undo stack if the command is undoable
        if (cmd->estAnnulable())
        {
            m_pileAnnulation.push_back(cmd);
            // A new command clears the redo stack
            m_pileRetablissement.clear();
        }
    }
}

void Invocateur::annuler()
{
    if (!m_pileAnnulation.empty())
    {
        shared_ptr<Commande> last_cmd = m_pileAnnulation.back();
        m_pileAnnulation.pop_back();
        last_cmd->annuler();
        m_pileRetablissement.push_back(last_cmd);
        cout << "Commande annulee." << endl;
    }
    else
    {
        cout << "Rien a annuler." << endl;
    }
}

void Invocateur::retablir()
{
    if (!m_pileRetablissement.empty())
    {
        shared_ptr<Commande> last_undone_cmd = m_pileRetablissement.back();
        m_pileRetablissement.pop_back();
        last_undone_cmd->executer();
        m_pileAnnulation.push_back(last_undone_cmd);
        cout << "Commande retablie." << endl;
    }
    else
    {
        cout << "Rien a retablir." << endl;
    }
}
