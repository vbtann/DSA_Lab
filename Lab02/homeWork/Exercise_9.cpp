#include <iostream>
#include <vector>

using namespace std;

int binStrLen;
vector<int> binStr;
vector<vector<int>> binStrSet;

void printSet(vector<vector<int>> vec)
{
    for (vector<int> x : vec)
    {
        for (int y : x)
        {
            cout << y;
        }
        cout << "\n";
    }
}

void createBinStr(int len)
{
    if (binStr.size() == len)
    {
        binStrSet.push_back(binStr);
        return;
    }

    for (int i = 0; i <= 1; i++)
    {
        binStr.push_back(i);
        createBinStr(len);
        binStr.pop_back();
    }
}

int main()
{
    cin >> binStrLen;
    createBinStr(binStrLen);
    printSet(binStrSet);

    return 0;
}