#include <stdio.h>

int rightrot(int x, int n);

int main() {
    
    printf("%d\n", rightrot(211, 1));

    return 0;
}

int rightrot(int x, int n) {
    const int INT_SIZE = sizeof(int) * 8;
    int mask;
    int pos_to_rotate;
    int overflow;

    pos_to_rotate = n % INT_SIZE;

    if (pos_to_rotate == 0) {
        return x;
    }

    mask = (1 << pos_to_rotate) - 1;

    overflow = (x & mask) << (INT_SIZE - pos_to_rotate);

    return (x >> pos_to_rotate) | overflow;
}
