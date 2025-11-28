#include "AffichageListe.h"
#include <iostream>

using namespace std;

void AffichageListe::afficher(Plan& plan) const
{

    cout << "Liste: "<<endl; 
    for(const auto& element : plan.getGraphElements())
        {
            cout<<element->dessiner()<<endl;
        }
}