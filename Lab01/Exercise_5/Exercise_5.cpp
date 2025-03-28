#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int x, Node *n) : data(x), next(n) {};
};

struct Stack
{
    Node *top;
    Stack() : top(nullptr) {}
};

void push(Stack &st, int _data)
{
    st.top = new Node(_data, st.top);
}

bool pop(Stack &st)
{
    if (st.top == nullptr)
    {
        return 0;
    }

    Node *cur = st.top;
    st.top = st.top->next;
    delete cur;
    return 1;
}

int top(Stack st)
{
    if (st.top == nullptr)
    {
        cout << "Stack is empty..!\n";
    }

    return st.top->data;
}

int main()
{
    Stack st;
    push(st, 1);
    push(st, 2);
    push(st, 3);

    cout << top(st) << "\n";
    if (pop(st))
    {
        cout << "Pop successfully..!\n"
             << top(st) << "\n";
    }
    return 0;
}