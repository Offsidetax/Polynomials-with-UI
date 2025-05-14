#include <iostream>
#include <algorithm>

template <typename TKey, typename TValue>
class TAVLTree 
{
private:
    struct TTableRec 
    {
        TKey key;
        TValue value;
    };

    struct Node 
    {
        TTableRec data;
        Node* left;
        Node* right;
        Node* parent;
        int height;
    };

    Node* root;

    int GetHeight(Node* node) 
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int GetBalance(Node* node) 
    {
        if (node == nullptr)
            return 0;
        return GetHeight(node->right) - GetHeight(node->left);
    }

    void UpdateHeight(Node* node) 
    {
        int leftHeight = GetHeight(node->left);
        int rightHeight = GetHeight(node->right);
        node->height = 1 + std::max(leftHeight, rightHeight);
    }

    Node* RotateLeft(Node* x) 
    {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr)
            y->left->parent = x;
        y->left = x;
        y->parent = x->parent;
        x->parent = y;
        UpdateHeight(x);
        UpdateHeight(y);
        return y;
    }

    Node* RotateRight(Node* y) 
    {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nullptr)
            x->right->parent = y;
        x->right = y;
        x->parent = y->parent;
        y->parent = x;
        UpdateHeight(y);
        UpdateHeight(x);
        return x;
    }

    Node* Balance(Node* node) 
    {
        UpdateHeight(node);
        int balance = GetBalance(node);

        if (balance < -1) 
        {
            if (GetBalance(node->left) > 0)
                node->left = RotateLeft(node->left);
            return RotateRight(node);
        }

        if (balance > 1) 
        {
            if (GetBalance(node->right) < 0)
                node->right = RotateRight(node->right);
            return RotateLeft(node);
        }

        return node;
    }

    Node* Minimum(Node* node) 
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    Node* Insert(Node* node, TKey key, TValue value, Node* parent = nullptr) 
    {
        if (node == nullptr) 
        {
            Node* newNode = new Node{ {key, value}, nullptr, nullptr, parent, 1 };
            return newNode;
        }

        if (key < node->data.key) 
        {
            node->left = Insert(node->left, key, value, node);
        }
        else if (key > node->data.key) 
        {
            node->right = Insert(node->right, key, value, node);
        }
        else 
        {
            node->data.value = value;
        }

        return Balance(node);
    }

    Node* Delete(Node* node, TKey key) 
    {
        if (node == nullptr)
            return nullptr;

        if (key < node->data.key) 
        {
            node->left = Delete(node->left, key);
        }
        else if (key > node->data.key) 
        {
            node->right = Delete(node->right, key);
        }
        else 
        {
            if (node->left == nullptr || node->right == nullptr) 
            {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) 
                {
                    temp = node;
                    node = nullptr;
                }
                else 
                {
                    temp->parent = node->parent;
                    *node = *temp;
                }
                delete temp;
            }
            else 
            {
                Node* temp = Minimum(node->right);
                node->data = temp->data;
                node->right = Delete(node->right, temp->data.key);
            }
        }

        if (node == nullptr)
            return nullptr;

        return Balance(node);
    }

    void PrintTree(Node* node, int level = 0) const 
    {
        if (node == nullptr)
            return;

        PrintTree(node->right, level + 1);
        for (int i = 0; i < level; ++i)
            std::cout << "   ";
        std::cout << node->data.key << " (" << GetBalance(node) << ")\n";
        PrintTree(node->left, level + 1);
    }

    void DestroyTree(Node* node) 
    {
        if (node != nullptr) 
        {
            DestroyTree(node->left);
            DestroyTree(node->right);
            delete node;
        }
    }
public:
    TAVLTree() 
    {
        root = nullptr;
    }

    ~TAVLTree() 
    {
        DestroyTree(root);
    }

    void Insert(TKey key, TValue value) 
    {
        root = Insert(root, key, value);
    }

    void Delete(TKey key) 
    {
        root = Delete(root, key);
    }

    Node* GetRoot() const 
    {
        return root;
    }

    TValue& operator[](TKey key) 
    {
        Node* node = root;
        while (node != nullptr) 
        {
            if (key == node->data.key)
                return node->data.value;
            else if (key < node->data.key)
                node = node->left;
            else
                node = node->right;
        }
        Insert(key, TValue());
        return (*this)[key]; 
    }

    bool Find(TKey key, TValue& outValue) const 
    {
        Node* node = root;
        while (node != nullptr) 
        {
            if (key == node->data.key) 
            {
                outValue = node->data.value;
                return true;
            }
            else if (key < node->data.key)
                node = node->left;
            else
                node = node->right;
        }
        return false;
    }

    void Print() const 
    {
        if (root == nullptr)
            std::cout << "(empty)\n";
        else
            PrintTree(root);
    }

    TValue* find(const TKey& key)
    {
        Node* node = root;
        while (node != nullptr)
        {
            if (key == node->data.key)
                return &(node->data.value);
            else if (key < node->data.key)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

    void remove(const TKey& key)
    {
        Delete(key);
    }

};
