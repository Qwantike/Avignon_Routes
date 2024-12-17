#ifndef TRIS_H
#define TRIS_H

#include <vector>
#include <string>
#include <utility> // Pour std::pair

using namespace std;

// Fonction pour trier un vecteur de paires (id de noeud, degré) avec le tri rapide
void triRapide(vector<pair<string, int>> &vec, int a, int b);

// Fonction pour partitionner un vecteur de paires autour d'un pivot
void partitionnement(vector<pair<string, int>> &vec, int a, int b, int &m);

#endif // TRIS_H
