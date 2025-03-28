#include <iostream>

using namespace std;

int elementCnt;
int arr[101];

bool strictlyInc(int i, int arr[])
{
    if (i == elementCnt - 1)
    {
        return true;
    }

    if (arr[i] >= arr[i + 1])
    {
        return false;
    }

    return strictlyInc(i + 1, arr);
}
int main()
{
    cin >> elementCnt;
    for (int i = 0; i < elementCnt; i++)
    {
        cin >> arr[i];
    }
    (strictlyInc(0, arr)) ? cout << "Yes" : cout << "No";
    return 0;
}