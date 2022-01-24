#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "map.h"


template<typename K, typename V>
class BstMap : public Map<K,V> {
private:
    class Node {
    public:
        K key;
        V value;
        Node * left;
        Node * right;
    public:
        Node() {}
        Node(const K & k, const V & v) : key(k), value(v), left(NULL), right(NULL) {}
    };
    Node * root;
    Node * copy(Node * x) {
        if (x == NULL) {
            return NULL;
        }
        Node * root = new Node(x->key, x->value);
        root->left = copy(x->left);
        root->right = copy(x->right);
        return root;
    }
    Node * add(Node * x, const K & key, const V & value) {
        if (x == NULL) {
            return new Node(key, value);
        }
        if (key < x->key) {
            x->left = add(x->left, key, value);
        }
        else if (key > x->key){
            x->right = add(x->right, key, value);
        }
        else {
            x->value = value;
        }
        return x;
    }
    Node * lookup(Node * x, const K& key) const {
        if (x == NULL) {
            return NULL;
        }
        if (key < x->key) {
            return lookup(x->left, key);
        }
        else if (key > x->key) {
            return lookup(x->right, key);
        }
        else {
            return x;
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
    Node * remove(Node * x, const K& key) {
        if (x == NULL) {
            return NULL;
        }
        if (key < x->key) {
            x->left = remove(x->left, key);
        }
        else if (key > x->key) {
            x->right = remove(x->right, key);
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
            x = new Node(min(t->right)->key, min(t->right)->value);
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
        std::cout << x->key << ":" << x->value << "  ";
        inOrder(x->right);
    }
public:
    virtual void add(const K & key, const V & value) {
        root = add(root, key, value);
    }
    virtual const V & lookup(const K& key) const throw (std::invalid_argument) {
        Node * res = lookup(root, key);
        if (res == NULL) {
            throw std::invalid_argument("The key is not found!");
        }
        return res->value;
    }
    virtual void remove(const K & key) {
        root = remove(root, key);
    }
    BstMap() : root(NULL) {} 
    BstMap(const BstMap & rhs) {
        root = copy(rhs.root);
    }
    // BstMap & operator=(const BstMap & rhs) {
    //     if (this != &rhs) {
    //         BstMap temp(rhs);
    //         destroy(root);
    //         root = temp.root;
    //     }
    //     return *this;
    // }
    BstMap & operator=(const BstMap & rhs) {
        if (this != &rhs) {
            destroy(root);
            root = copy(rhs.root);
        }
        return *this;
    }

    virtual ~BstMap<K,V>() {
        destroy(root);
        root = NULL;
    }
    void print() {
        inOrder(root);
        std::cout << std::endl;
    }
};

#endif