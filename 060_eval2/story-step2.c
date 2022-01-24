#include "rand_story.h"

int main(int argc, char ** argv) {
    if (argc != 2) {
        printError("wrong use of story-step2!\n");
    }
    catarray_t cats = {NULL, 0};
    FILE * f = openFileRead(argv[1]);
    words wo = readWords(f);
    closeFile(f);
    for (size_t i = 0; i < wo.words_sz; i++) {
        parseLine(wo.words[i], &cats);
    }
    printWords(&cats);
    freeWords(wo);
    freeCats(&cats);
    return EXIT_SUCCESS;
}