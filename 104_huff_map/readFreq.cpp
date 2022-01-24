#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  std::ifstream f;
  f.open(fname);
  if (f.fail()) {
    std::cerr << "Open file failed!" << std::endl;
    exit(EXIT_FAILURE);
  }
  uint64_t * res = new uint64_t[257]();
  memset(res, 0, 256);
  res[256] = 1;
  int c = 0;
  while ( (c = f.get()) != EOF) {
    res[c]++;
  }
  f.close();
  return res;
}
