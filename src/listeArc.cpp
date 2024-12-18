#include "listeArc.h"

// Constructeur
ArcListe::ArcListe(arc *a)
{
    this->a = a;
    this->next = nullptr;
}

void ArcListe::afficher()
{
    a->affiche();
}
