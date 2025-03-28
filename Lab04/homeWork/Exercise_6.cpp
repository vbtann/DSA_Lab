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

// Heap sort
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
    // Build max heap
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        sift(a, i, size - 1);
    }

    // Heap sort
    for (int i = size - 1; i > 0; i--)
    {
        swap(a[0], a[i]);
        sift(a, 0, i - 1);
    }
}

// Quick sort
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

// Merge sort

vector<int> tmp(SIZE + 1);

void mergeSort(vector<int> &a, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = (left + right) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);

    int i = left, j = mid + 1, cur = 0;

    while (i <= mid || j <= right)
    {
        if (i > mid)
        {
            tmp[cur++] = a[j++];
        }
        else if (j > right)
        {
            tmp[cur++] = a[i++];
        }
        else if (a[i] < a[j])
        {
            tmp[cur++] = a[i++];
        }
        else
        {
            tmp[cur++] = a[j++];
        }
    }

    for (int i = 0; i < cur; i++)
    {
        a[left + i] = tmp[i];
    }
}

// Counting sort
vector<int> countingSort(vector<int> a)
{
    vector<int> sortedArray(SIZE + 1);
    int max = -1 * (int)1e8;
    for (int x : a)
    {
        if (x > max)
        {
            max = x;
        }
    }
    vector<int> existCount(max + 1);

    for (int num : a)
    {
        existCount[num]++;
    }

    for (int i = 0; i < max + 1; i++)
    {
        existCount[i] += existCount[i - 1];
    }

    for (int i = a.size() - 1; i >= 0; i--)
    {
        sortedArray[existCount[a[i]] - 1] = a[i];
        existCount[a[i]]--;
    }

    return sortedArray;
}

int findMax(vector<int> a)
{
    int max = -(int)1e8;
    for (int num : a)
    {
        if (num > max)
        {
            max = num;
        }
    }
    return max;
}

void countSort(vector<int> &a, int size, int exp)
{
    vector<int> outArray(size);
    vector<int> countArray(size, 0);

    // Count the occurances of numbers base on current digit
    for (int i = 0; i < size; i++)
    {
        countArray[(a[i] / exp) % 10]++;
    }

    for (int i = 0; i < size; i++)
    {
        outArray[countArray[(a[i] / exp) % 10] - 1] = a[i];
        countArray[(a[i] / exp) % 10]--;
    }

    for (int i = 0; i < size; i++)
    {
        a[i] = outArray[i];
    }
}

void radixSort(vector<int> &a, int size)
{
    int maxNum = findMax(a);

    for (int exponent = 1; maxNum / exponent > 0; exponent *= 10)
    {
        countSort(a, SIZE + 1, exponent);
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
    arr_clone = arr;
    auto quickSort_start = chrono::high_resolution_clock::now();
    quickSort(arr_clone, 0, n);
    auto quickSort_stop = chrono::high_resolution_clock::now();
    auto quickSort_duration = duration_cast<microseconds>(quickSort_stop - quickSort_start);
    cout << fixed << setprecision(3) << "Quick Sort: " << quickSort_duration.count() * 0.000001 << " seconds\n";

    // Merge sort
    arr_clone = arr;
    auto mergeSort_start = chrono::high_resolution_clock::now();
    mergeSort(arr_clone, 0, n);
    auto mergeSort_stop = chrono::high_resolution_clock::now();
    auto mergeSort_duration = duration_cast<microseconds>(mergeSort_stop - mergeSort_start);
    cout << fixed << setprecision(3) << "Merge Sort: " << mergeSort_duration.count() * 0.000001 << " seconds\n";

    // Counting sort
    auto countingSort_start = chrono::high_resolution_clock::now();
    arr_clone = countingSort(arr);
    auto countingSort_stop = chrono::high_resolution_clock::now();
    auto countingSort_duration = duration_cast<microseconds>(countingSort_stop - countingSort_start);
    cout << fixed << setprecision(3) << "Counting Sort: " << countingSort_duration.count() * 0.000001 << " seconds\n";

    // Heap sort
    arr_clone = arr;
    auto radixSort_start = chrono::high_resolution_clock::now();
    radixSort(arr_clone, SIZE + 1);
    auto radixSort_stop = chrono::high_resolution_clock::now();
    auto radixSort_duration = duration_cast<microseconds>(radixSort_stop - radixSort_start);
    cout << fixed << setprecision(3) << "Radix Sort: " << radixSort_duration.count() * 0.000001 << " seconds\n";

    vector<pair<string, long>> run_time;
    run_time.push_back({"Heap Sort", heapSort_duration.count()});
    run_time.push_back({"Quick Sort", quickSort_duration.count()});
    run_time.push_back({"Merge Sort", mergeSort_duration.count()});
    run_time.push_back({"Counting Sort", countingSort_duration.count()});
    run_time.push_back({"Radix Sort", radixSort_duration.count()});

    for (int i = 0; i < run_time.size() - 1; i++)
    {
        for (int j = 0; j < run_time.size() - i - 1; j++)
        {
            if (run_time[j].second > run_time[j + 1].second)
            {
                swap(run_time[j], run_time[j + 1]);
            }
        }
    }

    cout << "The fastest algorithm: " << run_time[0].first << "\n";
    cout << "The slowest algorithm: " << run_time[run_time.size() - 1].first << "\n";

    return 0;
}