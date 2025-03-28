#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int data, Node *next) : data(data), next(next) {};
};

struct List
{
    Node *head;
};

void createList(List &ls)
{
    ls.head = new Node(1, nullptr);
    Node *cur = ls.head;
    for (int i = 2; i <= 5; i++)
    {
        cur->next = new Node(4, nullptr);
        cur = cur->next;
    }
}

void deleteList(List &ls)
{
    if (ls.head == nullptr)
    {
        cout << "Delete failed..! List is empty..!\n";
    }

    Node *next = nullptr;
    Node *cur = ls.head;

    while (cur != nullptr)
    {
        next = cur->next;
        delete cur;
        cur = next;
    }
}

bool traversalNode(List ls)
{
    if (ls.head == nullptr)
    {
        return 0;
    }

    for (Node *cur = ls.head; cur != nullptr; cur = cur->next)
    {
        cout << cur->data << ' ';
    }
    cout << "\n";
    return 1;
}

int countNode(List ls)
{
    int count = 0;
    if (ls.head == nullptr)
    {
        return 0;
    }

    for (Node *cur = ls.head; cur != nullptr; cur = cur->next)
    {
        count++;
    }
    return count;
}

bool addHead(List &ls, int _data)
{
    Node *newNode = new Node(_data, nullptr);
    if (ls.head != nullptr)
    {
        newNode->next = ls.head;
        ls.head = newNode;
    }
    else
    {
        ls.head = newNode;
    }
    return 1;
}

bool addTail(List &ls, int _data)
{
    if (ls.head == nullptr)
    {
        ls.head = new Node(_data, nullptr);
        return 1;
    }

    Node *tail = ls.head;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }

    tail->next = new Node(_data, nullptr);
    return 1;
}

bool removeHead(List &ls)
{
    if (ls.head == nullptr)
    {
        return 0;
    }

    Node *cur = ls.head;
    ls.head = ls.head->next;
    delete cur;

    return 1;
}

bool removeTail(List &ls)
{
    if (ls.head == nullptr)
    {
        return 0;
    }

    Node *tail = ls.head;
    while (tail->next->next != nullptr)
    {
        tail = tail->next;
    }

    Node *cur = tail->next;
    tail->next = nullptr;
    delete cur;

    return 1;
}

bool removeDuplicate(List &ls)
{
    if (ls.head == nullptr || ls.head->next == nullptr)
    {
        return 0;
    }

    Node *prev = ls.head;
    while (prev != nullptr)
    {
        Node *cur = prev;
        while (cur != nullptr && cur->next != nullptr)
        {
            if (prev->data == cur->next->data)
            {
                Node *tmp = cur->next;
                cur->next = tmp->next;
                delete tmp;
            }
            else
            {
                cur = cur->next;
            }
        }
        prev = prev->next;
    }
    return 1;
}

int main()
{
    List ls;
    // Create a linked list
    createList(ls);

    // Add head to linked list
    if (addHead(ls, 9))
    {
        cout << "Head added successfully..!\n";
    }

    // Add tail to linked list
    if (addTail(ls, 10))
    {
        cout << "Tail added successfully..!\n";
    }

    // Remove head of linked list
    if (removeHead(ls))
    {
        cout << "Head removed successfully..!\n";
    }
    else
    {
        cout << "Failed to remove head..!\n";
    }

    // Remove tail of linked list
    if (removeTail(ls))
    {
        cout << "Tail removed successfully..!\n";
    }
    else
    {
        cout << "Failed to remove tail..!\n";
    }

    // Remove duplicated nodes in linked list
    if (removeDuplicate(ls))
    {
        cout << "Duplicated nodes removed successfully..!\n";
    }
    else
    {
        cout << "There is nothing to remove from the list..!\n";
    }

    // Print list to console
    if (traversalNode(ls))
    {
        cout << "Traverse successfully..!\n";
    }

    // Free up memory
    deleteList(ls);
    return 0;
}