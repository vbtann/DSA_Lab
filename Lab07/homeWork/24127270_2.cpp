#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 3;
const int MAX_keys = MAX - 1;
const int MIN_keys = (MAX / 2) - 1;

struct NODE
{
    int keys[MAX];
    NODE *childrenPtr[MAX + 1];
    int numKeys;
    bool isLeaf;
};

NODE *newNode(bool isLeaf)
{
    NODE *node = new NODE;
    node->isLeaf = isLeaf;
    node->numKeys = 0;
    for (int i = 0; i < MAX + 1; i++)
    {
        node->childrenPtr[i] = nullptr;
    }
    return node;
}

NODE *insertNonFullNode(NODE *root, int data)
{
    int pos = root->numKeys - 1;

    if (root->isLeaf == 1)
    {
        root->numKeys++;
        while (root->keys[pos] >= data && pos >= 0)
        {
            root->keys[pos + 1] = root->keys[pos];
            pos--;
        }
        root->keys[pos + 1] = data;
    }
    else
    {
        int pos = 0;
        while (root->keys[pos] < data && pos < MAX)
        {
            pos++;
        }
        if (root->childrenPtr[pos] == nullptr)
        {
            NODE *tmp = newNode(true);
            tmp->numKeys = 1;
            tmp->keys[0] = data;
            root->childrenPtr[pos] = tmp;
            return root;
        }
        else if (root->childrenPtr[pos]->numKeys == MAX)
        {
            NODE *left = root->childrenPtr[pos];
            NODE *right = newNode(left->isLeaf);

            int mid = root->childrenPtr[pos]->numKeys / 2;

            for (int i = 0; i < mid; i++)
            {
                right->keys[i] = left->keys[mid + i + 1];
            }

            if (!left->isLeaf)
            {
                for (int i = 0; i < mid; i++)
                {
                    right->childrenPtr[i] = left->childrenPtr[mid + i + 1];
                }
            }

            left->numKeys = right->numKeys = mid;

            for (int i = root->numKeys; i > pos; i--)
            {
                root->childrenPtr[i + 1] = root->childrenPtr[i];
            }

            root->childrenPtr[pos + 1] = right;

            for (int i = root->numKeys - 1; i >= pos; i--)
            {
                root->keys[i + 1] = root->keys[i];
            }

            root->keys[pos] = left->keys[mid];
            root->numKeys++;

            if (data < root->keys[pos])
            {
                insertNonFullNode(root->childrenPtr[pos], data);
            }
            else
            {
                insertNonFullNode(root->childrenPtr[pos + 1], data);
            }
        }
        else
        {
            insertNonFullNode(root->childrenPtr[pos], data);
        }
    }
}

NODE *insert(NODE *root, int data)
{
    if (root == nullptr)
    {
        root = newNode(1);
        root->numKeys = 1;
        root->keys[0] = data;
        return root;
    }

    if (root->numKeys == MAX)
    {
        NODE *newRoot = newNode(false);
        newRoot->childrenPtr[0] = root;

        NODE *tmp = newNode(false);
        int mid = MAX / 2;
        for (int i = 0; i < mid; i++)
        {
            tmp->keys[i] = root->keys[mid + i + 1];
        }
        if (!root->isLeaf)
        {
            for (int i = 0; i < mid; i++)
            {
                tmp->childrenPtr[i] = root->childrenPtr[mid + i + 1];
            }
        }
        root->numKeys = mid;
        tmp->numKeys = mid;

        newRoot->keys[0] = root->keys[mid];
        newRoot->childrenPtr[1] = tmp;
        newRoot->numKeys = 1;

        if (data < newRoot->keys[0])
        {
            insertNonFullNode(root, data);
        }
        else
        {
            insertNonFullNode(tmp, data);
        }
    }
    return root;
}

NODE *search(NODE *root, int data)
{
    if (root == nullptr)
        return nullptr;

    int pos = 0;
    while (pos < root->numKeys && data > root->keys[pos])
    {
        pos++;
    }

    if (pos < root->numKeys && root->keys[pos] == data)
    {
        return root;
    }

    if (root->isLeaf)
    {
        return nullptr;
    }

    return search(root->childrenPtr[pos], data);
}

int findSuccessor(NODE *root)
{
    NODE *current = root;

    while (!current->isLeaf)
    {
        current = current->childrenPtr[0];
    }

    return current->keys[0];
}

NODE *mergeNode(NODE *left, NODE *right, int deletedKey)
{
    int leftPos = left->numKeys;

    left->keys[leftPos] = deletedKey;
    left->numKeys++;

    for (int i = 0; i < right->numKeys; i++)
    {
        left->keys[left->numKeys] = right->keys[i];
        left->numKeys++;
    }

    if (!left->isLeaf)
    {
        for (int i = 0; i <= right->numKeys; i++)
        {
            left->childrenPtr[leftPos + 1 + i] = right->childrenPtr[i];
        }
    }

    delete right;
    return left;
}

NODE *deleteNode(NODE *root, int data)
{
    if (root == nullptr)
        return nullptr;

    NODE *node = search(root, data);

    if (node == nullptr)
    {
        cout << "Key " << data << " not found in the tree\n";
        return root;
    }

    int pos = 0;
    while (pos < node->numKeys && node->keys[pos] != data)
    {
        pos++;
    }

    if (node->isLeaf)
    {
        for (int i = pos; i < node->numKeys - 1; i++)
        {
            node->keys[i] = node->keys[i + 1];
        }
        node->numKeys--;

        if (node == root && node->numKeys == 0)
        {
            delete node;
            return nullptr;
        }

        return root;
    }
    else
    {
        if (node->numKeys > MIN_keys)
        {
            int replacement;
            if (node->childrenPtr[pos] != nullptr)
            {
                NODE *pred = node->childrenPtr[pos];
                while (!pred->isLeaf)
                {
                    pred = pred->childrenPtr[pred->numKeys];
                }
                replacement = pred->keys[pred->numKeys - 1];

                node->keys[pos] = replacement;

                node->childrenPtr[pos] = deleteNode(node->childrenPtr[pos], replacement);
            }
            else
            {
                int successor = findSuccessor(node->childrenPtr[pos + 1]);

                node->keys[pos] = successor;

                node->childrenPtr[pos + 1] = deleteNode(node->childrenPtr[pos + 1], successor);
            }
        }
        else
        {
            NODE *leftChild = node->childrenPtr[pos];
            NODE *rightChild = node->childrenPtr[pos + 1];

            if (leftChild && leftChild->numKeys > MIN_keys)
            {
                int predecessor = leftChild->keys[leftChild->numKeys - 1];
                node->keys[pos] = predecessor;

                node->childrenPtr[pos] = deleteNode(leftChild, predecessor);
            }
            else if (rightChild && rightChild->numKeys > MIN_keys)
            {
                int successor = rightChild->keys[0];
                node->keys[pos] = successor;

                node->childrenPtr[pos + 1] = deleteNode(rightChild, successor);
            }
            else if (leftChild && rightChild)
            {
                int deletedKey = node->keys[pos];

                leftChild = mergeNode(leftChild, rightChild, deletedKey);

                node->childrenPtr[pos] = leftChild;

                for (int i = pos; i < node->numKeys - 1; i++)
                {
                    node->keys[i] = node->keys[i + 1];
                    node->childrenPtr[i + 1] = node->childrenPtr[i + 2];
                }
                node->numKeys--;

                if (node == root && node->numKeys == 0)
                {
                    NODE *oldRoot = root;
                    root = leftChild;
                    delete oldRoot;
                }

                return deleteNode(root, data);
            }
        }
    }

    return root;
}

void NLR(NODE *root)
{
    if (root == nullptr)
        return;

    for (int i = 0; i < root->numKeys; i++)
    {
        cout << root->keys[i] << " ";
    }

    if (!root->isLeaf)
    {
        for (int i = 0; i <= root->numKeys; i++)
        {
            NLR(root->childrenPtr[i]);
        }
    }
}

void LNR(NODE *root)
{
    if (root == nullptr)
        return;

    if (root->isLeaf)
    {
        for (int i = 0; i < root->numKeys; i++)
        {
            cout << root->keys[i] << " ";
        }
        return;
    }

    for (int i = 0; i < root->numKeys; i++)
    {
        LNR(root->childrenPtr[i]);

        cout << root->keys[i] << " ";
    }

    LNR(root->childrenPtr[root->numKeys]);
}

void LRN(NODE *root)
{
    if (root == nullptr)
        return;

    if (!root->isLeaf)
    {
        for (int i = 0; i <= root->numKeys; i++)
        {
            LRN(root->childrenPtr[i]);
        }
    }

    for (int i = 0; i < root->numKeys; i++)
    {
        cout << root->keys[i] << " ";
    }
}

void LevelOrder(NODE *root)
{
    if (root == nullptr)
        return;

    queue<NODE *> q;
    q.push(root);

    while (!q.empty())
    {
        NODE *current = q.front();
        q.pop();

        for (int i = 0; i < current->numKeys; i++)
        {
            cout << current->keys[i] << " ";
        }

        if (!current->isLeaf)
        {
            for (int i = 0; i <= current->numKeys; i++)
            {
                if (current->childrenPtr[i] != nullptr)
                {
                    q.push(current->childrenPtr[i]);
                }
            }
        }
    }
}

int main(void)
{
    NODE *root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 12);
    root = insert(root, 30);
    root = insert(root, 7);

    cout << "Level Order Traversal: ";
    LevelOrder(root);
    cout << endl;

    cout << "Pre-order Traversal: ";
    NLR(root);
    cout << endl;

    cout << "In-order Traversal: ";
    LNR(root);
    cout << endl;

    cout << "Post-order Traversal: ";
    LRN(root);
    cout << endl;

    int searchKey = 6;
    NODE *result = search(root, searchKey);
    if (result)
        cout << "Key " << searchKey << " found in the tree." << endl;
    else
        cout << "Key " << searchKey << " not found in the tree." << endl;

    cout << "Deleting key 6..." << endl;
    root = deleteNode(root, 6);
    cout << "Level Order after deletion: ";
    LevelOrder(root);
    cout << endl;

    return 0;
}