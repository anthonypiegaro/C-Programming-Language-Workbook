#include <stdio.h>

// single comments [x]
// multiline comments [x]
// brackets []
// paranthesis []
// braces []
// single quotes []
// double quotes [x]
// escape sequences []
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
        } else if (c == '"') { // We are checking if in a string
            putchar('"');

            while ((c = getchar()) != EOF && c != '"') {
                putchar(c);
            }

            if (c == EOF) {
                printf("error: no matching closing double quote");
                return 1;
            }

            putchar('"');
        } else if (prev_c == '/' && c == '*') { // We are checking if entering a multiline comment
            // We can remove everything until the stop marker -> */
            prev_c = 0;
            while ((c = getchar()) != EOF && !(prev_c == '*' && c == '/')) {
                prev_c = c;
            }

            if (c == EOF) {
                printf("Error: Multiline comment missing closing marker");
            }

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
