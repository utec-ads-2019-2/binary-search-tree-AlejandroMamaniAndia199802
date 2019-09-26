#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>

template <typename T>
class Iterator {
private:
    Node<T> *current;
    std::stack< Node<T>* > *stackup;
    std::stack< Node<T>* > *stackdown;

public:
    Iterator() {
        current = nullptr;
        stackup = new std::stack<Node<T>*>;
        stackdown = new std::stack<Node<T>*>;
    }


    Iterator(Node<T> *node) {
        if(node)
        {
            stackup = new std::stack<Node<T>*>;
            stackdown = new std::stack<Node<T>*>;

            current = node;
            while(current->left)
            {
                stackup->push(current);
                current = current->left;
            }
        }
        else
        {
            current = nullptr;
            stackup = new std::stack<Node<T>*>;
            stackdown = new std::stack<Node<T>*>;
        }
    }

    Iterator<T> operator=(Iterator<T> other)
            {
        this->current = other.current;
        *stackup = other.stackInc;
        *stackdown = other.stackDec;
    }

    bool operator!=(Iterator<T> other)
    {
        return &(this->current) != &(other.current);
    }

    Iterator<T> operator++()
            {
        if(!current) return *this;
        stackdown->push(current);
        if(current->right)
        {
            current = current->right;
            while(current->left)
            {
                stackup->push(current);
                current = current->left;
            }
        }
        else
        {
            if(stackup->size()>0)
            {
                current = stackup->top();
                stackup->pop();
            }
            else
                current = nullptr;
        }

        return *this;
    }

    Iterator<T> operator--() {
        if(stackdown->empty()) return *this;

        if(current)
        {
            stackup->push(current);
            current = stackdown->top();
            stackdown->pop();
        }
        else
        {
            current = stackdown->top();
            stackdown->pop();
        }

        return *this;
    }


    T operator*() {

        if(!current) throw ;
        return current->data;
    }
};

#endif