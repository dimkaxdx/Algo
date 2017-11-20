#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;
const int INF = 1e9 + 7;

vector<pair<int, int> > g[N];
int dst[N], pr[N];

int main()
{
    memset(dst, INF, sizeof(dst));
    memset(pr, -1, sizeof(pr));

    int n, m; cin >> n >> m;
    for(int i = 0 ; i < m ; i ++)
    {
        int u, v, l; cin >> u >> v >> l;
        --u, --v;
        g[u].push_back({v, l});
        g[v].push_back({u, l});
    }
    int start, finish; cin >> start >> finish;
    --start, --finish;

    dst[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push({0, start});

    while (!q.empty())
    {
        pair<int, int> cur = q.top(); q.pop();

        int cur_dst = cur.first, v = cur.second;
        if (dst[v] < cur_dst)
            continue;

        for (auto e: g[v])
        {
            int next = e.first, next_dst = e.second + cur_dst;
            if (next_dst < dst[next])
            {
                dst[next] = next_dst;
                pr[next] = v;
                q.push({next_dst, next});
            }
        }
    }

    vector<int> path;
    int cur = finish;
    path.push_back(cur);
    while (pr[cur] != -1)
    {
        cur = pr[cur];
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());

    cout << "Коротчайший путь из " << start + 1 << " в " << finish + 1 << ": ";
    for (int i: path)
        cout << i + 1 << " ";
}
