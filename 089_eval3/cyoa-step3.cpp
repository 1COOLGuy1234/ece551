#include "story.hpp"
#include "util.hpp"

int main(int argc, char ** argv) {
    if (argc != 2) {
        printError("The wrong use of cyoa-step3! Correct: ./cyoa-step3 directoryname");
    }
    Story this_story(argv[1]);
    map<size_t,size_t> depth_map = this_story.getPageDepth();
    for (size_t i = 1; i <= this_story.getPageNum(); i++) {
        if (depth_map.count(i) == 0) {
            cout << "Page "<< i << " is not reachable" << endl;
        }
        else {
            cout << "Page " << i << ":" << depth_map[i] << endl;
        }
    }
    return EXIT_SUCCESS;
}