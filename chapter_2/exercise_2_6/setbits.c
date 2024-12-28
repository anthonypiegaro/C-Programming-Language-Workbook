#include <stdio.h>

int setbits(int x, int p, int n, int y);

int main() {
    printf("x = 12; y = 13; p = 2; n = 1;-> %d\n", setbits(12, 2, 1, 13));
    return 0;
}

int setbits(int x, int p, int n, int y) {
    int res;
    int mask;
    int y_mask;
    int y_rightmost;

    mask = ((~0) << p) | (~((~0) << (p - n)));

    // apply the mask
    res = x & mask;

    // get n rightmost of y
    y_mask = ~((~0) << n);

    y_rightmost = y & y_mask;

    // shift y's n rightmost by p - n
    y_rightmost = y_rightmost << (p - n);

    // combine our masked x with our shifted rightmost y
    res = res | y_rightmost;

    return res;
}
