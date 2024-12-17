#include "node.h"

node::node(string id, string x, string y, string streetCount)
{
    this->id = id;
    this->x = x;
    this->y = y;
    this->streetCount = streetCount;
    this->arcEntrant = nullptr;
    this->arcSortant = nullptr;
    this->degre = 0;
    this->visited = false;
}

void node::affiche()
{
    cout << "id du noeud : " << this->id;
    cout << "Longitude : " << this->x;
    cout << "Latitude : " << this->y;
    cout << "Degré : " << this->degre;
}

// Méthode pour ajouter un arc sortant
void node::ajouterArcSortant(arc *a)
{
    ArcListe *tmp = new ArcListe(a);
    if (arcSortant == nullptr) // Si la liste est vide, on affecte directement la tête
    {
        arcSortant = tmp;
    }
    else // Sinon, on ajoute à la tête de la liste
    {
        tmp->next = arcSortant;
        arcSortant = tmp;
    }
    this->degre++;
}

// Méthode pour ajouter un arc entrant
void node::ajouterArcEntrant(arc *a)
{
    ArcListe *tmp = new ArcListe(a);
    if (arcEntrant == nullptr) // Si la liste est vide, on affecte directement la tête
    {
        arcEntrant = tmp;
    }
    else // Sinon, on ajoute à la tête de la liste
    {
        tmp->next = arcEntrant;
        arcEntrant = tmp;
    }
    this->degre++;
}

// Pas bon car sens double sens = présent 2 fois dans la liste déjà
/* void node::ajouterArcListe(arc *a)
{
    string s = a->getStartingNode();
    string e = a->getEndingNode();
    if (a != nullptr)
    {
        if (a->getOneWay()) // Si la route est à sens unique
        {
            if (!a->getReversed()) // Sens normal : de départ à arrivée
            {
                if (x == this->id)
                {
                    this->ajouterArcSortant(a);
                }
                else if (e == this->id)
                {
                    this->ajouterArcEntrant(a);
                }
                else
                {
                    cout << "Aucun lien trouvé avec ce noeud. Erreur ?" << endl;
                }
            }

            else
            {
                if (e == this->id)
                    this->ajouterArcSortant(a); // Arc sortant
                else if (s == this->id)
                    this->ajouterArcEntrant(a); // Arc entrant
            }
        }
        else // Route bidirectionnelle
        {
            // Cas classique
            if (s == this->id || e == this->id)
            {
                this->ajouterArcSortant(a); // Arc sortant
                this->ajouterArcEntrant(a); // Arc entrant
            }
        }
    }
} */

void node::ajouterArcListe(arc *a)
{
    string s = a->getStartingNode();
    string e = a->getEndingNode();
    if (a != nullptr)
    {
        if (!a->getReversed()) // Sens normal : de départ à arrivée
        {
            if (s == this->id)
            {
                this->ajouterArcSortant(a);
            }
            else if (e == this->id)
            {
                this->ajouterArcEntrant(a);
            }
            else
            {
                cout << "Aucun lien trouvé avec ce noeud. Erreur ?" << endl;
            }
        }
        else
        {
            if (e == this->id)
                this->ajouterArcSortant(a); // Arc sortant
            else if (s == this->id)
                this->ajouterArcEntrant(a); // Arc entrant
        }
    }
}

/////////////
// getters //
/////////////

string node::getId()
{
    return this->id;
}

int node::getDegre()
{
    return this->degre;
}

float node::getX()
{
    return stof(this->x);
}

float node::getY()
{
    return stof(this->y);
}

bool node::getVisited()
{
    return this->visited;
}
void node::setVisited(bool x)
{
    this->visited = x;
}

ArcListe *node::getAdjacentNodes() const
{
    return this->arcSortant;
}