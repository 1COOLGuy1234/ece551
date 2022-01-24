#ifndef __STORY_HPP__
#define __STORY_HPP__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <assert.h>
#include <exception>
#include <queue>
#include <map>
#include <algorithm>
#include "page.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::queue;
using std::map;

class Story {
private:
    string path;     // the file path of the story
    vector<Page> story;  // the content of the story, consist of some pages
    vector<vector<Page> > win_path;  // all winning path of this story
    vector<vector<string> > choice_path;  // all choice you should make to win
    map<size_t,size_t> page_depth; // store each page's smallest depth in this story
    string getPagePath(const string & directory, int page_num);  // a helper function: get the directory name and page index, build the page file path
    bool isFileExist(const string & filename); // check if the file is exist or not
    bool isStoryValid();  // check if the format of this story is valid
    bool isOutofRange(string & input, int low, int high); // check if the user input a invalid choice
    void insertPage(const Page & p, size_t page_num);  // a helper function: insert one page into this story
    void calculatePageDepth();  // a helper function: calculate the page depth
    void calculateWinPath();   // a helper function: calculate the winning path of this story 
    void calculateChoicePath(); // a helper function: calculate all choices you should make to win this story
    void dfs(vector<vector<Page> > & ways, vector<Page>way,  map<size_t, int> & the_map, vector<size_t> visited, Page & thispage); // a helper function, use dfs to search the story
public:
    Story(const string & directory);
    ~Story() {}
    void startStory();   // start this CYOA
    map<size_t,size_t> getPageDepth();  // get the private field: page_depth
    size_t getPageNum(); // get the number of pages in this story
    vector<vector<Page> > getWinPath();  // get the private field: win_path
    vector<vector<string> > getChoicefromPath(); // get the private field: choice_path
    void printWinPath();  // print all winning paths
};



#endif