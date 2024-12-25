#include <stdio.h>

#define IN 1
#define OUT 0

// only handle single line comments to start
int main() {
    int c;
    int prev_c;
    int comment;

    comment = OUT;
    while ((c = getchar()) != EOF) {
        if (c == '/' && prev_c == '/') {
            // we now know that we are in a comment, so lets go through the rest of this line
            while ((c = getchar()) != EOF && c != '\n') {
                ;
            }

            if (c == EOF) {
                return 0;
            }

            putchar('\n');
            prev_c = '\n';
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
