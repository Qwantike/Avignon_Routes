#ifndef MAILLON_H
#define MAILLON_H

#include "node.h" // Inclut la classe node
#include <iostream>
using namespace std;

class Maillon
{
private:
    node *noeud;        // Pointeur vers le node stocké dans le maillon
    Maillon *precedent; // Pointeur vers le maillon précédent
    Maillon *suivant;

public:
    // Constructeur
    Maillon(node *n, Maillon *prec = nullptr, Maillon *suiv = nullptr);

    // Accesseurs
    node *getNoeud() const;        // Retourne le noeud stocké dans le maillon
    Maillon *getPrecedent() const; // Retourne le pointeur vers le maillon précédent
    Maillon *getSuivant() const;

    // Mutateurs
    void setPrecedent(Maillon *prec); // Définit le pointeur vers le maillon précédent
    void setSuivant(Maillon *suiv);
};

#endif
