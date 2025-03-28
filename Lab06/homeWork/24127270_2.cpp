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

int height(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return max(height(root->left), height(root->right)) + 1;
}

int countNode(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return countNode(root->left) + countNode(root->right) + 1;
}

int countInternalNode(Node *root)
{
    if (root == nullptr || (root->left == nullptr && root->right == nullptr))
    {
        return 0;
    }

    return countInternalNode(root->left) + countInternalNode(root->right) + 1;
}

int sumNode(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return root->key + sumNode(root->left) + sumNode(root->right);
}

int countLeaf(Node *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    if (root->right == nullptr && root->left == nullptr)
    {
        return 1;
    }

    return countLeaf(root->left) + countLeaf(root->right);
}

int countLess(Node *root, int x)
{
    if (root == nullptr)
    {
        return 0;
    }

    int cur = (root->key < x) ? 1 : 0;
    return cur + countLess(root->left, x) + countLess(root->right, x);
}

int countGreater(Node *root, int x)
{
    if (root == nullptr)
    {
        return 0;
    }
    int cur = (root->key > x) ? 1 : 0;

    return cur + countGreater(root->left, x) + countGreater(root->right, x);
}

int main(void)
{
    // Initialize empty BST
    Node *root = nullptr;

    // Insert data
    root = insert(root, 8);
    root = insert(root, 6);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 10);
    root = insert(root, 9);

    // Pre-order
    cout << "Pre-order: ";
    NLR(root);
    cout << "\n";

    // In-order
    cout << "In-order: ";
    LNR(root);
    cout << "\n";

    // Post-order
    cout << "Post-order: ";
    LRN(root);
    cout << "\n";

    // Remove 8
    root = deleteNode(root, 8);
    // Level order
    cout << "Level order: ";
    levelOrder(root);
    cout << "\n";

    // Solve exercise 2 problems with x = 7
    int x = 7;
    cout << "height: " << height(root) << "\n";
    cout << "count node: " << countNode(root) << "\n";
    cout << "count internal node: " << countInternalNode(root) << "\n";
    cout << "sum node: " << sumNode(root) << "\n";
    cout << "count leaf: " << countLeaf(root) << "\n";
    cout << "count less: " << countLess(root, x) << "\n";
    cout << "count greater: " << countGreater(root, x) << "\n";
    return 0;
}