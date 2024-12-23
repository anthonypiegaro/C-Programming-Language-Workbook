#include <stdio.h>

main() {
    int c;

    printf("%d\n", EOF);

    while ((c = getchar()) != EOF) {
        putchar(c);
    }
}