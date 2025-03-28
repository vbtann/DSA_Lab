#include <iostream>
#include <vector>

using namespace std;

const int m = (int)1e9 + 9;
const int p = 31;

struct hashTable
{
    struct hashNode
    {
        string key;
        int val;
        hashNode *next;
    };

    int capacity;
    vector<hashNode *> table;

    void init(unsigned int hashSize)
    {
        capacity = hashSize;
        table.resize(hashSize, nullptr);
    }

    void release()
    {
        for (int i = 0; i < capacity; i++)
        {
            hashNode *cur = table[i];
            while (cur != nullptr)
            {
                hashNode *tmp = cur;
                cur = cur->next;
                delete tmp;
            }
            table[i] = nullptr;
        }
    }

    bool isInvalid(hashNode *node)
    {
        return (node == nullptr);
    }

    unsigned int hashFunction(string key)
    {
        unsigned int tmp = 0, pPow = 1;
        for (int i = 0; i < key.length(); i++)
        {
            tmp += ((key[i] - '0') * pPow);
            pPow *= p;
        }
        return (tmp % m) % capacity;
    }

    void add(string key, int value)
    {
        unsigned int ind = hashFunction(key);

        hashNode *cur = table[ind];
        while (cur != nullptr)
        {
            if (cur->key == key)
            {
                cur->val = value;
                return;
            }
            cur = cur->next;
        }

        hashNode *newNode = new hashNode;
        newNode->key = key;
        newNode->val = value;

        newNode->next = table[ind];
        table[ind] = newNode;
    }

    int *searchValue(string key)
    {
        unsigned int ind = hashFunction(key);
        hashNode *cur = table[ind];

        while (cur != nullptr)
        {
            if (cur->key == key)
            {
                return &(cur->val);
            }
            cur = cur->next;
        }

        return nullptr;
    }

    void removeKey(string key)
    {
        unsigned int ind = hashFunction(key);
        hashNode *cur = table[ind];
        hashNode *prev = nullptr;

        while (cur != nullptr)
        {
            if (cur->key == key)
            {
                if (prev == nullptr)
                {
                    table[ind] = cur->next;
                }
                else
                {
                    prev->next = cur->next;
                }

                delete cur;
                return;
            }

            prev = cur;
            cur = cur->next;
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
        if (hT.table[i] != nullptr)
        {
            cout << hT.table[i]->key << ' ' << hT.table[i]->val << "\n";
        }
        else
        {
            cout << "Buket " << i << ": Empty\n";
        }
    }
    hT.release();
    return 0;
}