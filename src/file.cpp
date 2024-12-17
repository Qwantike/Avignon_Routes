#include "file.h"

File::File()
{
    queue = nullptr;
    tete = nullptr;
    nbElements = 0;
}

void File::enfiler(node *n)
{
    Maillon *nouveau = new Maillon(n, nullptr, nullptr); // Utilise seulement `suivant`
    if (queue == nullptr)
    {
        // File vide : tête et queue pointent vers le même maillon
        tete = queue = nouveau;
    }
    else
    {
        queue->setSuivant(nouveau); // Ajoute après la queue
        queue = nouveau;            // Met à jour la queue
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
