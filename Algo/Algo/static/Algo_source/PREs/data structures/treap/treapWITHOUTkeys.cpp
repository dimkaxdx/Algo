#include <bits/stdc++.h>

using namespace std;

mt19937 gen(chrono::system_clock::now().time_since_epoch().count());

struct node
{
    int val, y;
    node *l, *r;
    int sz;

    node() {}
    node(int val): val(val), y(gen() % 1000000000), l(0), r(0), sz(1) {}
    node(int val, node *l, node *r): val(val), y(gen() % 1000000000), l(l), r(r), sz(1) {}


    int sizeOf(node *a)
    {
        if(a) return a->sz;
        return 0;
    }

    void update()
    {
        sz = 1 + sizeOf(l) + sizeOf(r);
    }
    void print()
    {
        if(l) l->print();
        cout << val << ' ';
        if(r) r->print();
    }
};

struct treap
{
    node *root;

    treap(): root(0) {};

    void merge(node *l, node *r, node *&v)
    {
         if (!l || !r) return void(v = l ? l : r);
         if (l->y > r->y)
         {
            v = r;
            merge(l, r->l, v->l);
         }
         else
         {
            v = l;
            merge(l->r, r, v->r);
         }
         v->update();
    }
    void split(node *t, int x, node *&l, node *&r)
    {
        if(!t) return void(l = r = nullptr);
        int sz = t->sizeOf(t->l) + 1;
        if(x < sz)
        {
            r = t;
            split(t->l, x, l, r->l);
            r->update();
        }
        else
        {
            l = t;
            split(t->r, x-sz, l->r, r);
            l->update();
        }
    }
    void add(int pos, int val)
    {
        node *a, *b;
        split(root, pos, a, b);
        merge(a, new node(val), a);
        merge(a, b, root);
    }
    void print()
    {
        root->print();
        cout << endl;
    }

    void moveToFront(int l, int r)
    {
        node *a, *b;
        split(root, l-1, a, b);
        node *c, *d;
        split(b, r-l+1, c, d);
        merge(c, a, c);
        merge(c, d, root);
    }
};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    #ifdef LOCAL_DEV
    #else
        freopen("movetofront.in", "r", stdin);
        freopen("movetofront.out", "w", stdout);
    #endif
    int n, m; cin >> n >> m;
    treap t;
    for(int i = 1 ; i <= n ; i ++)
        t.add(i, i);
    while(m--)
    {
        int l, r; cin >> l >> r;
        t.moveToFront(l, r);
    }
    t.print();
}
