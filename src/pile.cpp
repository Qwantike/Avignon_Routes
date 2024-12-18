#include "pile.h"

// Constructeur
Pile::Pile()
{
    sommet = nullptr;
    nbNoeuds = 0;
}

// Destructeur
Pile::~Pile()
{
    while (!vide())
    {
        depiler(); // Dépile tous les maillons jusqu'à ce que la pile soit vide
    }
}

// Vérifie si la pile est vide
bool Pile::vide() const
{
    return sommet == nullptr; // Si le sommet est null, la pile est vide
}

// Empiler un noeud
void Pile::empiler(node *n)
{
    Maillon *nouveauMaillon = new Maillon(n, sommet, nullptr); // Crée un nouveau maillon pointant vers le sommet actuel
    sommet = nouveauMaillon;
    nbNoeuds++; // Incrémente le nombre de noeuds dans la pile
}

// Dépiler un noeud
node *Pile::depiler()
{
    if (vide())
    {
        cout << "La pile est vide. Impossible de dépiler." << endl;
        return nullptr; // Si la pile est vide, retourne un pointeur nul
    }
    Maillon *maillonDepile = sommet;               // Sauvegarde le sommet
    node *noeudDepile = maillonDepile->getNoeud(); // Récupère le noeud du sommet
    sommet = sommet->getPrecedent();               // Le sommet devient le maillon précédent
    delete maillonDepile;                          // Libère la mémoire allouée au maillon
    nbNoeuds--;                                    // Décrémenter le nombre de noeuds
    return noeudDepile;                            // Retourne le noeud dépilé
}

// Retourne le sommet sans dépiler
node *Pile::sommetPile() const
{
    if (vide())
    {
        cout << "La pile est vide." << endl;
        return nullptr;
    }
    return sommet->getNoeud(); // Retourne le noeud du sommet
}

// Retourne le nombre de noeuds dans la pile
int Pile::taille() const
{
    return nbNoeuds; // Retourne le nombre de noeuds
}

// Affiche les éléments de la pile
void Pile::afficherNodePile() const
{
    if (vide())
    {
        cout << "La pile est vide." << endl;
        return;
    }

    Maillon *temp = sommet;
    cout << "Contenu de la pile : ";
    while (temp != nullptr)
    {
        cout << temp->getNoeud()->getId() << " "; // Affiche l'identifiant du noeud du maillon
        temp = temp->getPrecedent();              // Passe au maillon précédent
    }
    cout << endl;
}

Pile Pile::pileInversee() const
{
    Pile pileTemporaire; // Pile temporaire qui va contenir les éléments inversés
    Maillon *maillonCourant = sommet;

    // On parcourt toute la pile et on empile dans la pile temporaire
    while (maillonCourant != nullptr)
    {
        pileTemporaire.empiler(maillonCourant->getNoeud()); // Empile le noeud courant
        maillonCourant = maillonCourant->getPrecedent();    // Passe au maillon précédent
    }

    return pileTemporaire; // Retourne la pile inversée
}

void Pile::afficherArcPileInversee(EnsembleArc &ensembleArc) const
{
    Pile pileTemporaire = this->pileInversee(); // Obtenez la pile inversée
    if (pileTemporaire.vide())
    {
        cout << "La pile est vide." << endl;
        return;
    }

    node *startingPoint = pileTemporaire.depiler(); // Dépiler le premier élément (bas de la pile)

    while (!pileTemporaire.vide())
    {
        node *endingPoint = pileTemporaire.depiler(); // Dépiler pour obtenir le startingPoint
        string arcId = ensembleArc.rechercherArc(startingPoint->getId(), endingPoint->getId());
        if (!arcId.empty())
        {
            cout << arcId << " - ";
        }
        else
        {
            cout << "[Arc introuvable] - ";
        }

        // Le startingPoint devient le nouvel endingPoint
        startingPoint = endingPoint;
    }
    cout << endl;
}

void Pile::afficherArcPile(EnsembleArc &ensembleArc)
{
    string affichage = "";
    if (this->vide())
    {
        cout << "La pile est vide." << endl;
        return;
    }

    node *startingPoint = this->depiler(); // Dépiler le premier élément (bas de la pile)

    while (!this->vide())
    {
        node *endingPoint = this->depiler(); // Dépiler pour obtenir le startingPoint
        string arcId = ensembleArc.rechercherArc(startingPoint->getId(), endingPoint->getId());
        if (!arcId.empty())
        {
            affichage += arcId;
        }
        else
        {
            affichage += "[Arc introuvable]";
        }
        affichage += " - ";
        // Le startingPoint devient le nouvel endingPoint
        startingPoint = endingPoint;
    }
    if (affichage.length() > 3)
    {
        affichage = affichage.substr(0, affichage.length() - 3);
    }
    cout << affichage << endl;
}
