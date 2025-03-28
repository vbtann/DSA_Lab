#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int elementCnt;
vector<int> numbers, vec;
bool used[(int)1e8];

void printSet(vector<int> vec)
{
    for (int x : vec)
    {
        cout << x << ' ';
    }
    cout << "\n";
}

void createPermutation(int ind)
{
    if (ind == elementCnt)
    {
        printSet(vec);
        return;
    }

    for (int i = 0; i < elementCnt; i++)
    {
        if (!used[numbers[i]])
        {
            used[numbers[i]] = 1;
            vec.push_back(numbers[i]);
            createPermutation(ind + 1);
            vec.pop_back();
            used[numbers[i]] = 0;
        }
    }
}

int main()
{
    cin >> elementCnt;
    memset(used, 0, sizeof(used));
    for (int i = 0; i < elementCnt; i++)
    {
        int tmp;
        cin >> tmp;
        numbers.push_back(tmp);
    }
    createPermutation(0);
    return 0;
}