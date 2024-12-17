#include "gestionnaireRue.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream>

using namespace std;

string gestionnaireRue::nomRueAvecIndex(const string &name)
{
    int compteur = compteurNoms[name];
    if (compteur == 0)
    {
        compteurNoms[name]++;
        return name;
    }
    else
    {
        compteurNoms[name]++;
        return name + "-" + to_string(compteur);
    }
}
