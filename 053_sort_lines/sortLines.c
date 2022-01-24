#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void printError(const char *text){
    fprintf(stderr, "Wrong: %s\n", text);
    exit(EXIT_FAILURE);
}

void readData(FILE *f){
    char **data = NULL;
    char *line = NULL;
    size_t sz = 0;
    int line_num = 0;
    while (getline(&line, &sz, f) >= 0) {  // How it stops? Ans: encounter EOF
        data = realloc(data, sizeof(*data)*(line_num+1));  // change the size of rows
        data[line_num] = line;
        line = NULL; 
        line_num++;
    }
    free(line);
    sortData(data, line_num);
    for (size_t j = 0; j < line_num; j++){
        fputs(data[j], stdout);
        free(data[j]);
    }
    free(data); // why free here is different from free in line 83?
    data = NULL;
}


int main(int argc, char ** argv) {
    if (argc == 1) {
        readData(stdin);
        return EXIT_SUCCESS;
    }

    for (int i = 0; i < argc - 1; i++){
        FILE *f = fopen(argv[i+1], "r");
        if (f == NULL) {
            printError("Open file failed!");
        }
        readData(f);
        if (fclose(f) != 0) {
            fprintf(stderr, "failed to close input\n");
        }
    }
    return EXIT_SUCCESS;
}