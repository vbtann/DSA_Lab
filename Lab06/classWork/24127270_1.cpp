#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
};

Node *newNode(int data)
{
    Node *node = new Node;
    node->key = data;
    node->left = nullptr;
    node->right = nullptr;

    return node;
}

Node *insert(Node *root, int data)
{
    if (!root)
    {
        return newNode(data);
    }
    if (data > root->key)
    {
        root->right = insert(root->right, data);
        // return insert(root->right, data);
    }
    else if (data < root->key)
    {
        root->left = insert(root->left, data);
        // return insert(root->left, data);
    }

    return root;
}

Node *search(Node *root, int data)
{
    if (!root)
    {
        return nullptr;
    }

    if (root->key == data)
    {
        return root;
    }
    else
    {
        if (data > root->key)
        {
            return search(root->right, data);
        }
        else
        {
            return search(root->left, data);
        }
    }

    return nullptr;
}

Node *deleteNode(Node *root, int data) // Couldn't use "delete" as the functions's name because it conflict with C++ statement
{
    if (!root)
    {
        return nullptr;
    }

    if (data > root->key)
    {
        root->right = deleteNode(root->right, data);
    }
    else if (data < root->key)
    {
        root->left = deleteNode(root->left, data);
    }
    else
    {
        // Node with no child
        if (!root->left && !root->right)
        {
            delete root;
            return nullptr;
        }

        // Node with one child
        else if (!root->right)
        {
            Node *tmp = root->left;
            delete root;
            return tmp;
        }
        else if (!root->left)
        {
            Node *tmp = root->right;
            delete root;
            return tmp;
        }

        // Node with two children
        Node *tmp = root->right;
        while (tmp && tmp->left)
        {
            tmp = tmp->left;
        }
        root->key = tmp->key;
        root->right = deleteNode(root->right, tmp->key);
    }
    return root;
}

void NLR(Node *root) // Preorder
{
    if (!root)
    {
        return;
    }
    cout << root->key << ' ';
    if (root->left != nullptr)
    {
        NLR(root->left);
    }
    if (root->right != nullptr)
    {
        NLR(root->right);
    }
}

void LNR(Node *root) // Inorder
{
    if (!root)
    {
        return;
    }
    if (root->left != nullptr)
    {
        LNR(root->left);
    }
    cout << root->key << ' ';
    if (root->right != nullptr)
    {
        LNR(root->right);
    }
}

void LRN(Node *root) // Postorder
{
    if (!root)
    {
        return;
    }
    if (root->left != nullptr)
    {
        LRN(root->left);
    }
    if (root->right != nullptr)
    {
        LRN(root->right);
    }
    cout << root->key << ' ';
}

void levelOrder(Node *root)
{
    if (!root)
    {
        return;
    }
    queue<Node *> nodeQ;
    nodeQ.push(root);

    while (!nodeQ.empty())
    {
        Node *cur = nodeQ.front();
        nodeQ.pop();
        cout << cur->key << ' ';

        if (cur->left != nullptr)
        {
            nodeQ.push(cur->left);
        }
        if (cur->right != nullptr)
        {
            nodeQ.push(cur->right);
        }
    }
}

int main(void)
{
    int n = 7;
    Node *root = nullptr;
    for (int i = 1; i <= n; i++)
    {
        root = insert(root, i);
    }
    cout << "Before deletion:\n";
    cout << "NLR: ";
    NLR(root);
    cout << "\n";

    cout << "LNR: ";
    LNR(root);
    cout << "\n";

    cout << "LRN: ";
    LRN(root);
    cout << "\n";

    cout << "Level order: ";
    levelOrder(root);
    cout << "\n";

    deleteNode(root, 6);
    cout << "\nAfter deletion:\n";
    cout << "NLR: ";
    NLR(root);
    cout << "\n";

    cout << "LNR: ";
    LNR(root);
    cout << "\n";

    cout << "LRN: ";
    LRN(root);
    cout << "\n";

    cout << "Level order: ";
    levelOrder(root);
    cout << "\n";
    return 0;
}