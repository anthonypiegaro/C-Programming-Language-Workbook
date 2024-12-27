#include <stdio.h>

// single comments [x]
// multiline comments [x]
// brackets []
// paranthesis []
// braces []
// single quotes [x]
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
        } else if (c == '\'') {
            putchar('\'');

            c = getchar();

            if (c == EOF) {
                printf("error: single quote not closed");
                return 1;
            }

            if (c == '\\') { // this means an escape char is used
                c = getchar();

                if (c == EOF) {
                    printf("error: single quote not closed");
                    return 1;
                }

                if (
                    // Not going to include unicode or hex stuff
                    c == '\n' ||  // Newline
                    c == '\t' ||  // Horizontal Tab
                    c == '\b' ||  // Backspace
                    c == '\r' ||  // Carriage Return
                    c == '\\' ||  // Backslash
                    c == '\'' ||  // Single Quote
                    c == '\"' ||  // Double Quote
                    c == '\a' ||  // Alert (Bell)
                    c == '\f' ||  // Form Feed
                    c == '\v' ||  // Vertical Tab
                    c == '\0'     // Null Character
                ) {
                    putchar(c);
                } else {
                    printf("error: multi-character character constant");
                    return 1;
                }
            } else { // this means an escape was not used
                putchar(c);
            }

            if ((c = getchar()) != '\'') {
                printf("error: mulit-character character constant");
                return 1;
            }

            putchar('\'');

            prev_c = 0;

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
