#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

string filename = "English-Vietnamese Dictionary.txt";

struct WORD
{
    string word;
    string definition;
};

vector<WORD> wordSet;

string binarySearch(string str)
{
    int l = 0;
    int r = wordSet.size() - 1;
    while (l <= r)
    {
        int mid = (l + r) / 2;

        if (strcmp(str.c_str(), wordSet[mid].word.c_str()) == 0)
        {
            return wordSet[mid].definition;
        }
        else if (strcmp(str.c_str(), wordSet[mid].word.c_str()) < 0)
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }
    return "Word not found..!";
}

int main(int argc, char *argv[])
{
    freopen(filename.c_str(), "r", stdin);
    freopen(argv[argc - 1], "w", stdout);

    string str;

    while (getline(cin, str))
    {
        WORD w;
        stringstream ss(str);
        getline(ss, w.word, ':');
        getline(ss, w.definition);
        if (w.definition[0] == ' ')
        {
            w.definition.erase(0, 1);
        }

        wordSet.push_back(w);
    }

    for (int i = 1; i <= argc - 2; i++)
    {
        string def = binarySearch(argv[i]);
        cout << argv[i] << ": " << def << "\n";
    }

    return 0;
}