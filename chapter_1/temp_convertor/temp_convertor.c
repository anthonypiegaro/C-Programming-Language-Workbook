#include <stdio.h>

main() {
    float farh, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    printf("%3s\t%6s\n", "F", "C"); 

    farh = lower;
    while (farh <= upper) {
        celsius = (5.0 / 9.0) * (farh + 32.0);

        printf("%3.0f\t%6.1f\n", farh, celsius);

        farh = farh + step;
    }
}
