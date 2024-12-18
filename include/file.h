#include "maillon.h"

using namespace std;

class File
{
private:
    Maillon *tete;
    Maillon *queue;
    int nbElements;

public:
    File();

    void enfiler(node *n);
    node *defiler();
    bool vide() const;
    int taille();
};
