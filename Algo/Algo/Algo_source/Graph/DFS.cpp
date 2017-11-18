#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

vector<int> g[N];
bool used[N];

void dfs(int v)
{
    cout << v+1 << ' ';
    for(auto next : g[v])
    {
        if(!used[next])
        {
            used[next] = true;
            dfs(next);
        }
    }
}

int main()
{
    int n, m; cin >> n >> m;
    for(int i = 0 ; i < m ; i ++)
    {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0);
}
