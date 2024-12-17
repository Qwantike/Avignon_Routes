#ifndef PILE_H
#define PILE_H

#include "maillon.h"
#include "ensembleArc.h"
#include <iostream>
using namespace std;

class Pile
{
private:
    Maillon *sommet; // Pointeur vers le sommet de la pile
    int nbNoeuds;    // Nombre de noeuds dans la pile

public:
    Pile();                   // Constructeur
    ~Pile();                  // Destructeur
    bool vide() const;        // Vérifie si la pile est vide
    void empiler(node *n);    // Empiler un noeud
    node *depiler();          // Dépiler un noeud
    node *sommetPile() const; // Retourne le sommet sans dépiler
    int taille() const;       // Retourne le nombre de noeuds dans la pile
    void afficherNodePile() const;
    Pile pileInversee() const;
    void afficherArcPileInversee(EnsembleArc &ensembleArc) const; // Afficher les éléments de la pile
    void afficherArcPile(EnsembleArc &ensembleArc);               // Afficher les éléments de la pile
};

#endif
