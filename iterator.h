#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>

template <typename T>
class Iterator {
private:
    Node<T> *current;
    std::stack< Node<T>* > *stackInc;
    std::stack< Node<T>* > *stackDec;

public:
    Iterator() {
        current = nullptr;
        stackInc = new std::stack<Node<T>*>;
        stackDec = new std::stack<Node<T>*>;
    }


    Iterator(Node<T> *node) {
        if(!node)
        {
            current = nullptr;
            stackInc = new std::stack<Node<T>*>;
            stackDec = new std::stack<Node<T>*>;
        }
        else
        {
            stackInc = new std::stack<Node<T>*>;
            stackDec = new std::stack<Node<T>*>;

            current = node;
            while(current->left)
            {
                stackInc->push(current);
                current = current->left;
            }
        }
    }

    Iterator<T> operator=(Iterator<T> other) {
        this->current = other.current;
        *stackInc = other.stackInc;
        *stackDec = other.stackDec;
    }

    bool operator!=(Iterator<T> other) {
        return &(this->current) != &(other.current);
    }

    Iterator<T> operator++() {
        if(!current) return *this;
        stackDec->push(current);
        if(current->right)
        {
            current = current->right;
            while(current->left)
            {
                stackInc->push(current);
                current = current->left;
            }
        }
        else
        {
            if(stackInc->size()>0)
            {
                current = stackInc->top();
                stackInc->pop();
            }
            else
                current = nullptr;
        }

        return *this;
    }

    Iterator<T> operator--() {
        if(stackDec->empty()) return *this;

        if(!current)
        {
            current = stackDec->top();
            stackDec->pop();
        }
        else
        {
            stackInc->push(current);
            current = stackDec->top();
            stackDec->pop();
        }

        return *this;
    }


    T operator*() {

        if(!current) throw ;
        return current->data;
    }
};

#endif