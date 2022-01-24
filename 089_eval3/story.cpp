#include "story.hpp"
#include "util.hpp"


/**
 * @brief a helper function: get the directory name and page index, build the page file path
 * @param directory the path of the story directory
 * @param page_index the path index
 * @return the path of page which index is page_index
*/
string Story::getPagePath(const string & directory, int page_index) {
    return directory + "/page" +std::to_string(page_index) + ".txt";
}

/**
 * @brief check if the file is exist or not
 * @param filename the name of the file will be checked
 * @return if the file exists, return true. Otherwise, return false
*/
bool Story::isFileExist(const string & filename) {
    std::ifstream f(filename.c_str());
    return f.good();
}

/**
 * @brief check if the format of this story is valid
 * @return if the story format is valid, return true. Otherwise, print error information and exit failure
*/
bool Story::isStoryValid() {  // has problem in 4b?
    // check every page that is referenced by a choice is valid
    int N = story.size();    // page1 - pageN
    vector<bool> pointed_by(N, false);      // record if this page has been referenced
    for (auto it = story.begin(); it != story.end(); ++it) {
        vector<int> page_point_to = (*it).getPointTo();
        if (page_point_to.size() == 0) {
            continue;
        }
        for (auto itp = page_point_to.begin(); itp != page_point_to.end(); ++itp) {
            if (*itp > N) {
                printError("The jump index is out of range!");
            }
            else {
                pointed_by[*itp-1] = true;
            }
        }
    }
    // check Every page (except page 1) is referenced by at least one *other* page's choices
    for (int i = 1; i < N; i++) {
        if (pointed_by[i] == false) {
            printError("there are some pages are not referenced by any page!");
        }
    }
    // check if at least one WIN and one LOSE
    int cnt_win = 0;
    int cnt_lose = 0;
    for (auto it = story.begin(); it != story.end(); ++it) {
        if ((*it).getCategory() == 1) {
            cnt_win++;
        }
        if ((*it).getCategory() == 2) {
            cnt_lose++;
        }
    }
    if (cnt_win == 0 || cnt_lose == 0) {
        printError("There is no WIN page or LOSE page!");
    }
    return true;
}


/**
 * @brief check if the user input a invalid choice
 * @param input the user input
 * @param low the lower bound of choice
 * @param high the upper bound of choice
 * @return if the user input is invalid, return true. Otherwise, return false
*/
bool Story::isOutofRange(string & input, int low, int high) {
    if (input.empty()) {
        return true;
    }
    for (auto it = input.begin(); it != input.end(); ++it) {
        if (!isdigit(*it)) {
            return true;
        }
    }
    int integer = stoi(input);
    if (integer >= low && integer <= high) {
        return false;
    }
    return true;
}

/**
 * @brief a helper function: insert one page into this story
 * @param p the page needed to be inserted
 * @param page_index the index of this page in this story
*/
void Story::insertPage(const Page & p, size_t page_index) {
    story.push_back(p);
    story.back().assignPageIndex(page_index);
}

/**
 * @brief a helper function: calculate the winning path of this story 
 * algorithm: DFS
 * backtrace
*/
void Story::calculateWinPath() {
    // build a map <page_index, navigation_category>
    map<size_t, int> my_map;
    for(auto it = story.begin(); it != story.end(); ++it) {
        my_map[(*it).getPageIndex()] = (*it).getCategory();
    }
    vector<size_t> visited_page;  
    vector<Page> way;       // store one specific way
    dfs(win_path, way, my_map, visited_page, story[0]);
}

/**
 * @brief a helper function: calculate all choices you should make to win this story
*/
void Story::calculateChoicePath() {
    for (auto it = win_path.begin(); it != win_path.end(); ++it) {  // it => one path
        vector<string> choice;
        for (auto it1 = (*it).begin(); it1 != (*it).end(); ++it1) {
            if (it1 == (*it).end()-1) {  // last page
                assert(it1->getCategory() == 1);
                choice.push_back("win");
                break;
            }
            vector<int> this_point_to = (*it1).getPointTo();
            for (size_t i = 0; i < this_point_to.size(); i++) {
                if (this_point_to[i] == int((*(it1+1)).getPageIndex())) {  // 
                    choice.push_back(std::to_string(i+1));
                }
            }
        }
        choice_path.push_back(choice);
    }
}

/**
 * @brief a helper function, use dfs to search the story to get the win path
 * @param ways store all win paths. If the current way meet the requirement, add it into ways
 * @param way the current way DFS is searching
 * @param the_map a map <page_index, navigation_category>
 * @param visited store which pages has been visited, avoid repetition
 * @param thispage the page the dfs is searching, you could take this as a node
*/
void Story::dfs(vector<vector<Page> > & ways, vector<Page>way, map<size_t, int> & the_map, vector<size_t> visited, Page & thispage) {
    // recursion end condition
    if (the_map[thispage.getPageIndex()] == 1) {   // if the page is win, add it in way, then add way in ways
        way.push_back(thispage);
        ways.push_back(way);
        return;
    }
    if (the_map[thispage.getPageIndex()] == 2) { // if the page is lose, this way will be discard
        return;
    }
    auto it = find(visited.begin(), visited.end(), thispage.getPageIndex());
    if (it != visited.end()) {    // if this page has existed in the path, discard this way
        return;
    }
    // do operation
    way.push_back(thispage);
    visited.push_back(thispage.getPageIndex());
    vector<int> thispage_point_to = thispage.getPointTo();
    for (auto it = thispage_point_to.begin(); it != thispage_point_to.end(); ++it) {
        dfs(ways, way, the_map, visited, story[(*it)-1]);
    }
}

/**
 * @brief the constructor of Story class
*/
Story::Story(const string & directory) : path(directory) {
    if (!isFileExist(getPagePath(path, 1))) {
        printError("Page 1 doesn't exist!");
    }
    insertPage(Page(getPagePath(path, 1)), 1);
    size_t page_num = 2;
    while (isFileExist(getPagePath(path, page_num))) {  // story[0] stores page1
        insertPage(Page(getPagePath(path, page_num)), page_num);  // story[1] stores page2
        page_num++;
    }
    if (!isStoryValid()) {
        printError("The story format is not valid!");
    }
    calculatePageDepth();
    calculateWinPath();
    calculateChoicePath();
    // check if win path dimension == choice path dimension
    assert(win_path.size() == choice_path.size());
    for (size_t i = 0; i < win_path.size(); i++) {
        assert(win_path[i].size() == choice_path[i].size());
    }
}

/**
 * @brief start this CYOA game
*/
void Story::startStory() {
    // print page1
    size_t pageIndex = 0;
    while (story[pageIndex].getCategory() == 3) { // Not win or lose page
        Page & current_page = story[pageIndex];
        current_page.printPage();
        int choice_range = current_page.getPointTo().size();
        // the user input can only be in the range [1, choice_range];
        string input;
        if (!getline(cin,input)) {
            printError("EOF!");
        }
        while (isOutofRange(input, 1, choice_range)) {
            cout << "That is not a valid choice, please try again" << endl;
            if (!getline(cin,input)) {
                printError("EOF!");
            }
        }
        int userChoose = stoi(input);
        // jump to the corresponding page
        pageIndex = current_page.getPointTo()[userChoose-1] - 1;
        assert(pageIndex >= 0 && pageIndex < story.size());
    }
    // WIN or LOSE page
    story[pageIndex].printPage();
}


/**
 * @brief a helper function: calculate the page depth
 * algorithm: BFS
 * the depth of the pages added to the queue will be the depth of the poped page plus one
*/
void Story::calculatePageDepth() {
    queue<Page> my_queue;
    my_queue.push(story[0]); // page1 enqueue
    page_depth[1] = 0;
    while (!my_queue.empty()) {
        Page front = my_queue.front();
        my_queue.pop();
        vector<int> front_point_to = front.getPointTo();
        for (auto it = front_point_to.begin(); it != front_point_to.end(); ++it) {
            my_queue.push(story[(*it)-1]);      // *it-1 because story[0] means page1
            if (page_depth.count(my_queue.back().getPageIndex()) == 0 || page_depth[my_queue.back().getPageIndex()] > page_depth[front.getPageIndex()] + 1) {
                // only this page's index does not exist, or larger than the depth it will be updated, update it
                page_depth[my_queue.back().getPageIndex()] = page_depth[front.getPageIndex()] + 1;
            }
        }
    }
}

/**
 * @brief get the private field: page_depth
 * @return each page's smallest depth in this story
*/
map<size_t,size_t> Story::getPageDepth() {    
    return page_depth;
}

/**
 * @brief get the number of pages in this story
 * @return the number of pages
*/
size_t Story::getPageNum() {
    return story.size();
}

/**
 * @brief get the private field: win_path
 * @return all winning path of this story
*/
vector<vector<Page> > Story::getWinPath() {
    return win_path;
}

/**
 * @brief get the private field: choice_path
 * @return all choice you should make to win
*/
vector<vector<string> > Story::getChoicefromPath() {
    return choice_path;
}

/**
 * @brief print all winning paths according to the requirement of step4
*/
void Story::printWinPath() {
    if (win_path.size() == 0) {
        cout << "This story is unwinnable!" << endl;
        return;
    }
    for (size_t i = 0; i < win_path.size(); i++) {
        for (size_t j = 0; j < win_path[i].size(); j++) {
            if (j != win_path[i].size()-1) {
                cout << (win_path[i][j]).getPageIndex() <<"(" << choice_path[i][j] << "),";
            }
            else {
                cout << (win_path[i][j]).getPageIndex() <<"(" << choice_path[i][j] << ")";
            }
        }
        cout << endl;
    }
}





