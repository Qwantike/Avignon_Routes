#ifndef GRAPHE_H
#define GRAPHE_H

#include "ensembleArc.h"
#include "ensembleNode.h"
#include "tris.h"
#include "pile.h"
#include "file.h"
#include <iomanip>

using namespace std;

class graphe
{
private:
    EnsembleNode V;
    EnsembleArc E;
    int nbNode;
    int nbArc;

public:
    graphe();
    graphe(const string &filePathArcs, const string &filePathNodes);
    ~graphe();
    // on l'utilise pas, on remplie direct dans constructeur graphe -> ensembleNode
    void listeIncidence();
    void affiche();
    void degre(int n);
    void parcours(node *s);
    int chemin(string o, string d);
    int plusCourtChemin(string o, string d);
    int itineraire(string o, string d);
};

#endif