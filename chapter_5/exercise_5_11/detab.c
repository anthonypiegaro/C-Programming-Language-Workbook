#include <stdio.h>
#include <stdlib.h>

#define TAB_SPACES 8
#define MAX_STOPS 100

int main(int argc, char *argv[]) {
    int c;
    int line_length;
    int spaces;
    int tab_stops[MAX_STOPS];
    int tab_stops_p = 0;
    int tab_stops_length;

    while (--argc) {
        tab_stops[tab_stops_p++] = atoi(*++argv);
    }

    tab_stops_length = tab_stops_p;
    tab_stops_p = 0;

    line_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line_length = 0;
            tab_stops_p = 0;
            putchar(c);
        } else if ( c == '\t') {
            if (tab_stops_p < tab_stops_length) {
                spaces = (line_length / tab_stops[tab_stops_p]) * tab_stops[tab_stops_p] + tab_stops[tab_stops_p] - line_length;
            } else {
                spaces = (line_length / TAB_SPACES) * TAB_SPACES + TAB_SPACES - line_length;
            }

            for (int i = 0; i < spaces; ++i) {
                putchar(' ');
            }

            line_length = line_length + spaces;
        } else {
            ++line_length;
            putchar(c);
        }

        while (tab_stops_p < tab_stops_length && tab_stops[tab_stops_p] < line_length)
            ++tab_stops_p;
    }

    return 0;
}
