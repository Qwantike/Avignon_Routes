#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "arc.h"
#include "listeArc.h"
using namespace std;

class node
{
private:
    string id;
    string x;
    string y;
    string streetCount;
    ArcListe *arcEntrant;
    ArcListe *arcSortant;
    int degre;
    bool visited;

public:
    node(string id, string x, string y, string streetCount);
    void affiche();
    void ajouterArcEntrant(arc *a);
    void ajouterArcSortant(arc *a);
    void ajouterArcListe(arc *a);
    string getId();
    int getDegre();
    float getX();
    float getY();
    bool getVisited();
    void setVisited(bool x);
    ArcListe *getAdjacentNodes() const;
};

#endif