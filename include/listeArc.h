#ifndef LISTE_ARC_H
#define LISTE_ARC_H
#include "arc.h"

using namespace std;

class ArcListe
{
public:
    arc *a;
    ArcListe *next;

public:
    ArcListe(arc *a);
    void afficher();
};

#endif