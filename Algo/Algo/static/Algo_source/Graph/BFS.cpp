#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

vector<int> g[N];
bool used[N];
int dst[N];

int main()
{
    memset(dst, INT_MAX, sizeof(dst));
    int n, m; cin >> n >> m;
    for(int i = 0 ; i < m ; i ++)
    {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<int> q;
    q.push(0); used[0] = true; dst[0] = 0;
    while(!q.empty())
    {
        int cur = q.front(); q.pop();
        for(int next : g[cur])
        {
            if(used[next])
                continue;
            q.push(next);
            used[next] = true;
            dst[next] = dst[cur] + 1;
        }
    }
    for(int i = 0 ; i < n ; i ++)
        if(dst[i] == INT_MAX)
            cout << "Вершина " << i+1 << " недостежима из вершины 1.\n";
        else
            cout << "Дистанция от вершины 1 до " << i+1 << " равна " << dst[i] << ".\n";
}
