#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647
#define INT_MIN (-INT_MAX-1)
size_t maxSeq(int * array, size_t n);

void test_maxSeq(int *array, size_t n, size_t ans){
  size_t ret = maxSeq(array, n);
  if (ans != ret){
    exit(EXIT_FAILURE);
  }
}

int main(){
  int array1[] = {1, 0};
  int array2[] = {1, 1};
  int array3[] = {0};
  int array4[] = {2, 1, 3, 7};
  int array5[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
  int array6[] = {INT_MIN,INT_MAX};
  int array7[] = {1,2,3,4,5};
  int *array8 = NULL;
  
  test_maxSeq(array1, 2, 1);
  test_maxSeq(array2, 2, 1);
  test_maxSeq(array3, 1, 1);
  test_maxSeq(array4, 4, 3);
  test_maxSeq(array5, 10, 4);
  test_maxSeq(array6, 2, 2);
  test_maxSeq(array7, 5, 5);
  test_maxSeq(array8, 0, 0);

  return EXIT_SUCCESS;
}
