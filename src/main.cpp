// liste d'incidence (matrice)

#include "rawToJson.h"
#include "graphe.h"
#include <iostream>
using namespace std;
int main()
{
    // init chemin pour toJson
    const string arcInputFilePath = "../data/arcs.csv";     // chemin du fichier CSV d'entrée (arc)
    const string arcOutputFilePath = "../data/arcs.json";   // chemin du fichier JSON de sortie (arc)
    const string nodeInputFilePath = "../data/nodes.csv";   // chemin du fichier CSV d'entrée (node)
    const string nodeOutputFilePath = "../data/nodes.json"; // chemin du fichier JSON de sortie(node)

    // parser les fichiers CSV et le convertir en JSON
    // arcsCsvToJson(arcInputFilePath, arcOutputFilePath);
    // nodesCsvToJson(nodeInputFilePath, nodeOutputFilePath);

    int n;
    cout << "Nombre de noeuds à afficher (trié par degré) ?" << endl;
    cin >> n;
    graphe *G = new graphe(arcOutputFilePath, nodeOutputFilePath);
    cout << "Initialisation du graphe ok" << endl;
    G->degre(n);
    // int cpt = G->chemin("1118550826", "1118550821"); // via 7549202749 Rue Condorcet - Rue Lavoisier
    // cout << "Nombre d'arcs parcourus : " << cpt << endl;
    int cpt = G->plusCourtChemin("1118550826", "1118550821");
    cout << "Nombre d'arcs parcourus : " << cpt << endl;

    return 0;
}
