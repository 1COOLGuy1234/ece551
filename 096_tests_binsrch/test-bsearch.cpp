#include "function.h"
#include <cstdio>
#include <cstdlib>
#include <math.h>

class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn), 
                                                                    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class linearFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) { return arg; }
};


int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int max_num = high > low ? (log(high-low)/log(2)+1) : 1;
  CountedIntFn * fun = new CountedIntFn(max_num, f, mesg);
  int ans = binarySearchForZero(fun, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "Wrong output answer in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
  delete fun;
}

int main() {
  SinFunction f;
  linearFunction lf;
  check(&f, 0, 150000, 52359, "sinFunction");
  check(&lf, -99999, 10000000, 0, "linear Function");
  check(&lf, 1, 1, 1, "linear Function");
  check(&lf, 0, 2, 0, "linear Function");
  check(&lf, 1, 2, 1, "linear Function");
  check(&lf, -2, 0, -1, "linear Function");
  check(&lf, -1, 3, 0, "linear Function");
}
