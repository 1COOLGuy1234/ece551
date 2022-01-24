#include "page.hpp"
#include "util.hpp"

/**
 * @brief when it is a choice page, judge if the choice is positive integer greater than 0
 * @param str the content before the first colon
 * @return if the choice is valid positive integer, return true. Otherwise, return false
*/
bool Page::isNumValid(string & str) {
    for (auto it = str.begin(); it != str.end(); ++it) {
        if (!isdigit(*it)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief get the content before the first colon
 * @param str a line in navigation section
 * @return the content before the first colon
*/
string Page::getChoice(const string & str) const {
    size_t colon_pos = str.find(':');
    string res = str.substr(colon_pos+1);
    return res;
}

/**
 * @breif: check if the page is valid
 * @return if the page is valid, return true. Otherwise, print error information and exit failure
*/
bool Page::isPageValid() {
    // get file content
    std::ifstream ifs;
    ifs.open(path);
    if (ifs.fail()) {
        printError("Open file failed!");
    }
    vector<string> content;
    string line;
    while (getline(ifs, line)) {
        content.push_back(line);
    }
    ifs.close();
    // check # exist
    bool is_pound_exist = false;
    for (auto it = content.begin(); it != content.end(); ++it) {
        if (*((*it).begin()) == '#') {
            is_pound_exist = true;
        }
    }
    if (is_pound_exist == false) {
        printError("There is no pound in this page at all!");
    }
    // navigation section check
    if (choice.size() == 0) {
        printError("There is no navigation section is this page!");
    }
    // check if WIN
    if (*(choice.begin()) == "WIN") {
        if (choice.size() != 1) {
            printError("Although the first line is WIN, there are other redunant information!");
        }
        return true;
    }
    // check if lose
    if (*(choice.begin()) == "LOSE") {
        if (choice.size() != 1) {
            printError("Although the first line is LOSE, there are other redunant information!");
        }
        return true;
    }
    // make choice section
    for (auto it = choice.begin(); it != choice.end(); ++it) {
        // check if choice
        size_t colon_pos = (*it).find(':');
        if (colon_pos == string::npos || colon_pos == 0) {
            printError("There is no colon or no choice before the colon!");
        }
        string num_str = (*it).substr(0, colon_pos);
        if (!isNumValid(num_str)) {
            printError("The choice before the colon is not a strict positive integer!");
        }
    }
    return true;
}


/**
 * @brief print the content after the navigation section, i.e. the text section
*/
void Page::printText() const {
    for (auto it = text.begin(); it != text.end(); ++it) {
        cout << *it << endl;
    }
}


/**
 * @brief the constructor of Page class
 * read the content from the specific file, check if it is valid 
*/
Page::Page(const string & filename) : navigation_category(0), path(filename) {
    // open file
    std::ifstream ifs;
    ifs.open(path);
    if (ifs.fail()) {
        printError("Open file failed!");
    }
    // get the page file content
    string line;
    while(getline(ifs, line) && *(line.begin()) != '#') {  // when read the line begin with '#', skip this line
        choice.push_back(line);
    }
    line.clear();
    while(getline(ifs, line)) {
        text.push_back(line);
    }
    ifs.close();
    if (!isPageValid()) {
        printError("This page is not valid!");
    }
    // assign the navigation_category
    if (*(choice.begin()) == "WIN") {
        navigation_category = 1;
    }
    else if (*(choice.begin()) == "LOSE") {
        navigation_category = 2;
    }
    else {
        navigation_category = 3;
    }
    if (navigation_category == 0) {
        printError("The page has a wrong navigation_category!");
    }
    // when it is a choice page, initial point_to array
    if (navigation_category == 3) {
        for (auto it = choice.begin(); it != choice.end(); ++it) {
            size_t colon_pos = (*it).find(':');
            string num_str = (*it).substr(0, colon_pos);
            point_to.push_back(stoi(num_str));
        }
    }
}

/**
 * @brief print the page according to the requirement of step1
*/
void Page::printPage() const {
    if (navigation_category == 1) {
        printText();
        cout << endl;
        cout << "Congratulations! You have won. Hooray!" << endl;
    }
    else if (navigation_category == 2) {
        printText();
        cout << endl;
        cout << "Sorry, you have lost. Better luck next time!" << endl;
    }
    else if (navigation_category == 3) {
        printText();
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << endl;
        assert(choice.size() >= 1);
        for (size_t i = 1; i <= choice.size(); i++) {
            cout << " " << std::to_string(i) << ". " << getChoice(choice[i-1]) << endl;
        }
    }
    else {
        printError("The navigation category is wrong!");
    }
}


/**
 * @brief get the private field: point_to
 * @return which page this page can jump to. If this page is WIN or LOSE, the vector is empty
*/
vector<int> Page::getPointTo() const {
    return point_to;
}


/**
 * @brief get the private field: navigation_category
 * @return 1: win 2:lose 3:choice
*/
int Page::getCategory() const {
    return navigation_category;
}


/**
 * @brief assign the private field: page_index
*/
void Page::assignPageIndex(size_t page_num) {
    page_index = page_num;
}

/**
 * @brief get the private field: page_index
 * @return the page index in the story
*/
size_t Page::getPageIndex() {
    return page_index;
}


