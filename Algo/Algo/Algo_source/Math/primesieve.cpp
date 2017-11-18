#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

bool sieve[N];
vector<int> primes;

void compute_primes(int n)
{
    for (int i = 2 ; i <= n ; i ++)
        sieve[i] = true;
    for (int i = 2 ; i <= n ; i ++)
        if (sieve[i])
        {
            primes.push_back(i);
            for (long long j = (long long)i * (long long)i ; j <= n; j += i)
                sieve[j] = false;
        }
}

int main()
{
    int n; cin >> n;
    compute_primes(n);
    cout << "Простые числа: ";
    for (int i: primes)
        cout << i << ' ';
}
