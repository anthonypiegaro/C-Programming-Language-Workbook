#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 100
#define SIZE 10

int buf[MAXSIZE];
int bufp = 0;

int getch(void);
void ungetch(int c);
int getint(int *);

int main() {
    int n, array[MAXSIZE];

    for (n = 0; n < SIZE && getint(&array[n]) != EOF; ++n)
        ;
    
    for (int i = 0; i < n; ++i) {
        printf("%d\n", array[i]);
    }

    return 0;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp < MAXSIZE) {
        buf[bufp++] = c;
    } else {
        printf("error: buffer out of memory");
    }
}

int getint(int *pn) {
    int c, sign;

    while (isspace(c = getch()))
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        if (!isdigit(c = getch())) {
            ungetch(c);
            ungetch((sign > 0) ? '+' : '-');
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;

    if (c != EOF) {
        ungetch(c);
    }

    return c;
}
