#include <stdio.h>

#define TAB_SPACE 8

int main() {
    int c;
    int num_spaces;
    int line_pos;

    num_spaces = line_pos = 0;

    while ((c = getchar()) != EOF) {
        ++line_pos;

        if (c == ' ') {
            ++num_spaces;

            if (line_pos % TAB_SPACE == 0 && num_spaces > 1) {
                putchar('\t');
                num_spaces = 0;
            }
        } else {
            while (num_spaces) {
                putchar(' ');
                --num_spaces;
            }

            if (c == '\n') {
                line_pos = 0;
            } else if (c == '\t') {
                line_pos = (((line_pos - 1) / TAB_SPACE) + 1) * TAB_SPACE + 1;
            }

            putchar(c);
        }
    }

    return 0;
}
