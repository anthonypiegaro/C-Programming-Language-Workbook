#include <stdio.h>

#define TAB_SPACES 8

int main() {
    int c;
    int line_length;
    int spaces;

    line_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line_length = 0;
            putchar(c);
        } else if ( c == '\t') {
            // find where the next stop is
            spaces = (line_length / TAB_SPACES) * TAB_SPACES + TAB_SPACES - line_length;

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
