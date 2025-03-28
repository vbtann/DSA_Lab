#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>
#include <algorithm>

using namespace std;

struct employee
{
    long id;
    string name;
    long birth_year;
    int age;
};

int getCurrentYear()
{
    time_t now = time(nullptr);
    struct tm *ltm = localtime(&now);
    return 1900 + ltm->tm_year;
}

vector<employee> employeeData;

long birth_year_process(long birth)
{
    if (birth > 3000)
    {
        birth = (birth % 100);
        if (birth < 5)
        {
            birth += 2000;
        }
        else
        {
            birth += 1900;
        }
    }
    return birth;
}

void inputData(vector<employee> &employee_data)
{
    int currentYear = getCurrentYear();

    fstream in("employee.txt", ios::in);
    string line;
    getline(in, line);
    while (getline(in, line))
    {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        long id = stol(token);
        getline(ss, token, ',');
        string name = token;
        getline(ss, token, ',');
        long birth = stol(token);

        int age = currentYear - birth;
        birth = birth_year_process(birth);
        employee_data.push_back({id, name, birth, age});
    }
}

void insertionSort(vector<employee> &data)
{
    for (int i = 1; i < data.size(); i++)
    {
        employee key = data[i];
        int j = i - 1;
        while (j >= 0 && (data[j].age < key.age ||
                          (data[j].age == key.age && data[j].name > key.name)))
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

void selectionSort(vector<employee> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
    {
        int maxIndex = i;
        for (int j = i + 1; j < data.size(); j++)
        {
            if (data[j].age > data[maxIndex].age ||
                (data[j].age == data[maxIndex].age &&
                 data[j].name < data[maxIndex].name))
            {
                maxIndex = j;
            }
        }
        if (maxIndex != i)
        {
            swap(data[i], data[maxIndex]);
        }
    }
}

void interchangeSort(vector<employee> &data)
{
    for (int i = 0; i < data.size() - 1; i++)
    {
        for (int j = i + 1; j < data.size(); j++)
        {
            if (data[i].age < data[j].age ||
                (data[i].age == data[j].age &&
                 data[i].name > data[j].name))
            {
                swap(data[i], data[j]);
            }
        }
    }
}

void writeToFile(const vector<employee> &data)
{
    ofstream out("sortedemponage.txt");
    out << "ID,Name,Birth Year\n";
    for (const auto &emp : data)
    {
        out << emp.id << "," << emp.name << ","
            << emp.birth_year << "\n";
    }
    out.close();
}

int main(void)
{
    inputData(employeeData);

    cout << "Choose sorting algorithm:\n";
    cout << "1. Insertion Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Interchange Sort\n";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        insertionSort(employeeData);
        cout << "Used Insertion Sort\n";
        break;
    case 2:
        selectionSort(employeeData);
        cout << "Used Selection Sort\n";
        break;
    case 3:
        interchangeSort(employeeData);
        cout << "Used Interchange Sort\n";
        break;
    default:
        cout << "Invalid choice\n";
        return 1;
    }

    writeToFile(employeeData);
    cout << "Sorted data written to sortedemponage.txt\n";

    return 0;
}