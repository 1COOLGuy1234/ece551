#include <cstdio>
#include <cstdlib>
#include "function.h"


int binarySearchForZero(Function<int, int> * f, int low, int high) {
    // if (f->invoke(high-1) < 0) { // forever negative
    //     return high-1;
    // }
    
    // if (f->invoke(low) > 0) {
    //     return low;
    // }

    while (low < high - 1) {
        int mid = (low + high) / 2;
        int res = f->invoke(mid);
        if (res > 0) {
            high = mid;
        }
        else if(res < 0) {
            // low = mid + 1;
            low = mid;
        }
        else {
            return mid;
        }
    }
    return low;
}