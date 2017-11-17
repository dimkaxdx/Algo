#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

vector<int> g[N];
bool used[N];
int dst[N], pr[N];

int main()
{
    memset(dst, INT_MAX, sizeof(dst));
    memset(pr, -1, sizeof(pr));
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
            pr[next] = cur;
        }
    }

    int k;
    cout << "Введите номер вершины, путь до которой вас интересует: "; cin >> k; --k;

    int cur = k; vector<int> p;
    while(cur != -1)
    {
        p.push_back(cur);
        cur = pr[cur];
    }
    reverse(p.begin(), p.end());

    cout << "Наикратчайший пусть из вершины 1 до " << k+1 << ":\n";
    if(p.size() == 1)
        cout << "Вершина " << k+1 << " недостежима из вершины 1.\n";
    else
        for(int c : p)
            cout << c+1 << ' ';
}
