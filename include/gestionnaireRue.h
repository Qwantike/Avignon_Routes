#ifndef GESTIONNAIRE_RUE_H
#define GESTIONNAIRE_RUE_H
#include <string>
#include <map>

using namespace std;

class gestionnaireRue
{
private:
    // dico nom de rue et compteur (nombre de rue déjà implémenté)
    map<string, int> compteurNoms;

public:
    string nomRueAvecIndex(const string &name);
};

#endif