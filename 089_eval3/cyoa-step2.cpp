#include "story.hpp"
#include "util.hpp"

int main(int argc, char ** argv) {
    if (argc != 2) {
        printError("The wrong use of cyoa-step2! Correct: ./cyoa-step2 directoryname");
    }
    Story this_story(argv[1]);
    this_story.startStory();
    return EXIT_SUCCESS;
}