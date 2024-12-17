#include "maillon.h"

using namespace std;

class File
{
private:
    Maillon *tete;  // Début de la file
    Maillon *queue; // Fin de la file
    int nbElements; // Nombre d'éléments dans la file

public:
    File();

    void enfiler(node *n);
    node *defiler();
    bool vide() const;
    int taille();
};
