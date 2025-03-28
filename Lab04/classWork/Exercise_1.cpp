#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>
#include <cstring>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int MAX = (int)1e9;
const int SIZE = 10000;
int arr[SIZE];

void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

void arrayGenerate(int size)
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed);

    uniform_int_distribution<int> distribution(1, size);

    for (int i = 0; i < SIZE; i++)
    {
        arr[i] = distribution(generator);
    }
}

void printArray(int a[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << ' ';
    }
    cout << "\n";
}

void insertionSort(int arr[], int size)
{
    for (int i = 1; i < size; i++)
    {
        int tmp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] >= tmp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = tmp;
    }
}

void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        int minInd = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minInd])
            {
                minInd = j;
            }
        }

        if (minInd != i)
            swap(arr[i], arr[minInd]);
    }
}

void interchangeSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[i] > arr[j])
            {
                swap(arr[i], arr[j]);
            }
        }
    }
}

int main(void)
{
    arrayGenerate(SIZE);
    int cloneArray[SIZE];

    // insertion sort
    auto insertion_sort_start = high_resolution_clock::now();
    insertionSort(arr, SIZE);
    auto insertion_sort_stop = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(insertion_sort_stop - insertion_sort_start);
    double insertion_sort_duration = (dur.count() * 0.000001);
    cout << fixed << setprecision(3) << "Insertion Sort running time: " << insertion_sort_duration << "\n";

    // selection sort
    auto selection_sort_start = high_resolution_clock::now();
    selectionSort(arr, SIZE);
    auto selection_sort_stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(selection_sort_stop - selection_sort_start);
    double selection_sort_duration = (dur.count() * 0.000001);
    cout << fixed << setprecision(3) << "Selection Sort running time: " << selection_sort_duration << "\n";

    // interchange sort
    auto interchange_sort_start = high_resolution_clock::now();
    interchangeSort(arr, SIZE);
    auto interchange_sort_stop = high_resolution_clock::now();
    dur = duration_cast<microseconds>(interchange_sort_stop - interchange_sort_start);
    double interchange_sort_duration = (dur.count() * 0.000001);
    cout << fixed << setprecision(3) << "Interchange Sort running time: " << interchange_sort_duration << "\n";

    cout << "The fastest algorithm: ";
    if (insertion_sort_duration < selection_sort_duration && insertion_sort_duration < interchange_sort_duration)
    {
        cout << "Insertion Sort";
    }
    else if (selection_sort_duration < insertion_sort_duration && selection_sort_duration < interchange_sort_duration)
    {
        cout << "Selection Sort";
    }
    else
    {
        cout << "Interchange Sort";
    }
    cout << "\n";

    cout << "The slowest algorithm: ";
    if (insertion_sort_duration > selection_sort_duration && insertion_sort_duration > interchange_sort_duration)
    {
        cout << "Insertion Sort";
    }
    else if (selection_sort_duration > insertion_sort_duration && selection_sort_duration > interchange_sort_duration)
    {
        cout << "Selection Sort";
    }
    else
    {
        cout << "Interchange Sort";
    }

    return 0;
}