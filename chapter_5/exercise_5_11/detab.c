#include <stdio.h>
#include <stdlib.h>

#define TAB_SPACES 8
#define MAXSIZE 100

int valid_stops(int *stops, int len);

int main(int argc, char *argv[]) {
    int c;
    int line_length;
    int spaces;
    int tab_stops[MAXSIZE];
    int tab_stops_p = 0;
    int tab_stops_len = argc - 1;

    while (--argc > 0) {
        tab_stops[tab_stops_p++] = atoi(*++argv);
    }

    if (argc > 1 && !valid_stops(tab_stops, tab_stops_p)) {
        printf("Invalid input, terminating program\n");
        return -1;
    }

    line_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line_length = 0;
            putchar(c);
        } else if ( c == '\t') {
            while (tab_stops_p < tab_stops_len && tab_stops[tab_stops_p] < line_length)
                ++tab_stops_p;

            if (tab_stops_p < tab_stops_len) {
                spaces = tab_stops[tab_stops_p] - line_length + 1;
            } else {
                int last_provided_tab_stop = (tab_stops_len > 0) ? tab_stops[tab_stops_p - 1] : 0;
                int len_after_last_provided_tab_stop = line_length - last_provided_tab_stop;
                spaces = TAB_SPACES - (len_after_last_provided_tab_stop % TAB_SPACES);
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

int valid_stops(int *stops, int len) {
    if (*stops < 0) {
        printf("tab stops contain negative input\n");
        return 0;
    }

    for (int i = 0; i < len - 1; ++i) {
        if (*stops >= *(stops + 1)) {
            printf("tab stops not increasing\n");
            return 0;
        }
    }

    return 1;
}
