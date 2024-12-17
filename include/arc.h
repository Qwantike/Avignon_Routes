#ifndef ARC_H
#define ARC_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

class arc
{
private:
    string id;
    string startingNode;
    string endingNode;
    bool oneWay;
    bool reversed;
    string lane;
    string highway;
    string length;
    string maxSpeed;
    string speedKph;
    string travelTime;

public:
    arc(string id, string o, string d, string oneWay, string reversed, string lane, string highway, string length, string maxspeed, string speedKph, string travelTime);
    void affiche();
    string getEndingNode();
    string getStartingNode();
    bool getOneWay();
    bool getReversed();
    string getId();
};

#endif