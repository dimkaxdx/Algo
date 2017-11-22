#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

int p[N], rk[N];

void init_dsu()
{
    for (int i = 0 ; i < N ; i ++)
    {
        p[i] = i;
        rk[i] = 1;
    }
}

int get_root(int v)
{
    if (p[v] == v)
        return v;
    else
        return p[v] = get_root(p[v]);
}

bool merge(int a, int b)
{
    int ra = get_root(a), rb = get_root(b);
    if (ra == rb)
        return false;

    if (rk[ra] < rk[rb])
        p[ra] = rb;
    else if (rk[rb] < rk[ra])
        p[rb] = ra;
    else
    {
        p[ra] = rb;
        rk[rb]++;
    }
    return true;
}

int main()
{
    init_dsu();
    merge(1, 4);
    merge(2, 1);
    merge(3, 1);
    cout << get_root(2) << endl;
}
