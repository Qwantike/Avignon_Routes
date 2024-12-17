#ifndef ENSEMBLE_ARC_H
#define ENSEMBLE_ARC_H

#include "gestionnaireRue.h"
#include "arc.h"
#include <unordered_map>
using namespace std;

class EnsembleArc
{
private:
    gestionnaireRue gr; // dico pour gerer les doublons des noms
    unordered_map<string, arc *> arcs;

public:
    EnsembleArc(const string &path, int &cpt);
    EnsembleArc();
    EnsembleArc(const EnsembleArc &other);
    EnsembleArc &operator=(const EnsembleArc &other);
    ~EnsembleArc();
    void ajouterArc(const string &id, const string &startingNode, const string &endingNode, const string &oneWay, const string &reversed, const string &lane, const string &highway, const string &length, const string &maxSpeed, const string &speedKph, const string &travelTime);
    arc *chercherArc(const string &nom);
    string rechercherArc(string o, string d);
    void supprimerArc(const string &nom);
    const unordered_map<string, arc *> &getArcs() const;
    void test();
};

#endif
