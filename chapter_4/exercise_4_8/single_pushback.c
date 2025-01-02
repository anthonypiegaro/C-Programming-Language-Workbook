#include <stdio.h>

#define ARRAYSIZE 100

char buf;
char buf_valid;

int getch(void);
void ungetch(int);

int main() {
    int c, i;
    char s[ARRAYSIZE];
    i = 0;

    ungetch('W');

    while ((c = getch()) != EOF) {
        if (c == '\n') {
            s[i] = '\0';
            printf("%s\n", s);
            i = 0;
        } else {
            s[i++] = c;
        }
    }

    return 0;
}

int getch(void) {
    if (buf_valid) {
        buf_valid = 0;
        return buf;
    } else {
        return getchar();
    }
}

void ungetch(int c) {
    if (buf_valid)
        printf("ungetch: buffer already in use\n");
    else
        buf_valid = 1;
        buf = c;
}
