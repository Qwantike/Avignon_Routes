#include "tris.h"

void triRapide(vector<pair<string, int>> &vec, int a, int b)
{
    if (a < b)
    {
        int p = a + rand() % (b - a + 1);
        swap(vec[a], vec[p]);
        int m;
        partitionnement(vec, a, b, m);
        triRapide(vec, a, m - 1);
        triRapide(vec, m + 1, b);
    }
}

// décroissant
void partitionnement(vector<pair<string, int>> &vec, int a, int b, int &m)
{
    int l = a + 1;
    int k = b;
    auto pivot = vec[a].second;

    while (l <= k)
    {
        while (l <= b && vec[l].second >= pivot)
        {
            l++;
        }
        while (k >= a && vec[k].second < pivot)
        {
            k--;
        }
        if (l < k)
        {
            swap(vec[l], vec[k]);
            l++;
            k--;
        }
    }
    swap(vec[a], vec[k]);
    m = k;
}