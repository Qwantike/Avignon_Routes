#include "maillon.h"

Maillon::Maillon(node *n, Maillon *prec, Maillon *suiv)
{
    noeud = n;
    precedent = prec;
    suivant = suiv;
}

Maillon::~Maillon()
{
    noeud = nullptr;
    precedent = nullptr;
    suivant = nullptr;
}

node *Maillon::getNoeud() const
{
    return noeud;
}

Maillon *Maillon::getPrecedent() const
{
    return precedent;
}

Maillon *Maillon::getSuivant() const
{
    return suivant;
}

void Maillon::setPrecedent(Maillon *prec)
{
    precedent = prec;
}

void Maillon::setSuivant(Maillon *suiv)
{
    suivant = suiv;
}
