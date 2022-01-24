#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "counts.h"

void printError1(const char * msg) {
  fprintf(stderr, "Wrong: %s", msg);
  exit(EXIT_FAILURE);
}

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  if (!c) {
    printError1("Failed to malloc!");
  }
  c->arr = NULL;
  c->len = 0;
  c->unknowns = 0;
  return c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->unknowns++;
    return;
  }
  
  for (int i = 0; i < c->len; i++) {
    if (strcmp(c->arr[i].string, name) == 0) {  // if equals, counts++
      c->arr[i].counts++;
      return;
    }
  }
  // if there is no name
  c->arr = realloc(c->arr, (c->len+1) * sizeof(*c->arr));
  assert(c->arr != NULL);
  c->len++;
  c->arr[c->len-1].string = strdup(name);
  c->arr[c->len-1].counts = 1;
  assert(strcmp(c->arr[c->len-1].string, name) == 0);  
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (int i = 0; i < c->len; i++) {
    fprintf(outFile, "%s: %d\n", c->arr[i].string, c->arr[i].counts);
  }
  if (c->unknowns > 0) {
    fprintf(outFile, "<unknown>: %d\n", c->unknowns);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i = 0; i < c->len; i++) {
    free(c->arr[i].string);
  }
  free(c->arr);
  free(c);
}
