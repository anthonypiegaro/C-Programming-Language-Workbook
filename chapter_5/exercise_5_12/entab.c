#include <stdio.h>

int main(int argc, char *argv[]) {
    int c;
    int num_spaces;
    int line_pos;
    char *arg;
    int tab_space = 8;
    int first_stop = 8;

    num_spaces = line_pos = 0;

    while (--argc) {
        arg = *++argv;

        if (*arg == '+') {
            tab_space = atoi(*++arg);
        } else if (*arg == '-') {
            first_stop = atoi(*++arg);
        }
    }

    while ((c = getchar()) != EOF) {
        ++line_pos;

        if (c == ' ') {
            ++num_spaces;

            if (line_pos < first_stop || ((line_pos - first_stop) % tab_space == 0 && num_spaces > 1)) {
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
                if (line_pos < first_stop) {
                    line_pos = first_stop + 1;
                } else {
                    line_pos = (((line_pos - first_stop - 1) / tab_space) + 1) * tab_space + 1 + first_stop;
                }
            }

            putchar(c);
        }
    }

    return 0;
}
