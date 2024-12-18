#include "graphe.h"

using namespace std;

graphe::graphe(const string &filePathArcs, const string &filePathNodes)
{
    this->nbArc = 0;
    this->nbNode = 0;
    this->E = EnsembleArc(filePathArcs, this->nbArc);
    this->V = EnsembleNode(filePathNodes, this->E, this->nbNode);
}

graphe::graphe()
{
    this->E;
    this->V;
    this->nbArc = 0;
    this->nbNode = 0;
}

// pas utilisé car on remplie direct dans le constructeur de ensembleNode
// fonction pas terrible
void graphe::listeIncidence()
{
    // Pour chaque noeud on check tous les arcs
    for (auto &pairNode : V.getNodes())
    {
        node *n = pairNode.second;

        // Ajouter les arcs correspondants
        for (const auto &pairArc : E.getArcs()) // Parcourir tous les arcs
        {
            arc *a = pairArc.second; // Pointeur vers l'arc actuel
            n->ajouterArcListe(a);   // Ajouter l'arc au noeud
        }
    }
}

void graphe::degre(int n)
{

    if (n > 0 && n <= this->V.getSizeMap())
    {
        // on créer un vector de paires (id de noeud, degré du noeud)
        vector<pair<string, int>> degres;
        // on remplit le vector avec les nœuds et leurs degrés
        for (const auto &pair : this->V.getNodes())
        {
            node *n = pair.second;
            degres.push_back({n->getId(), n->getDegre()});
        }

        // fonction tri rapide avec pivot aléatoire
        triRapide(degres, 0, degres.size() - 1);

        // Afficher les n premiers noeuds par degré
        cout << "|| i || id       || degré || x      || y      ||" << endl;
        cout << "------------------------------------------------" << endl;

        for (int i = 0; i < n; i++)
        {
            string id = degres[i].first;
            int degre = degres[i].second;
            float x = 0.0;
            float y = 0.0;
            node *noeud = this->V.rechercherNode(id);

            x = noeud->getX();
            y = noeud->getY();

            cout << "|| " << setw(5) << i + 1 << " || " << setw(10) << id
                 << " || " << setw(10) << degre
                 << " || " << setw(10) << x
                 << " || " << setw(10) << y << " ||" << endl;
        }
    }
    else
    {
        cout << "Le nombre n est hors de portée." << endl;
    }
}

void graphe::parcours(node *s)
{
    Pile pile;

    // dans le doute on marque tout comme non visité
    for (auto &pair : V.getNodes())
    {
        pair.second->setVisited(false);
    }
    // Empiler premier node
    pile.empiler(s);

    while (!pile.vide())
    {
        // on dépile
        node *courant = pile.depiler();

        if (!courant->getVisited())
        {
            courant->setVisited(true);

            // Empiler les voisins non visités
            ArcListe *arcs = courant->getAdjacentNodes();
            while (arcs != nullptr)
            {
                string voisinId = arcs->a->getEndingNode();
                node *voisin = V.rechercherNode(voisinId);
                {
                    pile.empiler(voisin);
                }
                arcs = arcs->next;
            }
        }
    }
}

// backtracking profondeur
int graphe::chemin(string o, string d)
{
    node *origine = V.rechercherNode(o);
    node *destination = V.rechercherNode(d);

    if (!origine || !destination)
    {
        cout << "L'un des nœuds (origine ou destination) n'existe pas." << endl;
        return -1;
    }

    // remettre les nœuds comme non visités au cas ou
    for (auto &pair : V.getNodes())
    {
        pair.second->setVisited(false);
    }

    Pile pile;
    pile.empiler(origine);
    origine->setVisited(true);

    while (!pile.vide())
    {

        node *courant = pile.sommetPile();

        // Si on a atteint la destination, afficher le chemin et retourner le nombre d'arcs
        if (courant == destination)
        {
            pile.afficherArcPileInversee(this->E);
            return pile.taille() - 1;
        }

        ArcListe *arcs = courant->getAdjacentNodes();
        bool voisinTrouve = false;

        while (arcs != nullptr)
        {
            arc *arcCourant = arcs->a;
            string idVoisin = arcCourant->getEndingNode();
            node *voisin = V.rechercherNode(idVoisin);

            if (voisin && !voisin->getVisited())
            {
                // Empiler le voisin et le marquer comme visité
                pile.empiler(voisin);
                voisin->setVisited(true);

                // Ajouter à la liste des arcs parcourus
                string arcId = this->E.rechercherArc(courant->getId(), idVoisin);

                voisinTrouve = true;
                break; // On suit ce chemin pour l'instant
            }
            // on passer au voisin suivant
            arcs = arcs->next;
        }

        // backtracking
        if (!voisinTrouve)
        {
            pile.depiler();
        }
    }

    // Si aucun chemin n'a été trouvé
    cout << "Aucun chemin trouvé entre " << o << " et " << d << "." << endl;
    return -1;
}

// parcours en largeur
int graphe::plusCourtChemin(string o, string d)
{
    // noeuds origine et destination
    node *origine = V.rechercherNode(o);
    node *destination = V.rechercherNode(d);

    if (origine == nullptr || destination == nullptr)
    {
        cout << "Erreur : Noeud d'origine ou de destination introuvable." << endl;
        return 0;
    }

    // Initialiser la file pour le BFS

    File file;
    origine->setVisited(true);
    file.enfiler(origine);

    // Map pour suivre les prédecesseurs
    unordered_map<node *, node *> predecesseurs;

    // pile pour chemin
    Pile pile;

    // parcours largeur
    while (!file.vide())
    {
        node *current = file.defiler();

        // si destination atteinte
        if (current == destination)
        {
            node *temp = destination;

            // Reconstruire le chemin en utilisant les prédecesseurs
            while (temp != nullptr)
            {
                pile.empiler(temp);
                temp = predecesseurs[temp]; // aller au truc précédent
            }
            // affichage via pile
            cout << "Chemin le plus court (en termes d'arcs) : ";
            int cpt = pile.taille() - 1;
            pile.afficherArcPile(E);
            return cpt;
        }

        // explorer les voisins du noeud actuel
        ArcListe *adjacents = current->getAdjacentNodes();
        while (adjacents != nullptr)
        {
            node *neighbor = V.rechercherNode(adjacents->a->getEndingNode());
            if (neighbor == nullptr)
            {
                cout << "Erreur : Le voisin est nul." << endl;
                break; // Passer à l'itération suivante, arrive si on fait degré puis ça
            }

            if (!neighbor->getVisited())
            {
                neighbor->setVisited(true);
                predecesseurs[neighbor] = current;

                file.enfiler(neighbor);
            }
            adjacents = adjacents->next;
        }
    }
    cout << "Aucun chemin trouvé entre " << o << " et " << d << "." << endl;
    return 0;
}

int graphe::itineraire(string o, string d)
{
    node *startingNode = V.rechercherNode(E.chercherArc(o)->getStartingNode()); // Recherche le noeud de départ par l'ID de l'arc o
    node *endingNode = V.rechercherNode(E.chercherArc(d)->getEndingNode());     // Recherche le noeud de destination par l'ID de l'arc d

    if (startingNode == nullptr || endingNode == nullptr)
    {
        cout << "Un des noeuds n'a pas été trouvé." << endl;
        return 0;
    }

    int cpt = plusCourtChemin(startingNode->getId(), endingNode->getId());

    return cpt;
}
