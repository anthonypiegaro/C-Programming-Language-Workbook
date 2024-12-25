#include <stdio.h>

#define IN 1
#define OUT 0

int main() {
    int c;
    int prev_c;
    int comment;

    comment = OUT;
    while ((c = getchar()) != EOF) {
        if (c == '/' && prev_c == '/') {
            while ((c = getchar()) != EOF && c != '\n') {
                ;
            }

            if (c == EOF) {
                return 0;
            }

            putchar('\n');
            prev_c = '\n';
        } else if (prev_c == '/' && c == '*') {
           while ((c = getchar()) != EOF && !(prev_c == '*' && c == '/')) {
                prev_c = c;
            }

            if (c == EOF) {
                return 0;
            }

            prev_c = 0;
        } else if (c == '/') {
            prev_c = '/';
        } else {
            if (prev_c == '/') {
                putchar('/');
            }

            putchar(c);
            prev_c = c;
        }
    }

    return 0;
}
