#include <bits/stdc++.h>

using namespace std;

int mypow(int a, int n)
{
	int res = 1;
	while (n)
    {
		if (n & 1)
			res *= a;
		a *= a;
		n >>= 1;
	}
	return res;
}

int char_to_int(char a)
{
    if('0' <= a && a <= '9')
        return a-'0';
    return (a-'A') + 10;
}
int int_to_char(int a)
{
    if(a < 10)
        return a+'0';
    return (a - 10)+'A';
}

string convert(int num, int sys)
{
    string ans = "";
    while(num)
    {
        ans += int_to_char(num % sys);
        num /= sys;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
int deconvert(string num, int sys)
{
    int ans = 0;
    for(int i = 0 ; i < (int)num.size() ; i ++)
        ans += char_to_int(num[i]) * mypow(sys, num.size()-i-1);
    return ans;
}

int main()
{
    cout << "Введите число и систему\n";
    int num, sys; cin >> num >> sys;
    string ans = convert(num, sys);
    cout << ans << endl;
    cout << deconvert(ans, sys) << endl;
}
