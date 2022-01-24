#include <cassert>
#include <cstdlib>
#include "il.hpp"

void testList(void) {
    IntList list1;
    // test intialize
    assert(list1.size == 0 && list1.getSize() == 0 && list1.head == NULL && list1.tail == NULL);
    // test addFront
    list1.addFront(1);
    assert(list1.head->data == 1 && list1.head->next == NULL && list1.head->prev == NULL);
    assert(list1.tail->data == 1 && list1.tail->next == NULL && list1.tail->prev == NULL);
    assert(list1.size == 1 && list1.getSize() == 1);
    assert(list1[0] == 1 && list1.find(1) == 0);
    // test addBack
    list1.addBack(2);
    assert(list1.head->data == 1 && list1.head->next->data == 2 && list1.head->prev == NULL);
    assert(list1.tail->data == 2 && list1.tail->next == NULL && list1.tail->prev->data == 1);
    assert(list1.size == 2 && list1.getSize() == 2);
    assert(list1[0] == 1 && list1.find(1) == 0);
    assert(list1[1] == 2 && list1.find(2) == 1);
    assert(list1.head->next->next == NULL);
    assert(list1.head == list1.head->next->prev);
    assert(list1.tail == list1.head->next);
    // test =
    IntList list2;
    list2 = list1;
    assert(list2.head->data == 1 && list2.head->next->data == 2 && list2.head->prev == NULL);
    assert(list2.tail->data == 2 && list2.tail->next == NULL && list2.tail->prev->data == 1);
    assert(list2.size == 2 && list2.getSize() == 2);
    assert(list2[0] == 1 && list2.find(1) == 0);
    assert(list2[1] == 2 && list2.find(2) == 1);
    assert(list2.head->next->next == NULL);
    assert(list2.head == list2.head->next->prev);
    assert(list2.tail == list2.head->next);
    // test copy constructor
    IntList list3(list1);
    assert(list3.head->data == 1 && list3.head->next->data == 2 && list3.head->prev == NULL);
    assert(list3.tail->data == 2 && list3.tail->next == NULL && list3.tail->prev->data == 1);
    assert(list3.size == 2 && list3.getSize() == 2);
    assert(list3[0] == 1 && list3.find(1) == 0);
    assert(list3[1] == 2 && list3.find(2) == 1);
    assert(list3.head->next->next == NULL);
    assert(list3.head == list3.head->next->prev);
    assert(list3.tail == list3.head->next);
    // remove
    list1.remove(1);
    list1.remove(2);
    assert(list1.size == 0 && list1.getSize() == 0);
    list1.addFront(1);
    list1.addFront(2);
    list1.addFront(3);
    list1.addFront(4);
    list1.addFront(2);
    list1.addFront(2);
    assert(list1[0] == 2 && list1[1] == 2 && list1[2] == 4 && list1[3] == 3);
    assert(list1.size == 6 && list1.getSize() == 6);
    bool temp = list1.remove(2);
    assert(list1.size == 5 && list1.getSize() == 5);
    assert(temp == true);
    assert(list1[0] == 2 && list1[3] == 2);
    assert(list1.head->data == 2);
    assert(list1.head->next->data == 4);
    temp = list1.remove(7);
    assert(temp == false);
    int f1 = list1.find(2);
    assert(f1 == 0);
    int f2 = list1.find(4);
    assert(f2 == 1);
    int f3 = list1.find(7);
    assert(f3 == -1);

    list1.addBack(5);
    list1.addBack(10);
    assert(list1.size == 7 && list1.getSize() == 7);
    assert(list1[5] == 5 && list1[6] == 10);
    // remove l2
    list2.remove(2);
    list2.remove(1);
    assert(list2.size == 0 && list2.getSize() == 0 && list2.head == NULL && list2.tail == NULL);
    // Inlist l3:21 change to 1
    list3.remove(2);
    assert(list3.getSize() == 1 && list3.size == 1 && list3.head == list3.tail && list3.head != NULL);
    assert(list3[0] == 1);
    assert(list3.head->next == NULL && list3.head->prev == NULL);

    IntList l1;
    l1.addFront(4);
    l1.addFront(5);
    l1.addBack(3);
    // copy constructor
    IntList l2(l1);
    l2[1] = 2;
    l2[1] = 4;
    // assignment operator
    IntList l3;
    l3 = l1;
    l3[1] = 2;
    assert(l3.find(2) == 1);
    assert(l3.find(4) == -1);
    assert(l3.size == 3 && l3.getSize() == 3);
    l3[1] = 4;
    // remove
    assert(l3.remove(4));
    assert(l3.size == 2 && l3.getSize() == 2);
    assert(l3[0] == 5 && l3[1] == 3);
    // l2 = l3
    l2 = l3;
    assert(l2.head != l3.head);
    assert(l2.size == 2 && l2.getSize() == 2);
    assert(l2.head->next == l2.tail);
    assert(l2.tail->prev == l2.head);
    assert(l2[0] == 5 && l2[1] == 3);
    // remove
    assert(l3.remove(0) == false);
    assert(l3.head->next == l3.tail);
    assert(l3.tail->prev == l3.head);
    assert(l3.size == 2 && l3.getSize() == 2);
    assert(l3[0] == 5 && l3[1] == 3);
    assert(l3.remove(5));
    assert(l3.head == l3.tail);
    assert(l3.head->next == NULL && l3.tail->prev == NULL);
    assert(l3.size == 1 && l3.getSize() == 1);
    assert(l3[0] == 3);
    assert(l3.remove(3));
    assert(l3.head == NULL && l3.tail == NULL);
    assert(l3.getSize() == 0 && l3.size == 0);

}

int main(void) {
    testList();
    return EXIT_SUCCESS;
}