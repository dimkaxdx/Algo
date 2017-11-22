#include <bits/stdc++.h>

using namespace std;

mt19937 gen(chrono::system_clock::now().time_since_epoch().count());

struct node
{
    int val, y;
    node *l, *r;
    bool reversed;
    int mn;
    int sz;

    node() {}
    node(int val): val(val), y(gen() % 1000000000), l(0), r(0), sz(1), reversed(false), mn(val) {}

    int sizeOf(node *a)
    {
        if(a) return a->sz;
        return 0;
    }
    int minOf(node *a)
    {
        if(a) return a->mn;
        return INT_MAX;
    }

    void update()
    {
        sz = 1 + sizeOf(l) + sizeOf(r);
        mn = min(val, min(minOf(l), minOf(r)));
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

    treap(): root(0) {}

    void push(node *v)
    {
        if(!v || !v->reversed) return;
        swap(v->l, v->r);
        v->reversed = false;
        if(v->l) v->l->reversed ^= true;
        if(v->r) v->r->reversed ^= true;
    }
    void merge(node *l, node *r, node *&v)
    {
        if(l) push(l);
        if(r) push(r);
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
        push(t);
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
    void pushBack(int val)
    {
        merge(root, new node(val), root);
    }
    void _reverse(int l, int r)
    {
        node *a, *b;
        split(root, l-1, a, b);
        node *c, *d;
        split(b, r-l+1, c, d);
        if(c) c->reversed ^= true;
        merge(c, d, b);
        merge(a, b, root);
    }
    int minOf(int l, int r)
    {
        node *a, *b;
        split(root, l-1, a, b);
        node *c, *d;
        split(b, r-l+1, c, d);
        int res = c->mn;
        merge(c, d, b);
        merge(a, b, root);
        return res;
    }

    void print()
    {
        root->print();
        cout << endl;
    }

};

int main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    treap t;
    for(int i = 0 ; i < n ; i ++)
    {
        int temp; cin >> temp;
        t.pushBack(temp);
    }
    while(m--)
    {
        int ty; cin >> ty;
        if(ty == 1)
        {
            int l, r; cin >> l >> r;
            t._reverse(l, r);
        }
        else
        {
            int l, r; cin >> l >> r;
            cout << t.minOf(l, r) << "\n";
        }
    }
}
