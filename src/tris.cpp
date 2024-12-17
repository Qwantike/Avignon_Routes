#include "tris.h"

void triRapide(vector<pair<string, int>> &vec, int a, int b)
{
    if (a < b)
    {
        int p = a + rand() % (b - a + 1);
        swap(vec[a], vec[p]); // Met le pivot aléatoire au début

        int m;
        partitionnement(vec, a, b, m); // Partitionne le vecteur autour du pivot
        triRapide(vec, a, m - 1);      // Tri récursif sur la partie gauche
        triRapide(vec, m + 1, b);      // Tri récursif sur la partie droite
    }
}

// Tri décroissant
void partitionnement(vector<pair<string, int>> &vec, int a, int b, int &m)
{
    int l = a + 1;              // Indice de début
    int k = b;                  // Indice de fin
    auto pivot = vec[a].second; // Valeur du pivot (degré de l'élément à l'indice 'a')

    while (l <= k)
    {
        while (l <= b && vec[l].second >= pivot)
        { // Avancer 'l' tant que les éléments sont >= pivot
            l++;
        }
        while (k >= a && vec[k].second < pivot)
        { // Reculer 'k' tant que les éléments sont < pivot
            k--;
        }
        if (l < k)
        { // Échanger les éléments si 'l' est avant 'k'
            swap(vec[l], vec[k]);
            l++;
            k--;
        }
    }
    swap(vec[a], vec[k]); // Échanger le pivot avec l'élément à l'indice 'k'
    m = k;                // Retourner la position finale du pivot
}