#include "page.hpp"
#include "util.hpp"

int main(int argc, char ** argv) {
    if (argc != 2) {
        printError("The wrong use of cyoa-step1! Correct: ./cyoa-step1 filename");
    }
    Page p1(argv[1]);   // use the file path to instantiate a page obj
    p1.printPage();
    return EXIT_SUCCESS;
}