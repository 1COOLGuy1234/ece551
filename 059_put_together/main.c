#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  // open file
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    printError1("Failed to open file");
  }
  // initial counts_t
  counts_t *c = createCounts();
  // read file
  char * line = NULL;
  size_t sz = 0;
  // ssize_t char_num = 0;
  while (getline(&line, &sz, f) >= 0) {
    // remove next line
    char * p = strchr(line, '\n');
    if (p != NULL) {
      *p = '\0';
    }
    addCount(c, lookupValue(kvPairs, line));
  }
  if (!feof(f)) {
    printError1("Failed to read all file!");
  }
  free(line);

  if (fclose(f) != 0) {
    printError1("Failed to close file!");
  }

  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 2) {
    printError1("At least one argument!");
  }
  kvarray_t * kv = readKVs(argv[1]);
 //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      printError1("Failed to open th file!");
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      printError1("Failed to close file!");
    }

    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }



 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
