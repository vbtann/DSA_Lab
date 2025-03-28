#include <iostream>

using namespace std;

long long sumDigit(int n)
{
    if (n == 0)
    {
        return 0;
    }

    return (n % 10 + sumDigit(n / 10));
}

int main()
{
    int n;
    cin >> n;
    long long ans = sumDigit(n);
    cout << ans;
    return 0;
}