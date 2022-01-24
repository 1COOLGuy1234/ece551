#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// store the story template
struct _story {
    char ** lines;
    size_t lines_sz;
};
typedef struct _story story;

// almost the same as story, but more readible
struct _words {
    char ** words;
    size_t words_sz;
};
typedef struct _words words;


struct _word {
    char * category;
    char * word;
};
typedef struct _word word;

void printError(const char * msg);

FILE * openFileRead(const char * filename);

void printStory(story sto);

void closeFile(FILE * f);

story readStory(FILE * f);

void freeStory(story sto);

int isUnderline(char c);

int checkInputFile(story sto);

char * replaceWord(char * line, char * pos1, char * pos2, const char * replaceWord);

void parseStoryStep1(story sto);

words readWords(FILE * f);

void freeWords(words wo);

int checkLine(char * line);

int getCategoryIndex(char * category, catarray_t * cats);

int getWordIndex(char * word, category_t * c);

void parseLine(char * line, catarray_t * cats);

void freeCats(catarray_t * cats);

void displayWords(words wo);

void stripNextLine(char * line);

void freeCatagory(category_t * cat);

char * getBlankName(char * pos1, char * pos2);

int isInteger(char * str);

void parseStory(story sto, catarray_t * cats, int isN);

void removeWord(char * word, category_t * cat);

int checkParamStep4(int argc, char ** argv);

#endif
