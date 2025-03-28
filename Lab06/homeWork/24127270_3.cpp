#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
    int height;
};

Node *newNode(int data)
{
    Node *tmp = new Node;
    tmp->key = data;
    tmp->right = nullptr;
    tmp->left = nullptr;
    tmp->height = 1;
    return tmp;
}

int getHeight(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }
    return node->height;
}

int getBalance(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return getHeight(node->left) - getHeight(node->right);
}

Node *rightRotate(Node *root)
{
    Node *left = root->left;
    Node *lRight = left->right;

    left->right = root;
    root->left = lRight;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    left->height = max(getHeight(left->left), getHeight(left->right)) + 1;

    return left;
}

Node *leftRotate(Node *root)
{
    Node *right = root->right;
    Node *rLeft = right->left;

    right->left = root;
    root->right = rLeft;

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    right->height = max(getHeight(right->left), getHeight(right->right)) + 1;

    return right;
}

Node *insertNode(Node *root, int data)
{
    if (root == nullptr)
    {
        return newNode(data);
    }

    if (data > root->key)
    {
        root->right = insertNode(root->right, data);
    }
    else if (data < root->key)
    {
        root->left = insertNode(root->left, data);
    }
    else
    {
        return root;
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balanceFactor = getBalance(root);

    if (balanceFactor > 1 && data < root->left->key)
    {
        return rightRotate(root);
    }
    if (balanceFactor < -1 && data > root->right->key)
    {
        return leftRotate(root);
    }
    if (balanceFactor > 1 && data > root->left->key)
    {
        root->left = leftRotate(root);
        return rightRotate(root);
    }
    if (balanceFactor < -1 && data < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *searchNode(Node *root, int data)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->key == data)
    {
        return root;
    }
    else
    {
        if (root->key > data)
        {
            return searchNode(root->left, data);
        }
        else if (root->key < data)
        {
            return searchNode(root->right, data);
        }
    }

    return nullptr;
}

Node *deleteNode(Node *root, int data)
{
    if (root == nullptr)
    {
        return root;
    }

    if (data < root->key)
    {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->key)
    {
        root->right = deleteNode(root->right, data);
    }
    else
    {
        // Node with no child or only one child case
        if (root->left == nullptr || root->right == nullptr)
        {
            Node *tmp = (root->left) ? root->left : root->right;

            // No child
            if (tmp == nullptr)
            {
                tmp = root;
                root = nullptr;
            }

            // One child
            else
            {
                *root = *tmp;
            }
            delete tmp;
        }

        // Node with 2 children case
        else
        {
            // Get the successor of root
            Node *tmpRight = root->right;
            while (tmpRight->left != nullptr)
            {
                tmpRight = tmpRight->left;
            }

            root->key = tmpRight->key;

            root->right = deleteNode(root->right, tmpRight->key);
        }

        if (root == nullptr)
        {
            return root;
        }

        // Update root's height
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;

        int balance = getBalance(root);

        if (balance > 1 && data > root->left->key)
        {
            return rightRotate(root);
        }
        else if (balance < -1 && data < root->right->key)
        {
            return leftRotate(root);
        }
        else if (balance > 1 && data < root->left->key)
        {
            root->left = rightRotate(root);
            return leftRotate(root);
        }
        else if (balance < -1 && data > root->right->key)
        {
            root->right = leftRotate(root);
            return rightRotate(root);
        }
    }

    return root;
}

void NLR(Node *root) // Pre-order
{
    if (root == nullptr)
    {
        return;
    }
    cout << root->key << ' ';
    if (root->left)
    {
        NLR(root->left);
    }
    if (root->right)
    {
        NLR(root->right);
    }
}

void LNR(Node *root) // In-order
{
    if (root == nullptr)
    {
        return;
    }

    if (root->left)
    {
        LNR(root->left);
    }
    cout << root->key << ' ';
    if (root->right)
    {
        LNR(root->right);
    }
}

void LRN(Node *root) // Post-order
{
    if (root == nullptr)
    {
        return;
    }

    if (root->left)
    {
        LRN(root->left);
    }
    if (root->right)
    {
        LRN(root->right);
    }
    cout << root->key << ' ';
}

void LevelOrder(Node *root)
{
    if (!root)
    {
        return;
    }
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *cur = q.front();
        q.pop();
        cout << cur->key << ' ';
        if (cur->left)
            q.push(cur->left);
        if (cur->right)
            q.push(cur->right);
    }
}

int main(void)
{
    Node *root = nullptr;
    int values[] = {10, 20, 30, 15, 5, 25, 40};

    for (int val : values)
    {
        root = insertNode(root, val);
    }

    cout << "Pre-order (NLR): ";
    NLR(root);
    cout << "\n";

    cout << "In-order (LNR): ";
    LNR(root);
    cout << "\n";

    cout << "Post-order (LRN): ";
    LRN(root);
    cout << "\n";

    root = deleteNode(root, 20);

    cout << "Level-order: ";
    LevelOrder(root);
    cout << "\n\n";

    return 0;
}