#ifndef __PAGE_HPP__
#define __PAGE_HPP__


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class Page {
private:
    int navigation_category; // 1: win 2:lose 3:choice
    const string path;      // the filepath this page read
    size_t page_index;      // the page index in the story
    vector<string> choice;  // the content of the navigation section
    vector<string> text;    // the content of the text 
    vector<int> point_to;   // which page this page can jump to. If this page is WIN or LOSE, the vector is empty
    bool isNumValid(string & str);   // when it is a choice page, judge if the choice is positive integer greater than 0
    string getChoice(const string & str) const;  // get the content before the first colon
    bool isPageValid();     // judge if the page has valid format
    void printText() const;  // print the text content
public:
    Page(const string & filename); 
    ~Page() {}
    void printPage() const;   
    vector<int> getPointTo() const;  // get the private field: point_to
    int getCategory() const;         // get the private field: navigation_category
    void assignPageIndex(size_t page_num);  // assign the private field: page_index
    size_t getPageIndex();           // get the private field: page_index
};

#endif