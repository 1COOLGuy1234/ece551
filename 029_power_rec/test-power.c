#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans){
  if (power(x,y) != expected_ans){
    printf("The case that x=%u and y=%u is wrong!", x, y);
    exit(EXIT_FAILURE);
  }
}
int main(){
  run_check(0, 0, 1);
  run_check(1, 1, 1);
  run_check(2, 0, 1);
  run_check(2, 1, 2);
  //run_check(4294967295, 4294967295, 18446744065119600000);
  run_check(4294967295, 0, 1);
  run_check(4294967295, 1, 4294967295);
  run_check(4, 3, 64);
  run_check(3, 3, 27);
  run_check(5, 5, 3125);
  run_check(1, 0, 1);
  run_check(0, 1, 0);
  return EXIT_SUCCESS;
}
