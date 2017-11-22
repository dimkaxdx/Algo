#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

#define int long long

int input()
{
    int res = 0; char c = ' ';
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') res = res * 10 + (c - '0'), c = getchar();
    return res;
}

int lazy[4*N];
int tree[4*N];

void updateRange(int node, int start, int end, int l, int r, int val)
{
    if(lazy[node] != 0)
    {
        tree[node] += (end - start + 1) * lazy[node];
        if(start != end)
        {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(start > end or start > r or end < l)
        return;
    if(start >= l and end <= r)
    {
        tree[node] += (end - start + 1) * val;
        if(start != end)
        {
            lazy[node*2] += val;
            lazy[node*2+1] += val;
        }
        return;
    }
    int mid = (start + end) / 2;
    updateRange(node*2, start, mid, l, r, val);
    updateRange(node*2 + 1, mid + 1, end, l, r, val);
    tree[node] = tree[node*2] + tree[node*2+1];
}

int queryRange(int node, int start, int end, int l, int r)
{
    if(start > end or start > r or end < l)
        return 0;
    if(lazy[node] != 0)
    {
        tree[node] += (end - start + 1) * lazy[node];
        if(start != end)
        {
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if(start >= l and end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    int p1 = queryRange(node*2, start, mid, l, r);
    int p2 = queryRange(node*2 + 1, mid + 1, end, l, r);
    return (p1 + p2);
}

int32_t main()
{
	#ifdef LOCAL_DEV
    #else
        freopen("G.IN", "r", stdin);
        freopen("G.OUT", "w", stdout);
    #endif
	int t = input();
	while(t--)
	{
		int n = input(), c = input();
		while(c--)
		{
			int ty = input();
			if(ty == 0)
			{
				int l = input(), r = input(), val = input(); --l, --r;
				updateRange(1, 0, n-1, l, r, val);
			}
			else
			{
				int l = input(), r = input(); --l, --r;
				cout << queryRange(1, 0, n-1, l, r) << "\n";
			}
		}
		memset(lazy, 0, sizeof(lazy));
		memset(tree, 0, sizeof(tree));
	}
}
