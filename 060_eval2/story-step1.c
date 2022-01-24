#include "rand_story.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
    if (argc != 2) {
        printError("wrong use of story-step1!\n");
    }
    FILE * f = openFileRead(argv[1]);
    story sto = readStory(f);
    closeFile(f);
    if (!checkInputFile(sto)) {
        printError("The file content is invalid!\n");
    }
    parseStoryStep1(sto);
    printStory(sto);
    freeStory(sto);
    return EXIT_SUCCESS;
}

