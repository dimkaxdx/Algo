#include <bits/stdc++.h>

using namespace std;

vector<int> get_sum(string a, string b)
{
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    vector<int> res( max(a.size(), b.size()) );
    for(int i = 0 ; i < (int)a.size() ; i ++)
        res[i] += (a[i] - '0');
    for(int i = 0 ; i < (int)b.size() ; i ++)
        res[i] += (b[i] - '0');
    for(int i = 0 ; i < (int)res.size() ; i ++)
        if(res[i] >= 10)
        {
            if(i+1 == (int)res.size())
                res.push_back(res[i]/10);
            else
                res[i+1] += res[i]/10;
            res[i] %= 10;
        }
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
