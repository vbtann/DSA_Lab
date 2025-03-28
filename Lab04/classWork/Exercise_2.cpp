#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int> &a, int size)
{
    // Sort even numbers in ascending order
    for (int i = 0; i < size; i++)
    {
        if (a[i] % 2 == 0)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (a[j] % 2 == 0 && a[i] > a[j])
                {
                    swap(a[i], a[j]);
                }
            }
        }
    }

    // Sort odd numbers in descending order
    for (int i = 0; i < size; i++)
    {
        if (a[i] % 2 != 0)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (a[j] % 2 != 0 && a[i] < a[j])
                {
                    swap(a[i], a[j]);
                }
            }
        }
    }
}

int main()
{
    int arraySize;
    cin >> arraySize;

    vector<int> arr(arraySize);

    for (int i = 0; i < arraySize; i++)
    {
        cin >> arr[i];
    }

    insertionSort(arr, arraySize);

    for (int i = 0; i < arraySize; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;

    return 0;
}