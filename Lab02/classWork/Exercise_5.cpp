#include <iostream>

using namespace std;

string input, ans;

string reverseString(int ind, string s)
{
    if (ind == s.length() - 1)
    {
        string tmp = "";
        tmp += s[ind];
        return tmp;
    }

    return reverseString(ind + 1, s) + s[ind];
}

int main()
{
    cin >> input;
    ans = reverseString(0, input);
    cout << ans;

    return 0;
}