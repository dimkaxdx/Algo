#include <bits/stdc++.h>

using namespace std;

vector<int> getDividers(int x)
{
    vector<int> dividers;
    for (int i = 1 ; i <= sqrt(x) ; i ++)
        if (x % i == 0)
        {
            dividers.push_back(i);
            if (i * i != x)
                dividers.push_back(x/i);
        }
    return dividers;
}

int main()
{
    int num; cin >> num;
    vector<int> dividers = getDividers(num);
    sort(dividers.begin(), dividers.end()); //сортировка для красоты вывода
    cout << "Dividers for " << num << ": ";
    for(auto div : dividers)
        cout << div << ' ';
}
