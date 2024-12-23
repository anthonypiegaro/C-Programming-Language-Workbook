#include <stdio.h>

main() {
    int prev;
    int c;

    prev = 1;
    while ((c = getchar()) != EOF) {
        if (c == ' ' && prev == ' ') {
            ;
        } else {
            putchar(c);
        }
        prev = c;
    }
}