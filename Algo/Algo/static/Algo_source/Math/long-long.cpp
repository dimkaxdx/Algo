#include <bits/stdc++.h>

using namespace std;

vector<int> get_sum(string a, string b) //a >= b
{
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<int> res( max(a.size(), b.size()) );
    for(int i = 0 ; i < (int)a.size() ; i ++)
        res[i] = (a[i] - '0');
    int need = 0;
    for(int i = 0 ; i < (int)b.size() || need ; i ++)
    {
        res[i] -= need + (i < (int)b.size() ? (b[i] - '0') : 0);
        need = (res[i] < 0);
        if(need)
            res[i] += 10;
    }
    while(res.size() > 1 && res.back() == 0)
        res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

int main()
{
    string a, b;
    cin >> a >> b;
    vector<int> ans = get_sum(a, b);
    for(int i : ans)
        cout << i;
}
