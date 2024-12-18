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
        arc *a = new arc(id, startingNode, endingNode, oneWay, reversed, lane, highway, length, maxSpeed, speedKph, travelTime);
        this->arcs[id] = a;
        cpt++;
    }
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

void EnsembleArc::ajouterArc(const string &id, const string &startingNode, const string &endingNode, const string &oneWay, const string &reversed, const string &lane, const string &highway, const string &length, const string &maxSpeed, const string &speedKph, const string &travelTime)
{
    string idUnique = gr.nomRueAvecIndex(id);
    arc *a = new arc(idUnique, startingNode, endingNode, oneWay, reversed, lane, highway, length, maxSpeed, speedKph, travelTime);
    arcs[idUnique] = a;
}

arc *EnsembleArc::chercherArc(const string &id)
{
    if (arcs.find(id) != arcs.end())
    {
        return arcs[id];
    }
    return nullptr;
}

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
        cout << "Arc ID : " << pair.first << endl;
        cout << "Vérification ID : " << pair.second->getId() << endl;
    }
    cout << "TEST FINI" << endl;
}
// Constructeur par recopie (copie profonde des arcs)
EnsembleArc::EnsembleArc(const EnsembleArc &other)
{
    // copie gr
    this->gr = other.gr;

    // copie map arcs
    for (const auto &pair : other.arcs)
    {
        this->arcs[pair.first] = new arc(*pair.second);
    }
}

// Opérateur d'affectation
EnsembleArc &EnsembleArc::operator=(const EnsembleArc &other)
{
    // != auto-affectation
    if (this != &other)
    {
        for (auto &pair : this->arcs)
        {
            delete pair.second;
        }
        this->arcs.clear();

        // Copie gestionnaire de rue
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
    for (const auto &pair : arcs)
    {
        arc *currentArc = pair.second;

        if (currentArc->getStartingNode() == o && currentArc->getEndingNode() == d)
        {
            return currentArc->getId();
        }
    }
    return "";
}
