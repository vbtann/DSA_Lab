#include <iostream>
#include <fstream>

using namespace std;

bool readMatrix(const char *filename, int **&matrix, int &rows, int &cols)
{
    fstream cin(filename, ios::in);
    if (!cin.is_open())
    {
        return 0;
    }

    cin >> rows >> cols;

    matrix = new int *[rows];
    for (int i = 0; i < rows; i++)
    {
        matrix[i] = new int[cols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!(cin >> matrix[i][j]))
            {
                return 0;
            }
        }
    }
    cin.close();
    return 1;
}

void printMatrix(const char *filename, int **matrix, int rows, int cols)
{
    fstream cout(filename, ios::out);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << matrix[i][j] << ' ';
        }
        cout << "\n";
    }
}

bool multiplyMatricies(int **a, int aRows, int aCols, int **b, int bRows, int bCols, int **&res, int &resRows, int &resCols)
{
    if (aCols != bRows)
    {
        cout << aCols << ' ' << bRows << "\n";
        return 0;
    }

    resRows = aRows;
    resCols = bCols;

    res = new int *[resRows];
    for (int i = 0; i < resRows; i++)
    {
        res[i] = new int[resCols];
    }

    for (int i = 0; i < resRows; i++)
    {
        for (int j = 0; j < resCols; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < aRows; k++)
            {
                res[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return 1;
}

void transposeMatrix(int **matrix, int rows, int cols, int **&res, int &resRows, int &resCols)
{
    resRows = cols;
    resCols = rows;
    res = new int *[resRows];
    for (int i = 0; i < resRows; i++)
    {
        res[i] = new int[resCols];
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            res[j][i] = matrix[i][j];
        }
    }
}

void releaseMemory(int **&arr, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;
}

int main()
{
    // Input matrix a
    int **a, aRows, aCols;
    readMatrix("matrix_a.txt", a, aRows, aCols);

    // Input matrix b
    int **b, bRows, bCols;
    readMatrix("matrix_b.txt", b, bRows, bCols);

    // Multiply a * b -> c
    int **c, cRows, cCols;
    if (multiplyMatricies(a, aRows, aCols, b, bRows, bCols, c, cRows, cCols))
    {
        cout << "Multiply successful!\n";
        printMatrix("matrix_c.txt", c, cRows, cCols);
    }
    else
    {
        cout << "Multiply failed!\n";
    }

    // Calculate the transpose of matrix c
    int **cTransposed, cTransposedRows, cTransposedCols;
    transposeMatrix(c, cRows, cCols, cTransposed, cTransposedRows, cTransposedCols);
    printMatrix("matrix_c_transposed.txt", cTransposed, cTransposedRows, cTransposedCols);
    return 0;
}