#include<stdio.h>
void print_binary(int n, unsigned int w){
    printf("0b");
    for(int i=8; i >= 0; i--){
        int bit = (n >> i) & 1;
        printf("%d", bit);
    }
    printf("\n");
}

int main(){
    int a = -3;
    unsigned char b = 253;
    printf("%d complement: ", a);
    print_binary(a, 8);
    printf("%d complement: ", b);
    print_binary(b, 8);
    printf("if %d is a complement, it = %d \n", b, (char)b);
    return 0;
}
