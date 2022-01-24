#include "rand_story.h"

int main(int argc, char ** argv) {
    if (argc != 3) {
        printError("wrong use of story-step3!\n");
    }
    catarray_t cats = {NULL, 0};
    // read words file
    FILE * f = openFileRead(argv[1]);
    words wo = readWords(f);
    closeFile(f);
    // read story template
    f = openFileRead(argv[2]);
    story sto = readStory(f);
    closeFile(f);
    // get cats
    for (size_t i = 0; i < wo.words_sz; i++) {
        parseLine(wo.words[i], &cats);
    }
    // parse the story and print it
    parseStory(sto, &cats, 0);
    printStory(sto);
    // free memory
    freeStory(sto);
    freeWords(wo);
    freeCats(&cats);
    return EXIT_SUCCESS;
}