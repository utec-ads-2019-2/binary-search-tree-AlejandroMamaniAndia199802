#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"

template <typename T>
class BSTree{
private:
    Node<T> *root;
    int nodes;
    Node<T>* minValueNode(Node<T>* node)
    {
        auto current = node;
        while(current && current->left)
            current = current->left;
        return current;
    }

    Node<T>* kill(Node<T>* node, T data)
    {
        if (!node) return node;

        if (data < node->data)
            node->left = kill(node->left, data);

        else if (data > node->data)
            node->right = kill(node->right, data);

        else
        {
            if(!node->right)
            {
                auto tempNode = node->left;
                delete  []node;
                return tempNode;
            }

            else if(!node->left)
            {

                auto tempNode = node->right;
                delete []node;
                return tempNode;
            }

            auto tempNode = minValueNode(node->right);

            node->data = tempNode->data;
            node->right = kill(node->right, tempNode->data);
        }
        return node;

    }

public:
    BSTree() : root(nullptr), nodes(0) {};

    bool find(T data) {
        Node<T> *keyNode = this->root;
        while(keyNode)
        {
            if(keyNode->data == data) return true;
            else if(data < keyNode->data)
            {
                if(keyNode->left) keyNode = keyNode->left;
                else break;
            }
            else if (data > keyNode->data)
            {
                if(keyNode->right) keyNode = keyNode->right;
                else break;
            }
        }
        return false;
    }

    void insert(T data) {
        Node<T> *keyNode = this -> root;
        // Podrías haber trabajado con doble puntero para evitar recorrer el árbol 2 veces
        if (find(data)) return;
        // Sería bueno sacar el new a un solo lugar en vez de repetirlo en diversos lados
        if (!keyNode) this->root = new Node<T>(data);
        else
        {
            while(keyNode)
            {
                if(data > keyNode->data)
                {
                    if(!(keyNode->right)) {keyNode->right = new Node<T>(data); break;}
                    else {keyNode = keyNode->right;}

                }
                else
                {
                    if(!(keyNode->left)) {keyNode->left = new Node<T>(data); break;}
                    else{keyNode = keyNode->left;}
                }
            }
        }
        ++nodes;
    }

    bool remove(T data) {
        Node<T> *searchNode = this -> root;
        // Lo mismo, con un doble puntero o con algún otro método te evitas hacer 2 recorridos
        if (!find(data) || !searchNode) return false;
        this->root = kill(searchNode, data);
        --nodes;
        return true;
    }

    unsigned int size() {
        return this->nodes;
    }

    void traversePreOrder() {
        // El temporal node es innecesario
        Node<T>* node = root;
        if(this->root) {
            std::cout << node->data << std::endl;
            if(node->left) traversePreOrder(node->left);
            if(node->right) traversePreOrder(node->right);
        }
    }

    void traverseInOrder() {
        Node<T> *node = root;
        if(this->root){
            if(node->left) traverseInOrder(node->left);
            std::cout << node->data << std::endl;
            if(node->right) traverseInOrder(node->right);
        };
    }

    void traversePostOrder() {
        Node<T> *node = root;
        if(this->root) {
            if(node->left) traversePostOrder(node->left);
            if(node->right) traversePostOrder(node->right);
            std::cout << node->data << std::endl;
        };
    }

    Iterator<T> begin() {
        return Iterator<T> (this->root);
    }

    Iterator<T> end() {
        return Iterator<T> ();
    }

    ~BSTree() {
        this->root->killself(this->root);
    }
};

#endif
