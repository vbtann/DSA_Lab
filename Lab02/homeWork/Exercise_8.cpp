#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int elementCnt;
vector<int> nums;
vector<int> currentSubSet;
vector<vector<int>> storeSubSets;
bool used[(int)1e8];

void printSubSet()
{
    // cout << "{";
    for (int x : currentSubSet)
    {
        cout << x << ", ";
    }
    cout << "\n";
    // cout << "}\n";
}

void print()
{
    for (vector<int> x : storeSubSets)
    {
        cout << "{";
        for (int i = 0; i < x.size(); i++)
        {
            cout << x[i];
            if (i < x.size() - 1)
            {
                cout << ",";
            }
        }
        cout << "}";
        cout << "\n";
    }
}

bool cmp(vector<int> a, vector<int> b)
{
    if (a.size() == b.size())
    {
        return a < b;
    }
    else
    {
        return a.size() < b.size();
    }
}

void subsetGenerate(int pos)
{
    if (pos == elementCnt)
    {
        storeSubSets.push_back(currentSubSet);
        // printSubSet();
        return;
    }

    subsetGenerate(pos + 1);

    currentSubSet.push_back(nums[pos]);
    subsetGenerate(pos + 1);
    currentSubSet.pop_back();
}

int main()
{
    cin >> elementCnt;
    for (int i = 0; i < elementCnt; i++)
    {
        int tmp;
        cin >> tmp;
        nums.push_back(tmp);
    }

    subsetGenerate(0);
    sort(storeSubSets.begin(), storeSubSets.end(), cmp);
    print();
    return 0;
}