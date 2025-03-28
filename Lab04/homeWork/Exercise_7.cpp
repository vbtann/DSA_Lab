#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#define fi first
#define se second

using namespace std;

struct STUDENT
{
    string name;
    double test_1, test_2;
    double avg_score;
    vector<int> refOptions;
    int assignedOptions;

    STUDENT() : assignedOptions(-1) {}
};

int optionCnt;
vector<int> maxPerOption;
vector<STUDENT> studentList;
vector<vector<STUDENT>> assignedList;
vector<STUDENT> rejected;

void readInput(const string &filename)
{
    fstream cin(filename, ios::in);

    cin >> optionCnt;

    maxPerOption.resize(optionCnt + 1);

    for (int i = 1; i <= optionCnt; i++)
    {
        int tmp;
        cin >> tmp >> maxPerOption[i];
    }

    cin.ignore();

    string line;
    while (getline(cin, line))
    {
        if (line.empty())
        {
            continue;
        }

        STUDENT s;

        string token;
        stringstream ss(line);
        getline(ss, token, ',');
        token = token.substr(1);
        token.pop_back();
        s.name = token;

        getline(ss, token, ',');
        stringstream(token) >> s.test_1;

        getline(ss, token, ',');
        stringstream(token) >> s.test_2;

        s.avg_score = (s.test_1 + s.test_2) / 2.0;

        while (getline(ss, token, ','))
        {
            int tmp;
            stringstream(token) >> tmp;
            s.refOptions.push_back(tmp);
        }

        studentList.push_back(s);
    }

    cin.close();
}

bool compareStudents(const STUDENT &a, const STUDENT &b)
{
    if (a.avg_score != b.avg_score)
    {
        return a.avg_score > b.avg_score;
    }
    if (a.test_1 != b.test_1)
    {
        return a.test_1 > b.test_1;
    }
    if (a.test_2 != b.test_2)
    {
        return a.test_2 > b.test_2;
    }
    return 0;
}

void quickSort(vector<STUDENT> &sList, int left, int right)
{
    if (left >= right)
        return;
    STUDENT pivot = sList[left];
    int i = left, j = right;
    while (i <= j)
    {
        while (compareStudents(sList[i], pivot))
            i++;
        while (compareStudents(pivot, sList[j]))
            j--;

        if (i <= j)
        {
            swap(sList[i], sList[j]);
            i++;
            j--;
        }
    }
    if (left < j)
    {
        quickSort(sList, left, j);
    }
    if (i < right)
    {
        quickSort(sList, i, right);
    }
}

void assignStudents(vector<STUDENT> &students, const vector<int> &maxPerOption)
{
    assignedList.resize(optionCnt + 1);
    vector<int> currentStudentPerOption(maxPerOption.size());
    for (STUDENT &s : students)
    {
        for (int opt : s.refOptions)
        {
            if (currentStudentPerOption[opt] < maxPerOption[opt])
            {
                currentStudentPerOption[opt]++;
                s.assignedOptions = opt;
                assignedList[opt].push_back(s);
                break;
            }
            else if (currentStudentPerOption[opt] >= maxPerOption[opt])
            {
                STUDENT cur = assignedList[opt][assignedList[opt].size() - 1];
                if (!compareStudents(cur, s))
                {
                    currentStudentPerOption[opt]++;
                    s.assignedOptions = opt;
                    assignedList[opt].push_back(s);
                    break;
                }
            }
        }
    }

    for (STUDENT s : students)
    {
        if (s.assignedOptions == -1)
        {
            rejected.push_back(s);
        }
    }
}

void print(vector<vector<STUDENT>> stu)
{
    for (int i = 1; i <= optionCnt; i++)
    {
        cout << "Successful candidates for option " << i << "\n";
        int count = 1;
        for (STUDENT s : stu[i])
        {
            cout << fixed << setprecision(2) << count << ". " << s.name << ' ' << s.avg_score << "\n";
            count++;
        }
    }

    cout << "Unsuccessful candidates\n";
    int count = 1;
    for (STUDENT s : rejected)
    {
        cout << fixed << setprecision(2) << count << ". " << s.name << ' ' << s.avg_score << "\n";
        count++;
    }
}

int main(void)
{
    readInput("exam.txt");
    quickSort(studentList, 0, studentList.size() - 1);
    assignStudents(studentList, maxPerOption);
    print(assignedList);
    // for (STUDENT s : studentList)
    // {
    //     cout << fixed << setprecision(2) << s.name << ' ' << s.avg_score << '\n';
    // }
    return 0;
}