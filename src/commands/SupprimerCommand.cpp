#include "../../include/commands/SupprimerCommand.h"
#include <iostream>

using namespace std;

void SupprimerCommand::execute(){

    m_backup = m_plan.getGraphElementById(m_id);
    if( m_backup == nullptr)
    {
        cerr<<"Element non trouvé"<<endl;
        return;
    }
        
    m_plan.supprimerGraphElementById(m_id);
}