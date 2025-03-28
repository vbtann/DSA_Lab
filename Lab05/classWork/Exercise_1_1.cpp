#include <iostream>
#include <vector>

using namespace std;

const int p = 31;
const int m = (int)1e9 + 9;

struct hashTable
{
    struct hashNode
    {
        string key;
        int val;

        hashNode(string k, int v) : key(k), val(v) {}
    };

    int capacity;
    vector<hashNode *> table;

    void init(unsigned int hashSize)
    {
        capacity = hashSize;
        table.resize(capacity, nullptr);
    }

    void release()
    {
        for (int i = 0; i < capacity; i++)
        {
            delete table[i];
            table[i] = nullptr;
        }
    }

    unsigned int hashFunction(string key)
    {
        unsigned int tmp, powP = 1;
        for (int i = 0; i < key.length(); i++)
        {
            tmp += ((key[i] - '0') * powP);
            powP *= p;
        }

        return (tmp % m) % capacity;
    }

    void add(string key, int val)
    {
        unsigned int ind = hashFunction(key);

        for (int i = 0; i < capacity; i++)
        {
            unsigned int curInd = (ind + i) % capacity;

            if (table[curInd] == nullptr)
            {
                table[curInd] = new hashNode(key, val);
                return;
            }

            if (table[curInd]->key == key)
            {
                table[curInd]->val = val;
                return;
            }
        }
    }

    int *searchValue(string key)
    {
        unsigned int ind = hashFunction(key);

        for (int i = 0; i < capacity; i++)
        {
            unsigned int curInd = (ind + i) % capacity;

            if (table[curInd] == nullptr)
            {
                return nullptr;
            }

            if (table[curInd]->key == key)
            {
                return &(table[curInd]->val);
            }
        }
        return nullptr;
    }

    void removeKey(string key)
    {
        unsigned int ind = hashFunction(key);

        for (int i = 0; i < capacity; i++)
        {
            unsigned int curInd = (ind + i) % capacity;

            if (table[curInd] == nullptr)
            {
                return;
            }

            if (table[curInd]->key == key)
            {
                delete table[curInd];
                table[curInd] = nullptr;
                return;
            }
        }
    }
};

int main(void)
{
    hashTable hT;
    hT.init(5);
    hT.add("a", 10);
    hT.add("b", 20);
    hT.add("c", 30);
    hT.add("d", 40);
    hT.add("e", 50);

    cout << *(hT.searchValue("e")) << "\n";
    hT.removeKey("e");
    hT.add("f", 60);
    cout << *hT.searchValue("f") << "\n";

    for (int i = 0; i < 5; i++)
    {
        cout << hT.table[i]->key << ' ' << hT.table[i]->val << "\n";
    }
    hT.release();
    return 0;
}