#ifndef __BSTSET_H__
#define __BSTSET_H__
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "set.h"


template<typename T>
class BstSet : public Set<T> {
private:
    class Node {
    public:
        T data;
        Node * left;
        Node * right;
    public:
        Node() {}
        Node(const T & el) : data(el), left(NULL), right(NULL) {}
    };
    Node * root;
    Node * copy(Node * x) {
        if (x == NULL) {
            return NULL;
        }
        Node * root = new Node(x->data);
        root->left = copy(x->left);
        root->right = copy(x->right);
        return root;
    }
    Node * add(Node * x, const T & el) {
        if (x == NULL) {
            return new Node(el);
        }
        if (el < x->data) {
            x->left = add(x->left, el);
        }
        else if (el > x->data){
            x->right = add(x->right, el);
        }
        else {
            return x;
        }
        return x;
    }
    bool contains(Node * x, const T & el) const {
        if (x == NULL) {
            return false;
        }
        if (el < x->data) {
            return contains(x->left, el);
        }
        else if (el > x->data) {
            return contains(x->right, el);
        }
        else {
            return true;
        }
    }
    Node * deleteMin(Node * x) {
        if (x == NULL) {
            throw std::invalid_argument("The node you want to delete doesn't exist!");
        }
        if (x->left == NULL) {
            Node * t = x->right;
            delete x;
            return t;
        }
        x->left = deleteMin(x->left);
        return x;
    }
    Node * min(Node * x) {
        if (x->left == NULL) {
            return x;
        }
        return min(x->left);
    }
    Node * remove(Node * x, const T& el) {
        if (x == NULL) {
            return NULL;
        }
        if (el < x->data) {
            x->left = remove(x->left, el);
        }
        else if (el > x->data) {
            x->right = remove(x->right, el);
        }
        else {
            if (x->left == NULL) {
                Node * t = x->right;
                delete x;
                return t;
            }
            if (x->right == NULL) {
                Node * t = x->left;
                delete x;
                return t;
            }
            Node * t = x;
            x = new Node(min(t->right)->data);
            x->left = t->left;
            x->right = deleteMin(t->right);
            delete t;
        }
        return x;
    }
    void destroy(Node * x) {
        if (x == NULL) {
            return;
        }
        destroy(x->left);
        destroy(x->right);
        delete x;
    }
    void inOrder(Node * x) {
        if (x == NULL) {
            return;
        }
        inOrder(x->left);
        std::cout << x->data << " ";
        inOrder(x->right);
    }
public:
    virtual void add(const T & key) {
        root = add(root, key);
    }
    virtual bool contains(const T& key) const {
        return contains(root, key);
    }
    virtual void remove(const T & key) {
        root = remove(root, key);
    }
    BstSet() : root(NULL) {} 
    BstSet(const BstSet & rhs) {
        root = copy(rhs.root);
    }
    BstSet & operator=(const BstSet & rhs) {
        if (this != &rhs) {
            destroy(root);
            root = copy(rhs.root);
        }
        return *this;
    }

    virtual ~BstSet() {
        destroy(root);
        root = NULL;
    }
    void print() {
        inOrder(root);
        std::cout << std::endl;
    }
};

#endif