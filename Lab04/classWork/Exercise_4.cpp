#include <iostream>
#include <vector>

using namespace std;

void printMatrix(vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            cout << val << ' ';
        }
        cout << endl;
    }
}

void selectionSort(vector<int> &arr)
{
    for (int i = 0; i < arr.size() - 1; i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < arr.size(); j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
        if (minIdx != i)
        {
            swap(arr[i], arr[minIdx]);
        }
    }
}

void spiralSort(vector<vector<int>> &matrix)
{
    int m = matrix.size();
    if (m == 0)
        return;
    int n = matrix[0].size();

    vector<int> temp;
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            temp.push_back(val);
        }
    }

    selectionSort(temp);

    int index = 0;
    int top = 0, bottom = m - 1, left = 0, right = n - 1;

    while (index < m * n)
    {
        for (int i = left; i <= right && index < m * n; i++)
        {
            matrix[top][i] = temp[index++];
        }
        top++;

        for (int i = top; i <= bottom && index < m * n; i++)
        {
            matrix[i][right] = temp[index++];
        }
        right--;

        for (int i = right; i >= left && index < m * n; i--)
        {
            matrix[bottom][i] = temp[index++];
        }
        bottom--;

        for (int i = bottom; i >= top && index < m * n; i--)
        {
            matrix[i][left] = temp[index++];
        }
        left++;
    }
}

int main(void)
{
    int rows, cols;
    cin >> rows >> cols;

    vector<vector<int>> matrix(rows, vector<int>(cols));

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cin >> matrix[i][j];
        }
    }

    cout << "\nOriginal Matrix:" << endl;
    printMatrix(matrix);

    spiralSort(matrix);

    cout << "\nSpiral Sorted Matrix:" << endl;
    printMatrix(matrix);

    return 0;
}