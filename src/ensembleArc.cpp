#include "ensembleArc.h"
#include <map>
#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;
using namespace std;

EnsembleArc::EnsembleArc()
{
    gr = gestionnaireRue();
    arcs = unordered_map<string, arc *>();
}

EnsembleArc::EnsembleArc(const string &path, int &cpt)
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

    for (const auto &item : data)
    {
        string id = gr.nomRueAvecIndex(item.at("name").get<string>());
        // string id = item.at("name").get<string>();
        string startingNode = item.at("StartingNode").get<string>();
        string endingNode = item.at("EndingNode").get<string>();
        string oneWay = item.value("oneway", "false");
        string reversed = item.value("reversed", "false");
        string lane = item.value("lane", "1");
        string highway = item.value("highway", "");
        string length = item.value("length", "0");
        string maxSpeed = item.value("maxSpeed", "0");
        string speedKph = item.value("speed_kph", "0");
        string travelTime = item.value("travel_time", "0");
        // this->ajouterArc(id, startingNode, endingNode, oneWay, reversed, lane, highway, length, maxSpeed, speedKph, travelTime);
        arc *a = new arc(id, startingNode, endingNode, oneWay, reversed, lane, highway, length, maxSpeed, speedKph, travelTime);
        this->arcs[id] = a;
        cpt++;
    }
    // Fermer le fichier
    fichier.close();
}

EnsembleArc::~EnsembleArc()
{
    for (auto &pair : arcs)
    {
        delete pair.second;
    }
    arcs.clear();
}

// Méthode pour ajouter un arc
void EnsembleArc::ajouterArc(const string &id, const string &startingNode, const string &endingNode, const string &oneWay, const string &reversed, const string &lane, const string &highway, const string &length, const string &maxSpeed, const string &speedKph, const string &travelTime)
{
    string idUnique = gr.nomRueAvecIndex(id);
    arc *a = new arc(idUnique, startingNode, endingNode, oneWay, reversed, lane, highway, length, maxSpeed, speedKph, travelTime);
    arcs[idUnique] = a;
}

// Méthode pour obtenir un arc par son id
arc *EnsembleArc::chercherArc(const string &id)
{
    if (arcs.find(id) != arcs.end())
    {
        return arcs[id];
    }
    return nullptr;
}

// Méthode pour supprimer un arc par son nom
void EnsembleArc::supprimerArc(const string &nom)
{
    if (arcs.find(nom) != arcs.end())
    {
        delete arcs[nom];
        arcs.erase(nom);
    }
}

const unordered_map<string, arc *> &EnsembleArc::getArcs() const
{
    return arcs;
}

void EnsembleArc::test()
{
    for (const auto &pair : arcs)
    {
        // Affiche l'ID de chaque arc
        cout << "Arc ID : " << pair.first << endl;
        cout << "Vérification ID : " << pair.second->getId() << endl;
    }
    cout << "TEST FINI" << endl;
}
// Constructeur de copie (copie profonde des arcs)
EnsembleArc::EnsembleArc(const EnsembleArc &other)
{
    this->gr = other.gr; // Copie de gr (si nécessaire)

    // Copie profonde de la map arcs
    for (const auto &pair : other.arcs)
    {
        this->arcs[pair.first] = new arc(*pair.second); // Copie de chaque arc
    }
}

// Opérateur d'affectation
EnsembleArc &EnsembleArc::operator=(const EnsembleArc &other)
{
    if (this != &other)
    { // éviter l'auto-affectation
        // Libérer la mémoire existante
        for (auto &pair : this->arcs)
        {
            delete pair.second;
        }
        this->arcs.clear();

        // Copie de la gestionnaire de rue
        this->gr = other.gr;

        // Copie profonde des arcs
        for (const auto &pair : other.arcs)
        {
            this->arcs[pair.first] = new arc(*pair.second);
        }
    }
    return *this;
}

string EnsembleArc::rechercherArc(string o, string d)
{
    // Parcourir chaque arc dans le unordered_map
    for (const auto &pair : arcs)
    {
        arc *currentArc = pair.second;

        // Comparer les noeuds de départ et d'arrivée
        if (currentArc->getStartingNode() == o && currentArc->getEndingNode() == d)
        {
            return currentArc->getId(); // Retourner l'ID de l'arc
        }
    }
    return "";
}
