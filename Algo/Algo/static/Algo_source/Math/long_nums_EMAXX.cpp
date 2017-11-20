#include <bits/stdc++.h>

using namespace std;

typedef vector<int> lnum;

const int base = 1000*1000*1000;

void sum(lnum &a, lnum &b)
{
    int carry = 0;
    for (size_t i=0; i<max(a.size(),b.size()) || carry; ++i) {
    	if (i == a.size())
    		a.push_back (0);
    	a[i] += carry + (i < b.size() ? b[i] : 0);
    	carry = a[i] >= base;
    	if (carry)  a[i] -= base;
    }
}

void dec(lnum& a, lnum &b)
{
    int carry = 0;
    for (size_t i=0; i<b.size() || carry; ++i) {
    	a[i] -= carry + (i < b.size() ? b[i] : 0);
    	carry = a[i] < 0;
    	if (carry)  a[i] += base;
    }
    while (a.size() > 1 && a.back() == 0)
    	a.pop_back();
}

void multLongOnShort(lnum&a, int b) //(b <= BASE)
{
    int carry = 0;
    for (size_t i=0; i<a.size() || carry; ++i) {
    	if (i == a.size())
    		a.push_back (0);
    	long long cur = carry + a[i] * 1ll * b;
    	a[i] = int (cur % base);
    	carry = int (cur / base);
    }
    while (a.size() > 1 && a.back() == 0)
    	a.pop_back();
}

void multLongOnLong(lnum& a, lnum& b)
{
    lnum c (a.size()+b.size());
    for (size_t i=0; i<a.size(); ++i)
    	for (int j=0, carry=0; j<(int)b.size() || carry; ++j) {
    		long long cur = c[i+j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
    		c[i+j] = int (cur % base);
    		carry = int (cur / base);
    	}
    while (c.size() > 1 && c.back() == 0)
    	c.pop_back();
    a = c;
}

void divLongOnShort(lnum& a, int b) //(b <= BASE)
{
    int carry = 0;
    for (int i=(int)a.size()-1; i>=0; --i) {
    	long long cur = a[i] + carry * 1ll * base;
    	a[i] = int (cur / b);
    	carry = int (cur % b);
    }
    while (a.size() > 1 && a.back() == 0)
    	a.pop_back();
}

int main()
{
    string sa, sb; cin >> sa >> sb;
    lnum a, b;

    for (int i=(int)sa.length(); i>0; i-=9)
	if (i < 9)
		a.push_back (atoi (sa.substr (0, i).c_str()));
	else
		a.push_back (atoi (sa.substr (i-9, 9).c_str()));

    for (int i=(int)sb.length(); i>0; i-=9)
    	if (i < 9)
    		b.push_back (atoi (sb.substr (0, i).c_str()));
    	else
    		b.push_back (atoi (sb.substr (i-9, 9).c_str()));

    multLongOnLong(a, b);

    printf ("%d", a.empty() ? 0 : a.back());
    for (int i=(int)a.size()-2; i>=0; --i)
    	printf ("%09d", a[i]);

}
