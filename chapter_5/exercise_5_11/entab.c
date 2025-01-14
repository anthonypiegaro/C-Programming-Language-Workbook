#include <stdio.h>
#include <stdlib.h>

#define TAB_SPACE 8
#define MAX_STOPS 100

int main(int argc, char *argv[]) {
    int c;
    int num_spaces;
    int line_pos;
    int tab_stops[MAX_STOPS];
    int tab_stops_p = 0;
    int tab_stops_length;

    while (--argc) {
        tab_stops[tab_stops_p++] = atoi(*++argv);
    }

    tab_stops_length = tab_stops_p;
    tab_stops_p = 0;

    num_spaces = line_pos = 0;

    while ((c = getchar()) != EOF) {
        ++line_pos;

        if (c == ' ') {
            ++num_spaces;

            if (tab_stops_p < tab_stops_length) {
                if (line_pos % (tab_stops[tab_stops_p++]) == 0 && num_spaces > 1) {
                    putchar('\t');
                    num_spaces = 0;
                }
            } else {
                if (line_pos % TAB_SPACE == 0 && num_spaces > 1) {
                    putchar('\t');
                    num_spaces = 0;
                }
            }
        } else {
            while (num_spaces) {
                putchar(' ');
                --num_spaces;
            }

            if (c == '\n') {
                line_pos = 0;
                tab_stops_p = 0;
            } else if (c == '\t') {
                if (tab_stops_p < tab_stops_length) {
                    line_pos = (((line_pos - 1) / tab_stops[tab_stops_p]) + 1) * tab_stops[tab_stops_p] + 1;
                    ++tab_stops_p;
                } else {
                    line_pos = (((line_pos - 1) / TAB_SPACE) + 1) * TAB_SPACE + 1;
                }
            }

            putchar(c);
        }
    }

    return 0;
}
