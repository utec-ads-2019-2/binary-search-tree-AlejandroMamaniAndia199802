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
        auto currentNode = node;
        while(currentNode && currentNode->left)
            currentNode = currentNode->left;
        return currentNode;
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
            if(!node->left)
            {
                auto tempNode = node->right;
                delete [] node;
                return tempNode;
            }

            else if(!node->right)
            {
                auto tempNode = node->left;
                delete [] node;
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
        Node<T> *searchNode = this->root;
        while(searchNode)
        {
            if(searchNode->data == data) return true;
            else if(data < searchNode->data)
            {
                if(searchNode->left) searchNode = searchNode->left;
                else break;
            }
            else if (data > searchNode->data)
            {
                if(searchNode->right) searchNode = searchNode->right;
                else break;
            }
        }
        return false;
    }

    void insert(T data) {
        Node<T> *searchNode = this -> root;
        if (find(data)) return;
        if (!searchNode) this->root = new Node<T>(data);
        else
        {
            while(searchNode)
            {
                if(data < searchNode->data)
                {
                    if(searchNode->left) searchNode = searchNode->left;
                    else {searchNode->left = new Node<T>(data); break;}
                }
                else
                {
                    if(searchNode->right) searchNode = searchNode->right;
                    else {searchNode->right = new Node<T>(data); break;}
                }
            }
        }
        ++nodes;
    }

    bool remove(T data) {
        Node<T> *searchNode = this -> root;
        if (!find(data) || !searchNode) return false;
        this->root = kill(searchNode, data);
        --nodes;
        return true;
    }

    int size() {
        return this->nodes;
    }

    void traversePreOrder() {
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
