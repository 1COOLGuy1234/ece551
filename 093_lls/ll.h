#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

class myException : public std::exception {
public:
	virtual const char * what() const throw() { 
  	return "The element is inaccessible!\n"; 
  }
};

template<typename T>
class LinkedList {
private:
    class Node {
    public:
        T data;
        Node * next;
        Node * prev;
        Node() : data(0), next(NULL), prev(NULL) {}
        Node(const T & item) : data(item), next(NULL), prev(NULL) {}
        Node(const T & item, Node * n1, Node * n2) : data(item), next(n1), prev(n2) {}
    };
    Node * head;
    Node * tail;
    int size;

public:
    LinkedList() : head(NULL), tail(NULL), size(0) {}
    LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(0) {
        Node * temp = rhs.tail;
        while (temp != NULL) {
            this->addFront(temp->data);
            temp = temp->prev;
        }
    }
    LinkedList & operator=(const LinkedList & rhs) {
        if (this != &rhs) {
            while (head != NULL) {
                Node * temp = head->next;
                delete head;
                head = temp;
            }
            tail = NULL;
            size = 0;
            Node * curr = rhs.tail;
            while (curr != NULL) {
                this->addFront(curr->data);
                curr = curr->prev;
            }
            size = rhs.size;
        }
        return *this;
    }
    ~LinkedList() {
        while (head != NULL) {
            Node * temp = head->next;
            delete head;
            head = temp;
        }
        // tail = NULL;
        // size = 0;
    }

    void addFront(const T & item) {
        head = new Node(item, head, NULL); // prev is NULL
        if (tail == NULL) {  // this is the first node
            tail = head;
        }
        else {
            head->next->prev = head;  // doubly linkedlist need to update old head's prev
        }
        size++;
    }

    void addBack(const T & item) {
        tail = new Node(item, NULL, tail);
        if (head == NULL) {
            head = tail;
        }
        else {
            tail->prev->next = tail;
        }
        size++;
    }

    bool remove(const T & item) {
        if (head == NULL) {
            return false;
        }
        if (head->data == item) {
            Node * temp = head->next;
            delete head;
            head = temp;
            if (head != NULL) {
                head->prev = NULL;
            }
            else {   // remove the last one
                tail = NULL;
            }
            size--;
            return true;
        }
        Node * curr = head;
        while (curr->next != NULL) {
            if (curr->next->data == item) {
                Node * temp = curr->next;
                curr->next = curr->next->next;
                delete temp;
                if (curr->next != NULL) {
                    curr->next->prev = curr;
                }
                else {
                    tail = curr;
                }
                size--;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    T & operator[](int index) {
        if (index < 0 || index >= size) {
            throw myException();
        }
        
        Node * curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }

    const T & operator[](int index) const {
        if (index < 0 || index >= size) {
            throw myException();
        }
        
        Node * curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }

    int find(const T & item) {
        int idx = 0;
        Node * curr = head;
        while (curr != NULL) {
            if (curr->data == item) {
                return idx;
            }
            else {
                curr = curr->next;
                idx++;
            }
        }
        return -1;
    }

    int getSize() const {
        return size;
    }
};

#endif
