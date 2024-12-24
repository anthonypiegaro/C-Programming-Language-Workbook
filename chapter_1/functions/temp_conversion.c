#include <stdio.h>

#define UPPER 300
#define LOWER 0
#define STEP 20

float f_to_c(int f);

int main() {
    for (int f = LOWER; f <= UPPER; f = f + STEP) {
        printf("%3d\t%6.1f\n", f, f_to_c(f));
    }

    return 0;
}

float f_to_c(int f) {
    return (5.0 / 9.0) * (f + 32);
}
