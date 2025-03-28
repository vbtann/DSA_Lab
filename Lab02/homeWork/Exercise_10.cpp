#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int queenCount;
int taken[15][15];
vector<int> pos;
vector<vector<int>> posSet;

bool isValid(int x, int y)
{
    return x >= 1 && x <= queenCount && y >= 1 && y <= queenCount;
}

void printRes(vector<vector<int>> pos)
{
    for (vector<int> x : pos)
    {
        cout << "[";
        for (int i = 0; i < x.size(); i++)
        {
            cout << x[i];
            if (i < x.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << "]\n";
    }
}

void fillPos(int x, int y, int val)
{
    for (int i = 1; i <= queenCount; i++)
    {
        taken[i][y] += val;
        taken[x][i] += val;
    }

    for (int k = 1; k <= queenCount; k++)
    {
        if (isValid(x - k, y - k))
        {
            taken[x - k][y - k] += val;
        }
        if (isValid(x + k, y - k))
        {
            taken[x + k][y - k] += val;
        }
        if (isValid(x - k, y + k))
        {
            taken[x - k][y + k] += val;
        }
        if (isValid(x + k, y + k))
        {
            taken[x + k][y + k] += val;
        }
    }
}

void print()
{
    for (int i = 1; i <= queenCount; i++)
    {
        for (int j = 1; j <= queenCount; j++)
        {
            cout << taken[i][j] << ' ';
        }
        cout << "\n";
    }
}

void placeQueen(int row)
{
    if (row == queenCount + 1)
    {
        // vector<int> solution = pos;
        posSet.push_back(pos);
        return;
    }

    // bool tmpTaken[15][15];
    // memcpy(tmpTaken, taken, sizeof(taken));

    for (int col = 1; col <= queenCount; col++)
    {
        if (taken[row][col] == 0)
        {
            pos.push_back(col);
            fillPos(row, col, 1);
            placeQueen(row + 1);
            pos.pop_back();
            fillPos(row, col, -1);
            // memcpy(taken, tmpTaken, sizeof(tmpTaken));
        }
    }
}

int main(void)
{
    cin >> queenCount;
    memset(taken, 0, sizeof(taken));
    placeQueen(1);

    if (posSet.size() > 0)
    {
        printRes(posSet);
    }
    else
    {
        cout << "No valid solution found!\n";
    }
    return 0;
}