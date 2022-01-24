#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min (int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max (int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
struct rectangle{
  int x;
  int y;
  int width;
  int height;
};
typedef struct rectangle rectangle;





rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION
  if (r.width < 0){
    r.x += r.width;
    r.width = -1 * r.width;
  }
  if (r.height < 0){
    r.y += r.height;
    r.height = -1 * r.height;
  }
  return r;
}
rectangle intersection(rectangle r1, rectangle r2) {
  //WRITE THIS FUNCTION
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);

  int r1_left = r1.x;
  int r1_bottom = r1.y;
  int r1_right = r1.x + r1.width;
  int r1_top = r1.y + r1.height;

  int r2_left = r2.x;
  int r2_bottom = r2.y;
  int r2_right = r2.x + r2.width;
  int r2_top = r2.y + r2.height;

  // figure out the intersection
  int is_top = (r1_top > r2_top)? r2_top : r1_top;
  int is_right = (r1_right > r2_right) ? r2_right : r1_right;
  int is_bottom = (r1_bottom > r2_bottom) ? r1_bottom : r2_bottom;
  int is_left = (r1_left > r2_left) ? r1_left : r2_left;

  // corner case: NO INTERSECTION
  if ((is_top < is_bottom) || (is_right < is_left) || (is_top == is_bottom && is_right == is_left)){
    r1.width = 0;
    r1.height = 0;
    return r1;
  }

  

  // assign to return value
  r1.x = is_left;
  r1.y = is_bottom;
  r1.width = is_right - is_left;
  r1.height = is_top - is_bottom;

  // return
  return r1;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, 
	                           r.x + r.width, r.y + r.height);
  }
}

int main (void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  // r1 = canonicalize(r1);
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  // r2 = canonicalize(r2);
  printf("r2 is ");
  printRectangle(r2);
  
  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  // r3 = canonicalize(r3);
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  // r4 = canonicalize(r4);
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);
  
  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);
  
  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);
  
  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);
  
  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);


  return EXIT_SUCCESS;

}
