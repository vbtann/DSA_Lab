#include <iostream>
#include <string>

using namespace std;

void removeExtraSpace(string &str)
{
    // Remove leading spaces
    int i = 0;
    while (str[i] == ' ')
    {
        str.erase(i, 1);
    }

    // Remove tailing spaces
    i = str.length() - 1;
    while (str[i] == ' ')
    {
        str.erase(i, 1);
        i--;
    }

    // Remove all extra spaces between word
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ' && (str[i + 1] == ' ' || ispunct(str[i + 1])))
        {
            str.erase(i, 1);
            i--;
        }
    }
}

int wordCount(string str)
{
    int count = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            count++;
        }
    }
    return count + 1;
}

string findLongestWord(string str)
{
    string longestWord = "";
    int maxLen = 0;
    int i = 0;
    while (i < str.length())
    {
        if (isalpha(str[i]))
        {
            string tmp = "";
            int j = i;
            int len = 0;
            while (isalpha(str[j]))
            {
                tmp += str[j];
                len++;
                j++;
            }
            if (len > maxLen)
            {
                longestWord = tmp;
                maxLen = len;
            }
            i = j;
        }
        else
        {
            i++;
        }
    }
    return longestWord;
}

int main()
{
    string inputStr;
    getline(cin, inputStr);
    removeExtraSpace(inputStr);
    cout << "Normalized paragraph: \n"
         << inputStr << "\n";

    cout << "Word count: " << wordCount(inputStr) << "\n";

    cout << "Longest word: " << findLongestWord(inputStr);
    return 0;
}