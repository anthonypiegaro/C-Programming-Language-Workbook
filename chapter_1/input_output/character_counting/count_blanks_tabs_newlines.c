#include <stdio.h>

main() {
    int c;
    int blanks, tabs, new_lines;

    blanks = 0;
    tabs = 0;
    new_lines = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
        } else if (c == '\t') {
            ++tabs;
        } else if (c == '\n') {
            ++new_lines;
        }
    }

    printf("Blanks: %d\nTabs: %d\nNew Lines: %d\n", blanks, tabs, new_lines);
}
