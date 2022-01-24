#include "rand_story.h"

/*
print the error information to stderr
@param
msg: the error information
*/
void printError(const char * msg) {
    fprintf(stderr, "Wrong: %s\n", msg);
    exit(EXIT_FAILURE);
}


/*
Open the file the test if it succeed
@param
filename: the name of file that should be opend
@return
the FILE * pointer to this file
*/
FILE * openFileRead(const char * filename) {
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        printError("Open file failed!");
    }
    return f;
}


/*
Close file and test if it succeed
@param
f: the file pointer
*/
void closeFile(FILE * f) {
    if (fclose(f) != 0) {
        fprintf(stderr, "failed to close input\n");
    }
}


/*
Use getline to read the story template file and put the content into the story struct
@param:
f: the file pointer
@return:
The story struct which contains the file template
*/
story readStory(FILE * f) {
    story ret = {NULL, 0};
    char ** lines = NULL;
    char * curr = NULL;
    size_t sz = 0;
    size_t lines_sz = 0;
    while (getline(&curr, &sz, f) >= 0) {
        lines = realloc(lines, (lines_sz+1) * sizeof(*lines));
        lines[lines_sz++] = curr;
        curr = NULL;
    }
    free(curr);
    ret.lines = lines;
    ret.lines_sz = lines_sz;
    return ret;
}


/*
print the story content in stdin
@param:
sto: the story
*/
void printStory(story sto) {
    for (size_t i = 0; i < sto.lines_sz; i++) {
        printf("%s", sto.lines[i]);
    }
}


/*
free the memory applied for the story
@param:
sto: the story
*/
void freeStory(story sto) {
    for (size_t i = 0; i < sto.lines_sz; i++) {
        free(sto.lines[i]);
    }
    free(sto.lines);
}


/*
judge if it is the '_'
@param: 
c: the character 
@return:
if c is _, return 1, else return 0
*/
int isUnderline(char c) {
    if (c == '_') {
        return 1;
    }
    else {
        return 0;
    }
}


/*
Check if the story template is valid, i.e. the number of '_' is even
@param:
sto: the story
@return:
1: File is valid;
0: File is invalid;
*/
int checkInputFile(story sto) {
    int ret = 1; // default: file is valid
    size_t underline_num = 0; // number of '_' per line
    for (size_t i = 0; i < sto.lines_sz; i++) {
        underline_num = 0;  // refresh underline_num, check the next line
        char * line_ptr = sto.lines[i];
        // calculate underline_num
        while(*line_ptr != '\0') {
            if (isUnderline(*line_ptr)) {
                underline_num++;
            }
            line_ptr++;
        }
        if (underline_num % 2 == 1) {   // if '_' occurs odd times, it is invalid
            ret = 0;
            break;
        }
    }
    return ret;
}

/*
@param:
line: the line that need to be replaced with
pos1: the pointer point to the first '_'
pos2: the pointer point to the second '_'
replaceWord: use this word to replace
@return:
the pointer to the new line that has been replaced
*/
char * replaceWord(char * line, char * pos1, char * pos2, const char * replaceWord) {
    size_t line_sz = strlen(line);
    // for example :_blank_
    // category_length = 5 
    size_t category_length = pos2 - pos1 - 1;
    int diff = category_length + 2 - strlen(replaceWord);  // +2: add two '_'
    size_t new_line_sz = line_sz - diff;
    char * newline = malloc((new_line_sz + 1) * sizeof(*newline));  // apply memory for new line
    
    char * line_ptr = line;
    char * newline_ptr = newline;
    const char * replaceWord_ptr = replaceWord;
    char * right_substring_ptr = pos2 + 1;

    // assign the left substring to newline
    while (line_ptr != pos1) {
        *newline_ptr = *line_ptr;
        newline_ptr++;
        line_ptr++;
    }

    // assign the word
    while (*replaceWord_ptr != '\0') {
        *newline_ptr = *replaceWord_ptr;
        newline_ptr++;
        replaceWord_ptr++;
    }

    // assign the right substring to newline

    while(*right_substring_ptr != '\0') {
        *newline_ptr = *right_substring_ptr;
        newline_ptr++;
        right_substring_ptr++;
    }
    *newline_ptr = '\0';

    free(line);  // free old line
    return newline;  // assign new line
}


/*
Get the content between two '_'
Note: the return pointer need to be freed
@param:
pos1: the first '_'
pos2: the second '_'
@return:
the pointer point to the string between '_'
*/
char * getBlankName(char * pos1, char * pos2) {
    size_t len = pos2 - pos1 - 1;
    char * ret = strndup(pos1+1, len);
    if (ret == NULL) {
        printError("Strdup failed!");
    }
    return ret;
}


/*
Judge if the content between two '_' is a valid integer
@param:
the string need to be judged
@return:
1: if the string is valid integer
0: if the string is invalid integer  
*/
int isInteger(char * str) {
    if (*str == '\0') {
        return 0;
    }
    while (*str != '\0') {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}


/*
parse the story: replace the blank with cat in step1
@param:
sto: the story
*/
void parseStoryStep1(story sto) {
    char ** data = sto.lines;
    size_t size = sto.lines_sz;
    char * pos1 = NULL; // point to the first '_'
    char * pos2 = NULL; // point to the second '_'
    for (size_t i = 0; i < size; i++) {  // traverse each line
        while(strchr(data[i], '_') != NULL) {
            pos1 = strchr(data[i], '_');
            pos2 = strchr(pos1+1, '_');
            data[i] = replaceWord(data[i], pos1, pos2, chooseWord("DONTCARE", NULL)); 
        }
    }
}


/*
Free the memory applied for the category
@param:
cat: the category needed to be free
*/
void freeCatagory(category_t * cat) {
    free(cat->name);
    for (size_t i = 0; i < cat->n_words; i++) {
        free(cat->words[i]);
    }
    free(cat->words);
}


/*
Use getline to read the words file and put the content into the words struct
@param:
f: the file pointer
@return:
The words struct which contains the words file content
*/
words readWords(FILE * f) {
    words ret = {NULL, 0};
    char ** lines = NULL;
    char * curr = NULL;
    size_t sz = 0;
    size_t lines_sz = 0;
    while (getline(&curr, &sz, f) >= 0) {
        lines = realloc(lines, (lines_sz+1) * sizeof(*lines));
        lines[lines_sz++] = curr;
        curr = NULL;
    }
    free(curr);
    ret.words = lines;
    ret.words_sz = lines_sz;
    return ret;
}


/*
free the memory applied for the words
@param:
wo: the words
*/
void freeWords(words wo) {
    for (size_t i = 0; i < wo.words_sz; i++) {
        free(wo.words[i]);
    }
    free(wo.words);
}

/*
Check if the line in words file is valid, i.e, contains ':'
@param:
line: the line needed to be checked
@return:
1: Line is valid
0: Line is invalid
*/
int checkLine(char * line) {
    while(*line != '\0') {
        if (*line == ':') {
            return 1;
        }
        line++;
    }
    return 0;
}


/*
Get the index of cats->arr corresponding to category
@param:
category: the category
cats: the catarray_t where we need find the category
@return:
the index of cats->arr: if found this category
-1: if the category is not in this catarray_t
*/
int getCategoryIndex(char * category, catarray_t * cats) {
    for (size_t i = 0; i < cats->n; i++) {
        if (strcmp(cats->arr[i].name, category) == 0) {
            return i;
        }
    }
    return -1;
}

/*
Get the index of c->words corresponding to word
@param:
word: the word
c: the category_t where we need find the word
@return:
the index of c->words: if found this word
-1: if the word is not in this category_t
*/
int getWordIndex(char * word, category_t * c) {
    for (size_t i = 0; i < c->n_words; i++) {
        if (strcmp(c->words[i], word) == 0) {
            return i;
        }
    }
    return -1;
}


/*
Parse the line in words.txt, put the content in cats
@param:
line: the line needed to be parsed
cats: After parsing, put the category and word in cats
*/
void parseLine(char * line, catarray_t * cats) {
    char * category = NULL;
    char * word = NULL;
    if (!checkLine(line)) {
        printError("This line is invalid!\n");
    }
    char * first_colon = strchr(line, ':');
    size_t category_len = first_colon - line;
    size_t word_len = strlen(line) - category_len - 1;
    category = strndup(line, category_len);   // if not used, need to be free
    if (category == NULL) {
        printError("Strdup failed!");
    }
    word = strndup(first_colon+1, word_len);  // if not used, need to be free
    if (word == NULL) {
        printError("Strdup failed!");
    }
    stripNextLine(word);
    // check if there is category in cats
    if (getCategoryIndex(category, cats) == -1) { // IF NO : add new category and init it
        cats->arr = realloc(cats->arr, (cats->n + 1) * sizeof(*cats->arr));
        cats->n++;
        cats->arr[cats->n-1].name = category;
        cats->arr[cats->n-1].n_words = 1;
        cats->arr[cats->n-1].words = malloc(cats->arr[cats->n-1].n_words * sizeof(*(cats->arr[cats->n-1].words)));
        cats->arr[cats->n-1].words[cats->arr[cats->n-1].n_words-1] = word;
    }
    else {  // check if there is word in this category
        int idx = getCategoryIndex(category, cats);
        free(category);
        if (getWordIndex(word, &(cats->arr[idx])) == -1) { // IF NO, add new word
            cats->arr[idx].words = realloc(cats->arr[idx].words, (cats->arr[idx].n_words+1) * sizeof(*(cats->arr[idx].words)));
            cats->arr[idx].n_words++;
            cats->arr[idx].words[cats->arr[idx].n_words-1] = word;
        }
        else {  // do nothing but free the word
            free(word);
        }
    }
}


/*
Free the memory for the cats
@param:
cats: the catarry_t would be freed
*/
void freeCats(catarray_t * cats) {
    for (size_t i = 0; i < cats->n; i++) {
        free(cats->arr[i].name);
        for (size_t j = 0; j < cats->arr[i].n_words; j++) {
            free(cats->arr[i].words[j]);
        }
        free(cats->arr[i].words);
    }
    free(cats->arr);
}


/*
Print the words in std.
Used for debugging
@param:
wo: the wo
*/
void displayWords(words wo) {
    for (size_t i = 0; i < wo.words_sz; i++) {
        printf("%s", wo.words[i]);
    }
}


/*
remove the first '\n' of the line 
use this function with the result of getline, which only has one '\n'
@param:
line: the line
*/
void stripNextLine(char * line) {
    if (strchr(line, '\n')) {
        char * pch = strchr(line, '\n');
        *pch = '\0';
    }
}


/*
Parsing the story: use the word in cats to fill the blank in story template
@param:
sto: the story needed to be parsed
cats: the words stored here
isN: if add -n, DO NOT use the word repeatedly
*/
void parseStory(story sto, catarray_t * cats, int isN) {
    char ** data = sto.lines;
    size_t size = sto.lines_sz;
    char * pos1 = NULL; // point to the first '_'
    char * pos2 = NULL; // point to the second '_'
    char * replace_word = NULL;
    char * blank_name = NULL;

    // initial history
    category_t history = {NULL, NULL, 0};

    for (size_t i = 0; i < size; i++) {  // parse story line by line
        while(strchr(data[i], '_') != NULL) {   // fill all blank in one line
            pos1 = strchr(data[i], '_');
            pos2 = strchr(pos1+1, '_');
            blank_name = getBlankName(pos1, pos2); // need free
            if (isInteger(blank_name)) {              // if Integer, search the history
                int integer = atoi(blank_name);
                // test if integer > 0
                if ((integer >= 1) && (integer <= (&history)->n_words)) {
                    replace_word = strdup((&history)->words[(&history)->n_words - integer]);
                    if (replace_word == NULL) {
                        printError("Strdup failed!");
                    }
                    data[i] = replaceWord(data[i], pos1, pos2, replace_word); 
                    // maintain history
                    (&history)->words = realloc((&history)->words, ((&history)->n_words + 1) * sizeof(*((&history)->words)));
                    (&history)->words[(&history)->n_words] = replace_word;
                    (&history)->n_words++;
                }
                else {
                    printError("Can't search this word in history");
                }
            }
            else if (getCategoryIndex(blank_name, cats) != -1){   // if category name, search the cats
                int idx = getCategoryIndex(blank_name, cats);
                replace_word = strdup(chooseWord(cats->arr[idx].name, cats));
                if (replace_word == NULL) {
                    printError("Strdup failed!");
                }
                data[i] = replaceWord(data[i], pos1, pos2, replace_word); 
                // if isN == 1, remove the word
                if (isN) {
                    removeWord(replace_word, &(cats->arr[idx]));
                }
                // maintain history
                (&history)->words = realloc((&history)->words, ((&history)->n_words + 1) * sizeof(*((&history)->words)));
                (&history)->words[(&history)->n_words] = replace_word;
                (&history)->n_words++;
            }  
            else {  // invalid blank name
                printError("The blank name is invalid!");
            }
            free(blank_name);
        }
    }
    // free history
    for (size_t i = 0; i < (&history)->n_words; i++) {
        free((&history)->words[i]);
    }
    free((&history)->words);
}


/*
If the non-repeat version, we call this function to remove the word we used
@param:
word: the word we just used (need to be removed in category_t)
cat: the category store the word
*/
void removeWord(char * word, category_t * cat) {
    int idx = getWordIndex(word, cat);
    // swap
    char * temp = cat->words[idx];
    cat->words[idx] = cat->words[cat->n_words-1];
    cat->words[cat->n_words-1] = temp;
    // remove the last one
    free(cat->words[cat->n_words-1]);
    cat->words = realloc(cat->words, (cat->n_words-1) * sizeof(*(cat->words)));
    cat->n_words--;
}


/*
Test the command line argument in step4
@param:
argc: the argc in main
argv: the argv in main
@return:
0: if argc == 3
1: if argc == 4 && the second argument is "-n"
exit with failure: other cases
*/
int checkParamStep4(int argc, char ** argv) {
    if (argc == 3) {
        return 0;
    }
    else if (argc == 4) {  // ./story-step4 -n words.txt story.txt
        if (strcmp(argv[1], "-n") != 0) {  
            printError("The second paramter shoud be -n!");
        }
        else {
            return 1;
        }
    }
    else {
        printError("Worng use in story-step4!");
    }
    exit(EXIT_FAILURE);
}