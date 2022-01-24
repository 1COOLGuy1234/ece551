#include "rand_story.h"

int main(int argc, char ** argv) {
    int isN = checkParamStep4(argc, argv);
    catarray_t cats = {NULL, 0};
    FILE * f = NULL;
    // read words file
    f = isN ? openFileRead(argv[2]) : openFileRead(argv[1]);
    words wo = readWords(f);
    closeFile(f);
    // read story template
    f = isN ? openFileRead(argv[3]) : openFileRead(argv[2]);
    story sto = readStory(f);
    closeFile(f);
    // get cats
    for (size_t i = 0; i < wo.words_sz; i++) {
        parseLine(wo.words[i], &cats);
    }
    // parse story and print it
    parseStory(sto, &cats, isN);
    printStory(sto);
    // free memory
    freeStory(sto);
    freeWords(wo);
    freeCats(&cats);
    return EXIT_SUCCESS;
}