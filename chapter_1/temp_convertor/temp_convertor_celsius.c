#include <stdio.h>

main() {
    float farh, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("%3s\t%6s\n", "C", "F"); 

    celsius = lower;
    while (celsius <= upper) {
        farh = (5.0 / 9.0) * (celsius + 32.0);

        printf("%3.0f\t%6.1f\n", celsius, farh);

        celsius = celsius + step;
    }
}