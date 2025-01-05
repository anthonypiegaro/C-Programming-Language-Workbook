#include <stdio.h>

#define SIZE 100

void reverse(char *s);
int get_line(char *s);

int main() {
    char s[SIZE];

    while (get_line(s) != EOF) {
        reverse(s);
        printf("%s\n", s);
    }

    reverse(s);
    printf("%s\n", s);

    return 0;
}

void reverse(char *s) {
    char *t = s;
    char temp;

    while (*t != '\0') {
        t++;
    }

    t--;

    while (s < t) {
        temp = *s;

        *s++ = *t;
        *t-- = temp;
    }
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
