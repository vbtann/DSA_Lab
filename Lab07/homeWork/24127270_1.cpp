#include <iostream>
#include <queue>

using namespace std;

enum COLOR
{
    RED,
    BLACK
};

struct NODE
{
    int key;
    COLOR color;
    NODE *left;
    NODE *right;
    NODE *parent;
};

NODE *newNode(int data)
{
    NODE *tmp = new NODE;
    tmp->color = RED;
    tmp->key = data;
    tmp->left = tmp->right = nullptr;
    tmp->parent = nullptr;

    return tmp;
}

NODE *leftRotate(NODE *root)
{
    NODE *rightChild = root->right;
    root->right = rightChild->left;

    if (rightChild->left)
    {
        rightChild->left->parent = root;
    }

    rightChild->parent = root->parent;

    if (!root->parent)
    {
        ;
    }
    else if (root == root->parent->left)
    {
        root->parent->left = rightChild;
    }
    else
    {
        root->parent->right = rightChild;
    }

    rightChild->left = root;
    root->parent = rightChild;

    return rightChild;
}

NODE *rightRotate(NODE *root)
{
    NODE *leftChild = root->left;
    root->left = leftChild->right;

    if (leftChild->right)
    {
        leftChild->right->parent = root;
    }

    leftChild->parent = root->parent;

    if (!root->parent)
    {
        ;
    }
    else if (root == root->parent->left)
    {
        root->parent->left = leftChild;
    }
    else
    {
        root->parent->right = leftChild;
    }

    leftChild->right = root;
    root->parent = leftChild;

    return leftChild;
}

NODE *fixTreeAfterInsert(NODE *root, NODE *newNode)
{
    if (newNode == root)
    {
        newNode->color = BLACK;
        return root;
    }

    if (root == nullptr || newNode->parent == nullptr || newNode->parent->color == BLACK)
    {
        return root;
    }

    NODE *parentNode = newNode->parent;
    NODE *grandParentNode = parentNode->parent;

    if (grandParentNode == nullptr)
    {
        parentNode->color = BLACK;
        return root;
    }

    bool parentIsLeftChild = (parentNode == grandParentNode->left) ? 1 : 0;
    NODE *uncleNode = (parentIsLeftChild) ? grandParentNode->right : grandParentNode->left;

    if (uncleNode != nullptr && uncleNode->color == RED) // Case 1
    {
        uncleNode->color = BLACK;
        parentNode->color = BLACK;
        grandParentNode->color = RED;

        return fixTreeAfterInsert(root, grandParentNode);
    }
    else // Case 2 & 3
    {
        if (parentIsLeftChild)
        {
            if (newNode == parentNode->right) // Left right case
            {
                leftRotate(parentNode);

                NODE *tmp = newNode;
                newNode = parentNode;
                parentNode = tmp;
            }

            rightRotate(grandParentNode); // Left left case

            COLOR tmpColor = parentNode->color;
            parentNode->color = grandParentNode->color;
            grandParentNode->color = tmpColor;

            if (grandParentNode == root)
            {
                root = parentNode;
            }
        }
        else
        {
            if (newNode == parentNode->left) // Right left case
            {
                rightRotate(parentNode);

                NODE *tmp = newNode;
                newNode = parentNode;
                parentNode = tmp;
            }

            leftRotate(grandParentNode); // Right right case

            COLOR tmpColor = parentNode->color;
            parentNode->color = grandParentNode->color;
            grandParentNode->color = tmpColor;

            if (grandParentNode == root)
            {
                root = parentNode;
            }
        }
    }

    root->color = BLACK;
    return root;
}

NODE *insert(NODE *root, int data)
{
    if (!root)
    {
        root = newNode(data);
        root->color = BLACK;
        return root;
    }

    NODE *curNode = root;
    NODE *parentNode = nullptr;

    while (curNode != nullptr)
    {
        parentNode = curNode;

        if (data > curNode->key)
        {
            curNode = curNode->right;
        }
        else if (data < curNode->key)
        {
            curNode = curNode->left;
        }
        else
        {
            return root;
        }
    }

    NODE *insertedNode = newNode(data);
    insertedNode->parent = parentNode;

    if (parentNode->key > data)
    {
        parentNode->left = insertedNode;
    }
    else
    {
        parentNode->right = insertedNode;
    }

    return fixTreeAfterInsert(root, insertedNode);
}

NODE *search(NODE *root, int data)
{
    NODE *cur = root;
    while (cur != nullptr)
    {
        if (cur->key > data)
        {
            cur = cur->left;
        }
        else if (cur->key < data)
        {
            cur = cur->right;
        }
        else
        {
            return cur;
        }
    }
    return nullptr;
}

NODE *findSuccessor(NODE *node)
{
    while (node && node->left != nullptr)
    {
        node = node->left;
    }

    return node;
}

NODE *deleteNode(NODE *root, int data)
{
    if (root == nullptr)
    {
        return root;
    }

    if (root->key > data)
    {
        root->left = deleteNode(root->left, data);
        if (root->left != nullptr)
        {
            root->left->parent = root;
        }
    }
    else if (root->key < data)
    {
        root->right = deleteNode(root->right, data);

        if (root->right != nullptr)
        {
            root->right->parent = root;
        }
    }
    else
    {
        if (root->left == nullptr && root->right == nullptr) // Node has no child
        {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr) // Node has only right child
        {
            NODE *tmp = root->right;
            if (tmp)
            {
                tmp->parent = root->parent;
            }
            delete root;
            return tmp;
        }
        else if (root->right == nullptr) // Node has only left child
        {
            NODE *tmp = root->left;
            if (tmp)
            {
                tmp->parent = root->parent;
            }
            delete root;
            return tmp;
        }
        else
        {
            NODE *successor = findSuccessor(root->right);

            root->key = successor->key;

            root->right = deleteNode(root->right, successor->key);

            if (root->right != nullptr)
            {
                root->right->parent = root;
            }
        }
    }
    return root;
}

void levelOrder(NODE *root)
{
    queue<NODE *> q;
    q.push(root);
    while (!q.empty())
    {
        NODE *cur = q.front();
        q.pop();

        cout << cur->key << ' ';
        // cout << cur->key << ' (' << cur->color << ') ';

        if (cur->right)
        {
            q.push(cur->right);
        }
        if (cur->left)
        {
            q.push(cur->left);
        }
    }
}

int main(void)
{
    NODE *root = nullptr;
    root = insert(root, 11);
    root = insert(root, 2);
    root = insert(root, 14);
    root = insert(root, 1);
    root = insert(root, 7);
    root = insert(root, 15);
    root = insert(root, 5);
    root = insert(root, 8);

    cout << "Level order traversal: ";
    levelOrder(root);
    cout << "\n";

    NODE *found = search(root, 7);
    if (found)
    {
        cout << "Found " << found->key << " (" << (found->color == RED ? "RED" : "BLACK") << ")\n";
    }
    else
    {
        cout << "Not found!\n";
    }

    int deleteNum = 11;
    cout << "Tree after deleted number " << deleteNum << "\n";
    deleteNode(root, deleteNum);
    levelOrder(root);
    cout << "\n\n";
    return 0;
}