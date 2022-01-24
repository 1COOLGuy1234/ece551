#include "bstset.h"

int main() {
    BstSet<int> first;
    // test add
    first.add(1);
    first.add(2);
    first.add(5);
    first.add(8);
    first.add(4);
    first.add(3);
    first.add(10);
    first.print();
    // test remove
    first.remove(5);
    first.remove(3);
    first.print();
    // test contains
    if (first.contains(8)) {
        std::cout << "contains Node 8!" << first.contains(8) << std::endl;
    }
    if (first.contains(5)) {
        std::cout << "exist Node 5!" << first.contains(5) << std::endl;
    }
    return EXIT_SUCCESS;
}