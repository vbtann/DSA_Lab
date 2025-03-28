#include <iostream>
#include <cstring>

using namespace std;

int elementCnt;
int numArray[(int)1e8];

int linearSearch(int val)
{
    int i = 0;
    while (i <= elementCnt)
    {
        if (numArray[i] == val)
        {
            return i;
        }
        i++;
    }

    return -1;
}

int sentinelLinearSearch(int val)
{
    int i = 0;
    numArray[elementCnt] = val;
    while (numArray[i] != val)
    {
        i++;
    }

    if (i < elementCnt)
    {
        return i;
    }
    else
    {
        return -1;
    }
}

int binarySearch(int val)
{
    int l = 0;
    int r = elementCnt - 1;

    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (numArray[mid] == val)
        {
            while (mid >= 0 && numArray[mid - 1] == val)
            {
                --mid;
            }
            return mid;
        }
        else if (numArray[mid] < val)
        {
            l = mid + 1;
        }
        else
        {
            r = mid - 1;
        }
    }
    return -1;
}

int interpolationSearch(int val)
{
    int l = 0;
    int r = elementCnt - 1;

    while (l <= r && val >= numArray[l] && val <= numArray[r])
    {
        if (l == r)
        {
            if (numArray[l] == val)
            {
                return l;
            }
            return -1;
        }

        int pos = l + ((val - numArray[l]) * (r - l)) / (numArray[r] - numArray[l]);

        if (numArray[pos] == val)
        {
            while (pos >= 0 && numArray[pos - 1] == val)
            {
                --pos;
            }
            return pos;
        }

        if (numArray[pos] < val)
        {
            l = pos + 1;
        }
        else
        {
            r = pos - 1;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    freopen(argv[3], "r", stdin);
    freopen(argv[4], "w", stdout);

    cin >> elementCnt;
    for (int i = 0; i < elementCnt; i++)
    {
        cin >> numArray[i];
    }

    if (strcmp(argv[1], "1") == 0)
    {
        cout << linearSearch(atoi(argv[2]));
    }
    else if (strcmp(argv[1], "2") == 0)
    {
        cout << sentinelLinearSearch(atoi(argv[2]));
    }
    else if (strcmp(argv[1], "3") == 0)
    {
        cout << binarySearch(atoi(argv[2]));
    }
    else if (strcmp(argv[1], "4") == 0)
    {
        cout << interpolationSearch(atoi(argv[2]));
    }
    return 0;
}