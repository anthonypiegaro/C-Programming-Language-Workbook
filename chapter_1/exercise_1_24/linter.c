#include <stdio.h>

// start by just getting single line comments
int main() {
    int c;
    int prev_c;

    prev_c = 0;
    while ((c = getchar()) != EOF) {
        if (c == '/' && prev_c == '/') { // you have entered a single line comment
            // ignore rest of the line
            while ((c = getchar()) != EOF && c != '\n') {
                ;
            }

            if (c == EOF) { // This means we have reached the end of the file and we end the program
                return 0;
            }

            putchar('\n');

            prev_c = 0;
        } else if (c == '/') {
            prev_c = '/';
        } else {
            if (prev_c == '/') {
                putchar('/');
            }
            putchar(c);

            if (c == '\n') {
                prev_c = 0;
            } else {
                prev_c = c;
            }
        }
    }

    return 0;
}
