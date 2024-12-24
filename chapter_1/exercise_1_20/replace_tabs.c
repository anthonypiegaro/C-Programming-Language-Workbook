#include <stdio.h>

#define TAB_SPACES 4

int main() {
    int c;

    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (int i = 0; i < TAB_SPACES; ++i) {
                putchar(' ');
            }
        } else {
            putchar(c);
        }
    }

    return 0;
}