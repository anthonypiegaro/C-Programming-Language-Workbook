#include <stdio.h>

int invert(int x, int p, int n);

int main() {
    printf("%d\n", invert(21, 4, 3));

    return 0;
}

int invert(int x, int p, int n) {
    int mask;
    
    mask = ((1 << n) - 1) << (p - n);

    return x ^ mask;
}
