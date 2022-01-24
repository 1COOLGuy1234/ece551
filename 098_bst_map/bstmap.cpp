#include "bstmap.h"

int main() {
    BstMap<char, int> first;
    // test add
    first.add('a',0);
    first.add('e',0);
    first.add('f',0);
    first.add('b',0);
    first.add('z',0);
    first.add('h',0);
    first.add('p',0);
    first.print();
    // test remove
    first.remove('a');
    first.remove('z');
    first.print();
    // test lookup
    std::cout << "exist Node f! Value is" << first.lookup('f') << std::endl;
    // test duplicate value
    first.add('f',10);
    std::cout << "exist Node f! Value is" << first.lookup('f') << std::endl;
    return EXIT_SUCCESS;
}