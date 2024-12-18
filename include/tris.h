#ifndef TRIS_H
#define TRIS_H

#include <vector>
#include <string>
#include <utility> // std::pair

using namespace std;

// vecteur de paires (id de noeud, degré)
void triRapide(vector<pair<string, int>> &vec, int a, int b);

void partitionnement(vector<pair<string, int>> &vec, int a, int b, int &m);

#endif
