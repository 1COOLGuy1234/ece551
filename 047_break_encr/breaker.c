#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int findMaxIndex(int array[], int size){  // find the index of the max element in array[]
    int maxIdx = 0;
    for (int i = 0; i < size; i++){
        if(array[i] > array[maxIdx]){
            maxIdx = i;
        }
    }
    return maxIdx;
}

int getKey(FILE *f){  // judge which character is correspoinding to 'e'
    int c;
    int freq[26] = {0};
    int idx;
    while ((c = fgetc(f)) != EOF){
        if (isalpha(c)){
            c = tolower(c);
            idx = c - 'a';
            freq[idx]++;
        }
    }
    int maxIdx = findMaxIndex(freq, 26);
    // x -> (x + maxIdx -4) % 26    because maxIdx [0, 26) so need to add 26
    int key = (maxIdx - 4 + 26) % 26;
    return key;
}

int main(int argc, char ** argv){
    if (argc != 2) {
        fprintf(stderr,"Usage: breaker inputFileName\n");
        return EXIT_FAILURE;
    }
    FILE * f =  fopen(argv[1], "r");
    if (f == NULL) {
        perror("Could not open file!");
        return EXIT_FAILURE;
    }
    printf("%d\n", getKey(f));
    if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}