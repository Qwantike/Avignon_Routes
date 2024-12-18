#include "file.h"

File::File()
{
    queue = nullptr;
    tete = nullptr;
    nbElements = 0;
}

void File::enfiler(node *n)
{
    Maillon *nouveau = new Maillon(n, nullptr, nullptr);
    if (queue == nullptr)
    {
        tete = queue = nouveau;
    }
    else
    {
        queue->setSuivant(nouveau);
        queue = nouveau;
    }
    nbElements++;
}

node *File::defiler()
{
    if (tete == nullptr)
        return nullptr;

    Maillon *temp = tete;
    node *noeud = temp->getNoeud();
    tete = tete->getSuivant(); // Passe au suivant
    if (tete == nullptr)
        queue = nullptr; // File vide
    delete temp;
    nbElements--;
    return noeud;
}

bool File::vide() const
{
    return tete == nullptr;
}

int File::taille()
{
    return this->nbElements;
}
