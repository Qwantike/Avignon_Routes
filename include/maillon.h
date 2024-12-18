#ifndef MAILLON_H
#define MAILLON_H

#include "node.h"
#include <iostream>
using namespace std;

class Maillon
{
private:
    node *noeud;
    Maillon *precedent;
    Maillon *suivant;

public:
    Maillon(node *n, Maillon *prec = nullptr, Maillon *suiv = nullptr);
    ~Maillon();
    node *getNoeud() const;
    Maillon *getPrecedent() const;
    Maillon *getSuivant() const;
    void setPrecedent(Maillon *prec);
    void setSuivant(Maillon *suiv);
};

#endif
