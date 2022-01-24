#include <stdio.h>
#include <stdlib.h>


void printMatrix(char m[10][10]){
    for (int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            putchar(m[i][j]);
        }
        putchar('\n');
    }
}

void printError(const char *text){
    fprintf(stderr, "Wrong: %s\n", text);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
    // check argument number
    if (argc != 2) {
        fprintf(stderr,"Usage: rotateMatrix inputFileName\n");
        return EXIT_FAILURE;
    }
    // open file
    FILE * f =  fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr,"File cannot be opened!\n");
        return EXIT_FAILURE;
    }

    // read matrix
    char matrix[10][10] = {0};
    char c;
    int row = 0;
    int col = 0;
    while ((c = fgetc(f)) != EOF){
        if (c == '\n'){   // if c == next line
            if (col != 0){
                printError("Input file");
            }
            continue;
        }
        // if (c != '\n'){
        //     matrix[row][col++] = c;
        // }
        matrix[row][col++] = c;

        if (col == 10){
            col = 0;
            row++;
        }
        if (row == 10){
            if ((c = fgetc(f)) != '\n'){
                printError("Input file");
            }
            if ((c = fgetc(f)) != EOF){
                printError("Input file");
            }
            break;
        }
    }
    if (col != 0 || row != 10){
        printError("Input file");
    }
    // rorate matrix
    char matrix_rotate[10][10];
    for (int i = 9; i >= 0; i--){
        for (int j = 0; j < 10; j++){
            matrix_rotate[j][9 - i] = matrix[i][j];
        }
    }
    // print matrix
    printMatrix(matrix_rotate);
    // close file
    if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}