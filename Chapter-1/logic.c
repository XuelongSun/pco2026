#include<stdio.h>
#include<stdbool.h>

int main(){
    bool A = true;
    bool B = false;
    printf("not (A and B) = %d\n",(!(A && B)));
    return 0;
}