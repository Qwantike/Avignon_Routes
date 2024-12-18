#ifndef ENSEMBLE_NODE_H
#define ENSEMBLE_NODE_H
#include "ensembleArc.h"
#include "node.h"
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

using namespace std;

class EnsembleNode
{
private:
    unordered_map<string, node *> nodes;

public:
    // Constructeur defaut
    EnsembleNode();
    // Constructeur vrai
    EnsembleNode(const string &path, EnsembleArc E, int &cpt);
    // Constructeur recopie
    EnsembleNode(const EnsembleNode &other);

    ~EnsembleNode();

    void ajouterNode(node *n);
    node *rechercherNode(const string &id);
    void afficherContenu();
    void supprimerNode(const string &id);
    int getSizeMap();
    const unordered_map<std::string, node *> &getNodes() const;
    EnsembleNode &operator=(const EnsembleNode &other);
};

#endif