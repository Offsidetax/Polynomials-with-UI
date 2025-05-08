#pragma once

#include <iostream>
#include <string>

template <typename TKey, typename TValue>
class TRedBlackTree {
private:
    enum Color { RED, BLACK };

    struct TTableRec {
        TKey key;
        TValue value;
    };

    struct Node {
        TTableRec data;
        Node* left;
        Node* right;
        Node* parent;
        Color color;
    };

    Node* root;
    Node* nil;

    void PrintTree(Node* node, int level = 0) const {
        if (node == nil) return; // Игнорируем nil-узлы

        // Сначала правый потомок (печатается выше)
        PrintTree(node->right, level + 1);

        // Отступы для текущего уровня
        for (int i = 0; i < level; ++i)
            std::cout << "   ";

        // Цвет как текст [R] или [B]
        std::string color = (node->color == RED) ? "[R]" : "[B]";
        std::cout << color << node->data.key << std::endl;

        // Потом левый потомок (печатается ниже)
        PrintTree(node->left, level + 1);
    }

    Node* CopyTree(Node* node, Node* parent, Node* otherNil) {
        if (node == otherNil)
            return nil;

        Node* newNode = new Node{ node->data, nil, nil, parent, node->color };
        newNode->left = CopyTree(node->left, newNode, otherNil);
        newNode->right = CopyTree(node->right, newNode, otherNil);
        return newNode;
    }

    void DestroyTree(Node* node) {
        if (node != nil) {
            DestroyTree(node->left);
            DestroyTree(node->right);
            delete node;
        }
    }

    void swap(Node* u, Node* v) {
        if (u->parent == nil)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    int Height(Node* node) {
        if (node == nil) return 0;  // База рекурсии: высота NIL-узла = 0
        int leftHeight = Height(node->left);
        int rightHeight = Height(node->right);
        return 1 + std::max(leftHeight, rightHeight);  // Выбираем максимальную высоту
    }

    Node* Minimum(Node* node) {
        while (node->left != nil)
            node = node->left;
        return node;
    }

    void LeftRotate(Node* x) { //малый левый поворот
        Node* y = x->right;

        x->right = y->left;
        
        if (y->left != nil)
            y->left->parent = x;

        y->parent = x->parent;
        
        if (x->parent == nil)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        
        y->left = x;
        x->parent = y;
    }

    void RightRotate(Node* y) { //малый правый поворот
        Node* x = y->left;

        y->left = x->right;
        
        if (x->right != nil)
            x->right->parent = y;
        
        x->parent = y->parent;
        
        if (y->parent == nil)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
        
        x->right = y;
        y->parent = x;
    }

    void InsertFixup(Node* z) {
        while (z->parent->color == RED) { //пока не выполняется свойство о том, что у красного только черные дети
            if (z->parent == z->parent->parent->left) {  //родитель это левый ребенок 
                Node* y = z->parent->parent->right; // y - дядя для z

                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else { 
                    if (z == z->parent->right) { //z - правый ребенок
                        z = z->parent;
                        LeftRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    
                    RightRotate(z->parent->parent);
                }
            }
            else { //родитель это левый ребенок 
                Node* y = z->parent->parent->left; // y - дядя для z
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        RightRotate(z);
                    }

                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;

                    LeftRotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void DeleteFixup(Node* x) {
        while (x != root && x->color == BLACK) { 
            if (x == x->parent->left) {

                Node* w = x->parent->right;
                
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }
                
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    LeftRotate(x->parent);
                    x = root;
                }
            }
            else {
                Node* w = x->parent->left;

                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    RightRotate(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                }
                else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        LeftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    RightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

public:
    TRedBlackTree() {
        nil = new Node{ {}, nullptr, nullptr, nullptr, BLACK };
        root = nil;
    }

    TRedBlackTree(const TRedBlackTree& other) {
        nil = new Node{ {}, nullptr, nullptr, nullptr, BLACK };
        root = CopyTree(other.root, nil, other.nil);
    }

    ~TRedBlackTree() {
        DestroyTree(root);
        delete nil;
    }

    TRedBlackTree& operator=(const TRedBlackTree& other) {
        if (this == &other) {
            return *this; // Защита от самоприсваивания
        }

        // Удаляем текущее дерево
        DestroyTree(root);
        delete nil;

        // Создаем новый nil-узел
        nil = new Node{ {}, nullptr, nullptr, nullptr, BLACK };

        // Копируем дерево
        root = CopyTree(other.root, nil, other.nil);

        return *this;
    }

    int GetHeight() {
        return Height(root);
    }

    Node* Find(TKey key) {
        Node* node = root;

        while (node != nil) {
            if (key == node->data.key)
                return node;
            else if (key < node->data.key)
                node = node->left;
            else
                node = node->right;
        }

        return nullptr;
    }

    TValue* find(TKey key) { //Понадобилось для интерфейса
        Node* found = Find(key);
        if (found)
            return &found->data.value;
        return nullptr;
    }

    void Insert(TKey key, TValue value) {
        Node* z = new Node{ {key, value}, nil, nil, nullptr, RED };
        Node* y = nil;
        Node* x = root;

        while (x != nil) {
            y = x;

            if (z->data.key == x->data.key)
            {
                x->data.value = z->data.value;
                return;
            }
            else if (z->data.key < x->data.key)
                x = x->left;
            else
                x = x->right;
        }

        z->parent = y;

        if (y == nil)
            root = z;
        else if (z->data.key < y->data.key)
            y->left = z;
        else
            y->right = z;

        InsertFixup(z);
    }

    void Delete(TKey key) {
        Node* z = Find(key);
        if (!z) throw "There is no such element to delete!";

        Node* y = z;
        Node* x;
        Color originalColor = y -> color;

        if (z->left == nil) {
            x = z->right;
            swap(z, z->right);
        }
        else if (z->right == nil) {
            x = z->left;
            swap(z, z->left);
        }
        else {
            y = Minimum(z->right);
            originalColor = y->color;
            x = y->right;

            if (y->parent == z) {
                x->parent = y;
            }
            else {
                swap(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            swap(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;//свап ключа значения

        if (originalColor == BLACK) {
            DeleteFixup(x);
        }
    }

    void remove(TKey key) { //понадоилось для интерфейса
        Delete(key);
    }

    //void PrintHelper(Node* node, int indent = 0) {
    //    if (node != nil) {
    //        PrintHelper(node->right, indent + 6);
    //        std::cout << std::string(indent, ' ') << node->data.key << "(" << (node->color == RED ? "R" : "B") << ")\n";
    //        PrintHelper(node->left, indent + 6);
    //    }
    //}

    void Print() const {
        if (root == nullptr) {
            std::cout << "(empty)" << std::endl;
        }
        else {
            PrintTree(root);
        }
    }

    /////////////////ИТЕРАТОР/////////////////////////
    class Iterator {
    private:
        Node* current;
        Node* nil;

        Node* TreeSuccessor(Node* node) const {
            if (node->right != nil)
                return TreeMinimum(node->right);

            Node* y = node->parent;
            while (y != nil && node == y->right) {
                node = y;
                y = y->parent;
            }
            return y;
        }

        Node* TreeMinimum(Node* node) const {
            while (node->left != nil) {
                node = node->left;
            }
            return node;
        }

    public:
        Iterator(Node* node, Node* nilNode) : current(node), nil(nilNode) {}

        TTableRec& operator*() const {
            return current->data;
        }

        TTableRec* operator->() const {
            return &(current->data);
        }

        Iterator& operator++() { // префиксный ++
            current = TreeSuccessor(current);
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
    };

    Iterator begin() const {
        Node* min = root;
        if (min == nil) return Iterator(nil, nil);
        while (min->left != nil) {
            min = min->left;
        }
        return Iterator(min, nil);
    }

    Iterator end() const {
        return Iterator(nil, nil);
    }
};