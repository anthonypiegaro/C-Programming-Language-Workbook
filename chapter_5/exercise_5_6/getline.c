#include <stdio.h>

#define SIZE 100

int get_line(char *s);

int main() {
    char s[SIZE];

    while (get_line(s) != EOF) {
        printf("%s\n", s);
    }

    printf("%s\n", s);

    return 0;
}

int get_line(char *s) {
    int c;

    while ((c = getchar()) != EOF && c != '\n') {
        *s++ = c;
    }

    *s = '\0';

    if (c == EOF) {
        return EOF;
    }

    return 0;
}
