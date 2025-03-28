#include <iostream>
#include <algorithm>

using namespace std;

long findGCD(int a, int b)
{
    if (b == 0)
    {
        return a;
    }

    return findGCD(b, a % b);
}

int main()
{
    int a, b;
    cin >> a >> b;
    long ans = findGCD(a, b);
    cout << ans;
    return 0;
}