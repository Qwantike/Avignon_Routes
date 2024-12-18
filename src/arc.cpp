#include "arc.h"

arc::arc(string id, string startingNode, string endingNode, string oneWay, string reversed, string lane, string highway, string length, string maxSpeed, string speedKph, string travelTime)
{
    this->id = id;
    this->startingNode = startingNode;
    this->endingNode = endingNode;
    if (oneWay == "true")
    {
        this->oneWay = true;
        if (reversed == "true")
        {
            this->reversed = true;
        }
        else
            this->reversed = false;
    }
    else
    {
        this->oneWay = false;
        this->reversed = false;
    }
    this->lane = lane;
    this->highway = highway;
    this->length = length;
    this->maxSpeed = maxSpeed;
    this->speedKph = speedKph;
    this->travelTime = travelTime;
}

void arc::affiche()
{
    cout << "Nom de la rue/id : " << this->id << endl;
    if (this->reversed == true)
    {
        cout << "id de l'arc entrant : " << this->startingNode << endl;
        cout << "id de l'arc sortant : " << this->endingNode << endl;
    }
    else
    {
        cout << "id de l'arc entrant : " << this->endingNode << endl;
        cout << "id de l'arc sortant : " << this->startingNode << endl;
    }
    cout << "Nombre de voix : " << this->lane << endl;
    cout << "Type de route : " << this->highway << endl;
    cout << "Longueur de la route (m) : " << this->length << endl;
    if (this->maxSpeed != "")
    {
        cout << "Vitesse maximum : " << this->maxSpeed << endl;
    }
    else
    {
        cout << "Vitesse maximum : " << this->speedKph << endl;
    }
    cout << "Temps de trajet : " << this->travelTime << endl;
}

string arc::getEndingNode()
{
    return this->endingNode;
}

string arc::getStartingNode()
{
    return this->startingNode;
}

bool arc::getOneWay()
{
    return this->oneWay;
}

bool arc::getReversed()
{
    return this->reversed;
}

string arc::getId()
{
    if (id.empty())
    {
        cout << "Erreur : ID vide" << endl;
    }
    return id;
}