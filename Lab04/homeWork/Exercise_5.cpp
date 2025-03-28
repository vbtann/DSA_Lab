#include <iostream>
#include <random>
#include <vector>
#include <cstring>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

const int SIZE = 500000;

vector<int> arr(SIZE + 1);

void arrayGenerate(vector<int> &a, int size)
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<> dis(1, 1000000);

    for (int i = 1; i <= size; i++)
    {
        a[i] = dis(gen);
    }
}

void print(vector<int> a, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << a[i] << ' ';
    }
    cout << "\n";
}

void sift(vector<int> &a, int left, int right)
{
    int i = left;
    int j = 2 * i + 1;
    int tmp = a[i];
    while (j <= right)
    {
        if (j < right)
        {
            if (a[j] < a[j + 1])
            {
                j++;
            }
        }

        if (tmp >= a[j])
        {
            break;
        }

        a[i] = a[j];
        i = j;
        j = 2 * i + 1;
    }
    a[i] = tmp;
}

void heapSort(vector<int> &a, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        sift(a, i, size - 1);
    }

    for (int i = size - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        sift(a, 0, i - 1);
    }
}

void quickSort(vector<int> &a, int left, int right)
{
    int i = left, j = right, pivot = a[left];

    while (i <= j)
    {
        while (a[i] < pivot)
        {
            ++i;
        }
        while (a[j] > pivot)
        {
            --j;
        }

        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }

    if (left < j)
    {
        quickSort(a, left, j);
    }
    if (i < right)
    {
        quickSort(a, i, right);
    }
}

int main(void)
{
    int n = SIZE;

    arrayGenerate(arr, n);

    // Heap sort
    vector<int> arr_clone = arr;
    auto heapSort_start = chrono::high_resolution_clock::now();
    heapSort(arr_clone, n);
    auto heapSort_stop = chrono::high_resolution_clock::now();
    auto heapSort_duration = duration_cast<microseconds>(heapSort_stop - heapSort_start);
    cout << fixed << setprecision(3) << "Heap Sort: " << heapSort_duration.count() * 0.000001 << " seconds\n";

    // Quick sort
    vector<int> arr_clone_1 = arr;
    auto quickSort_start = chrono::high_resolution_clock::now();
    quickSort(arr_clone_1, 0, n);
    auto quickSort_stop = chrono::high_resolution_clock::now();
    auto quickSort_duration = duration_cast<microseconds>(quickSort_stop - quickSort_start);
    cout << fixed << setprecision(3) << "Quick Sort: " << quickSort_duration.count() * 0.000001 << " seconds\n";

    if (quickSort_duration.count() < heapSort_duration.count())
    {
        cout << "The fastest algorithm: Quick Sort\n";
        cout << "The slowest algorithm: Heap Sort\n";
    }
    else
    {
        cout << "The fastest algorithm: Heap Sort\n";
        cout << "The slowest algorithm: Quick Sort\n";
    }
    return 0;
}