#include <stdio.h>

#define swap(t, x, y) \
    { t temp = x; x = y; y = temp; }

int main() {
    int x = 5;
    int y = 12;

    swap(int, x, y);

    printf("x: %d\ty: %d\n", x, y);

    return 0;
}
