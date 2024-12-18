#ifndef PILE_H
#define PILE_H

#include "maillon.h"
#include "ensembleArc.h"
#include <iostream>
using namespace std;

class Pile
{
private:
    Maillon *sommet;
    int nbNoeuds;

public:
    Pile();
    ~Pile();
    bool vide() const;
    void empiler(node *n);
    node *depiler();
    node *sommetPile() const;
    int taille() const;
    void afficherNodePile() const;
    Pile pileInversee() const;
    void afficherArcPileInversee(EnsembleArc &ensembleArc) const;
    void afficherArcPile(EnsembleArc &ensembleArc);
};

#endif
