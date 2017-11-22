#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

int n;
int a[N], f[N];

int sum(int x)
{
    int result = 0;
    for (; x >= 0; x = (x & (x + 1)) - 1)
        result += f[x];
    return result;
}

int sum(int l, int r)
{
    if (l)
        return sum(r) - sum(l - 1);
    else
        return sum(r);
}

void increase(int idx, int delta)
{
    a[idx] += delta;
    for (; idx < n; idx |= idx + 1)
        f[idx] += delta;
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int t;
        cin >> t;
        increase(i, t);
    }

}
