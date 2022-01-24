#include "story.hpp"
#include "util.hpp"

int main(int argc, char ** argv) {
    if (argc != 2) {
        printError("The wrong use of cyoa-step4! Correct: ./cyoa-step4 directoryname");
    }
    Story this_story(argv[1]);
    this_story.printWinPath();
    return EXIT_SUCCESS;
}
