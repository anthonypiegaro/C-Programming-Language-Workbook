#include <stdio.h>

int bitcount(int x);

int main() {
    // 11001
    printf("%d\n", bitcount(25));

    return 0;
}

int bitcount(int x) {
    int i;

    if (x == 0) {
        return 0;
    }

    for (i = 1; (x &= (x - 1)) != 0; ++i) {
        ;
    }

    return i;
}
