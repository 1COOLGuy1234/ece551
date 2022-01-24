#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t length = strlen(inputName);
  char *processName = malloc((length+8) * sizeof(*processName));
  memcpy(processName, inputName, length);
  memcpy(processName + length, ".counts", 8);
  return processName;
}
