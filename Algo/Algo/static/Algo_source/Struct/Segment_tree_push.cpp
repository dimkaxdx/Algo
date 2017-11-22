#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

struct Node
{
    int sum = 0;
    int m = 0;
};

int ar[N];
Node tree[4*N];

void build_tree(int tl, int tr, int v)
{
    if(tl == tr) return void( tree[v].sum = ar[tl] );
    int tm = (tl + tr) >> 1;
    build_tree(tl, tm, v*2);
    build_tree(tm+1, tr, v*2+1);
    tree[v].sum = tree[v*2].sum + tree[v*2+1].sum;
}

void push(int v, int tl, int tr)
{
    if(tree[v].m && v*2+1 < 4*N)
    {
        tree[v*2].m = tree[v*2+1].m = tree[v].m;
        tree[v].m = 0;
        int tm = (tl + tr) >> 1;
        tree[v*2].sum = (tm - tl + 1) * tree[v*2].m;
        tree[v*2+1].sum = (tr - tm) * tree[v*2+1].m;
    }
}

int get_sum(int l, int r, int tl, int tr, int v)
{
    if(l <= tl && tr <= r)
        return tree[v].sum;
    if(l > tr || r < tl)
        return 0;
    push(v, tl, tr);
    int tm = (tl + tr) >> 1;
    return get_sum(l, r, tl, tm, v*2) + get_sum(l, r, tm+1, tr, v*2+1);
}

void update(int l, int r, int tl, int tr, int v, int val)
{
    if(l <= tl && tr <= r)
    {
        tree[v].m = val;
        tree[v].sum = (tr - tl + 1) * val;
        return;
    }
    if(l > tr || r < tl)
        return;
    push(v, tl, tr);
    int tm = (tl + tr) >> 1;
    update(l, r, tl, tm, v*2, val);
    update(l, r, tm+1, tr, v*2+1, val);
    tree[v].sum = tree[v*2].sum + tree[v*2+1].sum;
}

int main()
{
    int n; cin >> n;
    for(int i = 0 ; i < n ; i ++)
        cin >> ar[i];
    build_tree(0, n-1, 1);
    string s;
    while(s != "exit")
    {
        cin >> s;
        if(s == "sum")
        {
            int l, r; cin >> l >> r;
            --l, --r;
            cout << get_sum(l, r, 0, n-1, 1) << endl;
        }
        if(s == "update")
        {
            int l, r, val; cin >> l >> r >> val;
            --l, --r;
            update(l, r, 0, n-1, 1, val);
            cout << "updated.\n";
        }
    }
    cout << "exit.\n";
}
