#include <iostream>

using namespace std;

void inputArray(int *&arr, int n)
{
    if (n == 0)
    {
        arr = nullptr;
        return;
    }
    arr = new int[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
}

void printArray(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << ' ';
    }
}

int findMax(int *arr, int n)
{
    int max = -(int)(1e8);
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}

int sumArray(int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    return sum;
}

void concatArray(int *a, int na, int *b, int nb, int *&res, int &nres)
{
    res = new int[na + nb];
    nres = na + nb;
    for (int i = 0; i < na; i++)
    {
        res[i] = a[i];
    }
    for (int i = 0; i < nb; i++)
    {
        res[i + na] = b[i];
    }
}

void findLongestAscendingSubarray(int *arr, int n, int *&res, int &nres)
{
    if (n == 0)
    {
        res = nullptr;
        nres = 0;
    }

    int stPos = 0;
    int elementCount = 1;
    int maxElementCount = 0;
    int maxStPos = 0;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > arr[i - 1])
        {
            elementCount++;
            if (elementCount > maxElementCount)
            {
                maxElementCount = elementCount;
                maxStPos = stPos;
            }
        }
        else
        {
            elementCount = 1;
            stPos = i;
        }
    }

    nres = maxElementCount;
    res = new int[nres];
    int j = 0;
    for (int i = 0; i < maxElementCount; i++)
    {
        res[i] = arr[maxStPos + i];
    }
}

int main()
{
    // Input array a
    int aElementCount;
    int *a;
    cout << "Enter number of element in array a: ";
    cin >> aElementCount;
    inputArray(a, aElementCount);

    // Input array b
    int bElementCount;
    int *b;
    cout << "Enter number of element in array b: ";
    cin >> bElementCount;
    inputArray(b, bElementCount);

    // Concat a & b into c
    int cElementCount;
    int *c;
    concatArray(a, aElementCount, b, bElementCount, c, cElementCount);

    cout << "Array c: ";
    printArray(c, cElementCount);
    cout << "\n";

    int cMax = findMax(c, cElementCount);
    cout << "Maximum value in c is: " << cMax << "\n";

    int cSum = sumArray(c, cElementCount);
    cout << "Sum of the element in c is: " << cSum << "\n";

    // Find longest ascending sub array in c
    int subArrayElementCount;
    int *subArray;
    findLongestAscendingSubarray(c, cElementCount, subArray, subArrayElementCount);
    cout << "Longest ascending sub array is: ";
    printArray(subArray, subArrayElementCount);

    delete[] a;
    delete[] b;
    delete[] c;
    delete[] subArray;
    return 0;
}