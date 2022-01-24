#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void printError(const char * msg) {
  fprintf(stderr, "Wrong: %s", msg);
  exit(EXIT_FAILURE);
}

void freePair(kvpair_t *pair) {
  if (pair == NULL) {
    return;
  }
  free(pair->key);
  free(pair->value);
  free(pair);
}


void parseLine(kvpair_t *pair, char * line) {
  // apply for memory of one pair
  char *key = NULL;
  char *value = NULL;
  key = strchr(line, '=');
  if (key == NULL) {
    printError("No key!");
  }
  pair->key = strndup(line, (size_t)(key-line));
  value = strchr(++key, '\n');
  if (value == NULL) {
    printError("No Value!");
  }
  pair->value = strndup(key, (size_t)(value-key));
}

kvarray_t * readKVs(const char * fname) {
  // open file
  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    printError("Failed to open file!");
  }
  // read line
  char * line = NULL;
  size_t sz = 0;
  size_t i = 0;
  kvpair_t *pair = NULL;
  kvarray_t *pairs = NULL;

  while (getline(&line, &sz, f) >= 0) {
    pair = realloc(pair, (i+1) * sizeof(*pair));
    if (pair == NULL) {
      printError("Failed to realloc!");
    }
    parseLine(&pair[i++], line);
    // line = NULL; ?????????
  }
  free(line);
  if (fclose(f) != 0) {
    printError("Failed to close file!");
  }

  pairs = malloc(sizeof(*pairs));
  pairs->array = pair;
  pairs->len = i;

  return pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  // for (int i = 0; i < pairs->len; i++) {
  //   freePair(&pairs->array[i]);
  // }
  // free(pairs);
  for (int i = 0; i < pairs->len; i++) {
    free(pairs->array[i].key);
    free(pairs->array[i].value);
  }
  free(pairs->array);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  kvpair_t *p;
  for (int i = 0; i < pairs->len; i++) {
    p = &pairs->array[i];
    printf("key = '%s' value = '%s'\n", p->key, p->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  kvpair_t *p;
  for (int i = 0; i < pairs->len; i++) {
    p = &pairs->array[i];
    if (strcmp(key, p->key) == 0) {
      return p->value;
    }
  }
  return NULL;
}
