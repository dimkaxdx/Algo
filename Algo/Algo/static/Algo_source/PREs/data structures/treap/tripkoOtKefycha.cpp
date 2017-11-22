#include <bits/stdc++.h>

using namespace std;

mt19937 gen(chrono::system_clock::now().time_since_epoch().count());

int mygcd(int x, int y) {
    if (x == 0 || y == 0) return x + y;
    return __gcd(x, y);
}

struct node {
    int x, y;
    node *l, *r;
    int sizeOf(node *a)
    {
        if(a)
            return a->sz;
        return 0;
    }
    long long sumOf(node *a)
    {
        if(a)
            return a->sum;
        return 0;
    }
    int gcdOf(node *a)
    {
        if(a)
            return a->gcd;
        return 0;
    }
    void update() {
        sz = 1 + sizeOf(l) + sizeOf(r);
        sum = x + sumOf(l) + sumOf(r);
        gcd = mygcd(x, mygcd(gcdOf(l), gcdOf(r)));
    }
    void print() {
        if (!this) return;
        l->print();
        cout << x << ' ';
        r->print();
    }

    int kth(int k) {
        int sz = sizeOf(l);
        if (sz + 1 == k) return x;
        if (k <= sz) return l->kth(k);
        return r->kth(k - 1 - sz);
    }

    node(){}
    node(int x): x(x), y(gen() % 1000000000), l(0), r(0), sz(1), gcd(x), sum(x) {}
    int sz;
    long long sum;
    int gcd;
};

struct treap{
    node *root;
    treap(): root(0) {}
    void Merge(node *l, node *r, node *&v) {
         if (!l || !r) return void(v = l ? l : r);
         if (l->y > r->y) {
            v = r;
            Merge(l, r->l, v->l);
         } else {
            v = l;
            Merge(l->r, r, v->r);
         }
         v->update();
    }

    void Split(node *t, int key, node *&l, node *&r) {
        if (!t) return void(l = r = nullptr);
        if (t->x <= key) {
            l = t;
            Split(t->r, key, l->r, r);
            l->update();
        } else {
            r = t;
            Split(t->l, key, l, r->l);
            r->update();
        }
    }
    void add(int x) {
        node *a, *b;
        Split(root, x, a, b);
        Merge(a, new node(x), a);
        Merge(a, b, root);
    }
    void del(int x) {
        node *a, *b;
        Split(root, x, a, b);
        node *c, *d;
        Split(a, x - 1, c, d);
        if(root->sizeOf(d) != 0) {
            Merge(c, d->l, c);
            Merge(c, d->r, c);
        }
        Merge(c, b, root);
    }
    int calc(int x) {
        node *a, *b;
        Split(root, x - 1, a, b);
        int ret = root->sizeOf(b);
        Merge(a, b, root);
        return ret;
    }
    void print() {
        root->print();
        cout << endl;
    }
    int kth(int x) {
        return root->kth(x);
    }
    long long sum(int L, int R) {
        node *a, *b;
        Split(root, R, a, b);
        node *c, *d;
        Split(a, L - 1, c, d);
        long long ret = root->sumOf(d);
        Merge(c, d, a);
        Merge(a, b, root);
        return ret;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    treap *t = new treap();
    int q;
    cin >> q;
    while(q--) {
        char c;
        int x;
        cin >> c >> x;
        if (c == '+') {
            t->add(x);
        } else {
            t->del(x);
        }
        cout << (t->root->gcdOf(t->root) ? t->root->gcdOf(t->root) : 0) << '\n';
    }
}
