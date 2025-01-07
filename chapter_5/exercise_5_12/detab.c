#include <stdio.h>

#define SIZE 100

int process_input(int argc, char *argv[], int *tab_space, int *start_col);
int atoi(char *s);
int isdigit(char c);

int main(int argc, char *argv[]) {
    int c;
    int line_length;
    int spaces;
    int lines_after_start;
    int tab_space = 8;
    int start_col = 8;

    if (!process_input(argc, argv, &tab_space, &start_col)) {
        return 1;
    }

    printf("Start Column: %d\n", start_col);
    printf("Tab Space: %d\n", tab_space);

    line_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line_length = 0;
            putchar(c);
        } else if ( c == '\t') {
            // spaces = (line_length / TAB_SPACES) * TAB_SPACES + TAB_SPACES - line_length;

            if (line_length < start_col) {
                spaces = start_col - line_length;
            } else {
                lines_after_start = line_length - start_col;
                spaces = tab_space - (lines_after_start % tab_space);
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

int process_input(int argc, char *argv[], int *tab_space, int *start_col) {
    char c, s[SIZE];
    char *arg;

    while (--argc) {
        arg = *++argv;

        if (*arg == '-') {
            *start_col = atoi(++arg);

            if (*start_col == -1) {
                printf("Invalid Start Column Argument\n");
                return 0;
            }
        } else if (*arg == '+') {
            *tab_space = atoi(++arg);
            if (*tab_space == -1) {
                printf("Invalid Tab Space Argument\n");
                return 0;
            }
        } else {
            printf("unrecognized arg: %s\n", s);
        }
    }

    return 1;
}

int atoi(char *s) {
    int num = 0;

    while (*s != '\0') {
        if (isdigit(*s)) {
            num = 10 * num + (*s - '0');
            ++s;
        } else {
            return -1;
        }
    }

    return num;
}

int isdigit(char c) {
    return 48 <= c && c <= 57;
}
