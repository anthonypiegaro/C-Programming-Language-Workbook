#include <stdio.h>

#define TAB_SPACE 8

int main() {
    int c;
    int num_spaces;
    int spaces_to_last_tab_start;

    num_spaces = 0;
    for (int length = 1; (c = getchar()) != EOF; ++length) {
        if (c == ' ') {
            ++num_spaces;
        } else {
            if (num_spaces > 0) {
                spaces_to_last_tab_start = length - ((((length / TAB_SPACE) - 1) * TAB_SPACE) + 1);

                if (num_spaces <= spaces_to_last_tab_start) {
                    for (int i = 0; i < num_spaces; ++i) {
                        putchar(' ');
                    }
                } else {
                    num_spaces = num_spaces - spaces_to_last_tab_start;
                    while (num_spaces > 0) {
                        putchar('\t');
                        num_spaces = num_spaces - TAB_SPACE;
                    }

                    for (int i = 0; i < spaces_to_last_tab_start; ++i) {
                        putchar(' ');
                    }
                }

                num_spaces = 0;
            }

            if (c == '\t') {
                length = ((length / TAB_SPACE) * TAB_SPACE) - 1;
            }

            if (c == '\n') {
                length = 0;
            }

            putchar(c);
        }
    }

    putchar('\n');

    return 0;
}
