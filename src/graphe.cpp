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
void graphe::listeIncidence()
{
    // Parcourir tous les noeuds dans EnsembleNode
    for (auto &pairNode : V.getNodes()) // getNodes() renvoie la map des noeuds
    {
        node *n = pairNode.second; // Pointeur vers le noeud actuel

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
        // Créer un vector de paires (id de noeud, degré du noeud)
        vector<pair<string, int>> degres;
        // Remplir le vector avec les nœuds et leurs degrés
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

// Ajout de la méthode parcours dans graphe
void graphe::parcours(node *s)
{
    // Créer une pile pour gérer le parcours
    Pile pile;

    // Marquer tous les nœuds comme non visités
    for (auto &pair : V.getNodes())
    {
        pair.second->setVisited(false); // Remettre à faux la visite pour chaque nœud
    }

    // Empiler le noeud de départ
    pile.empiler(s);

    // Tant que la pile n'est pas vide
    while (!pile.vide())
    {
        // Dépiler un noeud
        node *courant = pile.depiler();

        // Si le noeud n'a pas encore été visité
        if (!courant->getVisited())
        {
            cout << "Visiting node: " << courant->getId() << endl; // Affichage du noeud visité
            courant->setVisited(true);                             // Marquer le noeud comme visité

            // Empiler les voisins non visités
            ArcListe *arcs = courant->getAdjacentNodes();
            while (arcs != nullptr)
            {
                string voisinId = arcs->a->getEndingNode(); // ID du voisin
                node *voisin = V.rechercherNode(voisinId);  // Rechercher le noeud correspondant dans l'ensemble de nœuds                if (!voisin->getVisited())
                {
                    pile.empiler(voisin);
                }
                arcs = arcs->next;
            }
        }
    }
}

// backtracking profondeur garantie pas le chemin le plus court contrairement à backtracking largeur
int graphe::chemin(string o, string d)
{
    node *origine = V.rechercherNode(o);
    node *destination = V.rechercherNode(d);

    if (!origine || !destination)
    {
        cout << "L'un des nœuds (origine ou destination) n'existe pas." << endl;
        return -1;
    }

    // Initialiser les nœuds comme non visités
    for (auto &pair : V.getNodes())
    {
        pair.second->setVisited(false);
    }

    Pile pile;
    pile.empiler(origine);
    origine->setVisited(true);

    // Liste pour stocker les arcs parcourus
    // vector<string> arcsParcourus;

    while (!pile.vide())
    {

        node *courant = pile.sommetPile();

        // Si on a atteint la destination, afficher le chemin et retourner le nombre d'arcs
        if (courant == destination)
        {
            pile.afficherArcPileInversee(this->E);
            return pile.taille() - 1;
            // Afficher le chemin basé sur le vecteur arcsParcourus
            // cout << "Chemin : ";
            // for (const string &arcId : arcsParcourus)
            //{
            //    cout << arcId << " - ";
            //}
            // cout << endl;
            // return arcsParcourus.size(); // Retourner le nombre d'arcs parcourus
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

                // Ajouter l'arc à la liste des arcs parcourus
                string arcId = this->E.rechercherArc(courant->getId(), idVoisin);
                // if (!arcId.empty())
                //{
                //     arcsParcourus.push_back(arcId); // Ajouter l'arc au vecteur
                // }

                voisinTrouve = true;
                break; // On suit ce chemin pour l'instant
            }

            arcs = arcs->next; // Passer au voisin suivant
        }

        // Si aucun voisin non visité n'a été trouvé, faire un backtrack
        if (!voisinTrouve)
        {
            pile.depiler();
        }
    }

    // Si aucun chemin n'a été trouvé
    cout << "Aucun chemin trouvé entre " << o << " et " << d << "." << endl;
    return -1;
}

// Faire file.vide()

int graphe::plusCourtChemin(string o, string d)
{
    // Récupérer les noeuds origine et destination
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

    // Initialiser la pile pour stocker le chemin
    Pile pile;

    // BFS classique
    while (!file.vide())
    {
        node *current = file.defiler();

        // Si on atteint la destination, on reconstruit le chemin
        if (current == destination)
        {
            node *temp = destination;

            // Reconstruire le chemin dans la pile en utilisant les prédecesseurs
            while (temp != nullptr)
            {
                pile.empiler(temp);         // Empiler le noeud
                temp = predecesseurs[temp]; // Remonter vers le prédécesseur
            }

            // Afficher le chemin via la pile
            cout << "Chemin le plus court (en termes d'arcs) : ";
            int cpt = pile.taille() - 1;
            pile.afficherArcPile(E);

            // Retourner le nombre d'arcs
            return cpt;
        }

        // Explorer les voisins du noeud actuel
        ArcListe *adjacents = current->getAdjacentNodes();
        while (adjacents != nullptr)
        {
            node *neighbor = V.rechercherNode(adjacents->a->getEndingNode());
            if (!neighbor->getVisited())
            {
                neighbor->setVisited(true);
                predecesseurs[neighbor] = current; // Enregistrer le prédécesseur
                file.enfiler(neighbor);
            }
            adjacents = adjacents->next;
        }
    }

    // Si on arrive ici, cela signifie qu'il n'y a pas de chemin entre l'origine et la destination
    cout << "Aucun chemin trouvé entre " << o << " et " << d << "." << endl;
    return 0;
}
int graphe::itineraire(string o, string d)
{
    // Trouver les noeuds associés aux arcs par leurs identifiants
    node *startingNode = V.rechercherNode(E.chercherArc(o)->getStartingNode()); // Recherche le noeud de départ par l'ID de l'arc o
    node *endingNode = V.rechercherNode(E.chercherArc(d)->getEndingNode());     // Recherche le noeud de destination par l'ID de l'arc d

    if (startingNode == nullptr || endingNode == nullptr)
    {
        cout << "Un des noeuds n'a pas été trouvé." << endl;
        return 0; // Retourne 0 si l'un des noeuds est introuvable
    }

    // Appeler la fonction pour obtenir le plus court chemin entre les deux noeuds
    int cpt = plusCourtChemin(startingNode->getId(), endingNode->getId());

    // Retourner le nombre d'arcs dans le plus court chemin
    return cpt;
}
