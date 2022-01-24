#include<stdio.h>


size_t  maxSeq(int * array, size_t n){
    if(n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    int pre = array[0];
    size_t cnt = 1;
    size_t max = 1;
    for (size_t i=1; i < n; i++){
        if(pre < array[i]){
            cnt++;
            if (max < cnt){
                max = cnt;
            }
        }
        else{
            // if(max < cnt){
            //     max = cnt;
            // }
            cnt = 1;
        }
        pre = array[i];
    }
    return max;
}