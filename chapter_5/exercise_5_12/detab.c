#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int c;
    int line_length;
    int spaces;
    char *arg;
    int tab_space = 8;
    int first_stop = 8;

    while (--argc) {
        arg = *++argv;

        if (*arg == '+') {
            tab_space = atoi(++arg);
        } else if (*arg == '-') {
            first_stop = atoi(++arg);
        }
    }

    printf("First Column: %d\tEvery Column: %d\n", first_stop, tab_space);

    line_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line_length = 0;
            putchar(c);
        } else if ( c == '\t') {
            if (line_length < first_stop) {
                spaces = first_stop - line_length;
            } else {
                spaces = tab_space - ((line_length - first_stop) % tab_space);
                spaces = (spaces) ? spaces : tab_space;
            }

            for (int i = 0; i < spaces; ++i) {
                putchar(' ');
            }

            line_length = line_length + spaces;
        } else {
            ++line_length;
            putchar(c);
        }
    }

    return 0;
}
