#include "listeArc.h"

// Constructeur
ArcListe::ArcListe(arc *a)
{
    this->a = a;
    this->next = nullptr;
}

// Méthode pour afficher l'arc de cette cellule
void ArcListe::afficher()
{
    a->affiche();
}
