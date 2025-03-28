#include <iostream>

using namespace std;

string input;

bool checkPalindrome(int ind, string s)
{
    if (ind == s.length() / 2)
    {
        return 1;
    }

    if (s[ind] != s[s.length() - ind - 1])
    {
        return 0;
    }

    return checkPalindrome(ind + 1, s);
}

int main()
{
    cin >> input;
    (checkPalindrome(0, input)) ? cout << "Yes" : cout << "No";
    return 0;
}