#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int x, Node *n) : data(x), next(n) {};
};

struct Queue
{
    Node *front;
    Queue() : front(nullptr) {}
};

void enqueue(Queue &qu, int _data)
{
    Node *newNode = new Node(_data, nullptr);

    if (qu.front == nullptr)
    {
        qu.front = newNode;
        return;
    }

    Node *tail = qu.front;
    while (tail->next != nullptr)
    {
        tail = tail->next;
    }
    tail->next = newNode;
}

bool dequeue(Queue &qu)
{
    if (qu.front == nullptr)
    {
        return 0;
    }

    Node *tmpFront = qu.front;
    qu.front = qu.front->next;
    delete tmpFront;
    return 1;
}

int front(Queue &qu)
{
    if (qu.front == nullptr)
    {
        cout << "Queue is empty..!\n";
    }

    return qu.front->data;
}

int main()
{
    Queue qu;
    enqueue(qu, 1);
    enqueue(qu, 2);
    enqueue(qu, 3);

    if (dequeue(qu))
    {
        cout << "Dequeued the front item successfully..!\n";
    }
    else
    {
        cout << "Failed to dequeue the front item..!\n";
    }

    cout << "Current front item: " << front(qu);
    return 0;
}