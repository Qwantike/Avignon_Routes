#include "ensembleNode.h"

EnsembleNode::EnsembleNode()
{
    nodes = unordered_map<string, node *>();
}

EnsembleNode::EnsembleNode(const string &path, EnsembleArc E, int &cpt)
{
    // Ouvrir le fichier JSON
    ifstream fichier(path);
    if (!fichier.is_open())
    {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << path << endl;
        return;
    }

    json data;
    fichier >> data;
    fichier.close();

    // Ajouter les arcs correspondants
    unordered_map<string, vector<arc *>> arcIndex;
    for (auto &pair : E.getArcs())
    {
        arc *a = pair.second;
        arcIndex[a->getStartingNode()].push_back(a);
        arcIndex[a->getEndingNode()].push_back(a);
    }

    // Parcourir les noeuds dans le JSON
    for (const auto &item : data)
    {
        string id = item.at("id").get<string>();
        string x = item.at("x").get<string>();
        string y = item.at("y").get<string>();
        string streetCount = item.at("street_count").get<string>();

        // Créer le noeud
        node *n = new node(id, x, y, streetCount);

        // Complexité nbArc + nbNode

        for (arc *a : arcIndex[n->getId()])
        {
            n->ajouterArcListe(a);
        }

        // Complexité nbArc x nbNode
        /* for (auto &pair : E.getArcs()) // Parcourir tous les arcs
        {
            if (pair.second->getStartingNode() == n->getId() || pair.second->getEndingNode() == n->getId())
            {
                arc *a = pair.second;
                n->ajouterArcListe(a);
            }
        } */
        // Ajouter le noeud à la map
        nodes[id] = n;
        cpt++;
    }
}

EnsembleNode::~EnsembleNode()
{
    for (auto &pair : nodes)
    {
        delete pair.second;
    }
    nodes.clear();
}

void EnsembleNode::ajouterNode(node *n)
{
    if (nodes.find(n->getId()) == nodes.end()) // si pas trouvé, .find() renvoie le même pointeur que nodes.end() qui correspond à "un élément après la map" fictifs
    {
        nodes[n->getId()] = n;
    }
    else
    {
        cerr << "node déjà présent : " << n->getId() << endl;
    }
}

// Rechercher un node par identifiant
node *EnsembleNode::rechercherNode(const string &id)
{
    auto node = nodes.find(id);
    if (node != nodes.end())
    {
        return node->second;
    }
    return nullptr;
}

// Afficher le contenu de l'ensemble
void EnsembleNode::afficherContenu()
{
    for (const auto &[id, n] : nodes)
    {
        cout << "ID : " << id << " -> ";
        n->affiche();
    }
}

// Supprimer un nœud par identifiant
void EnsembleNode::supprimerNode(const string &id)
{
    nodes.erase(id);
}

// Constructeur par recopie
EnsembleNode::EnsembleNode(const EnsembleNode &other)
{
    for (const auto &pair : other.nodes)
    {
        // Copie profonde : créer une nouvelle instance de chaque noeud
        nodes[pair.first] = new node(*(pair.second));
    }
}

// Opérateur d'assignation
EnsembleNode &EnsembleNode::operator=(const EnsembleNode &other)
{
    if (this != &other) // Éviter l'auto-affectation
    {
        // Libérer les ressources existantes
        for (auto &pair : nodes)
        {
            delete pair.second;
        }
        nodes.clear();

        // Copier les noeuds de l'autre instance (copie profonde)
        for (const auto &pair : other.nodes)
        {
            nodes[pair.first] = new node(*(pair.second));
        }
    }
    return *this;
}

// Méthode pour obtenir les noeuds
const std::unordered_map<std::string, node *> &EnsembleNode::getNodes() const
{
    return nodes; // Retourner une référence constante pour éviter une copie
}

int EnsembleNode::getSizeMap()
{
    return nodes.size();
}