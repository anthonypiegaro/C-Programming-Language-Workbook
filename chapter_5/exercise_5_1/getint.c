#include <stdio.h>
#include <ctype.h>

#define SIZE 10
#define BUF_SIZE 100

char buf[BUF_SIZE];
int bufp = 0;

char getch(void);
void ungetch(char c);
int getint(int *pn);

int main() {
    int n, len, array[SIZE];

    for (len = 0; len < SIZE && getint(&array[len]) != 0; ++len)
        ;
    
    for (n = 0; n < len; ++n) {
        printf("i = %d\t%d\n", n, array[n]);
    }

    return 0;
}

char getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(char c) {
    if (bufp == BUF_SIZE) {
        printf("error: buffer out of storage\n");
    } else {
        buf[bufp++] = c;
    }
}

int getint(int *pn) {
    char c;
    short sign;

    while (isspace(c = getch()))
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        c = getch();

        if (!isdigit(c)) {
            ungetch(c);
            ungetch((sign == -1) ? '-' : '+');
            return 0;
        }
    }
    
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    
    *pn *= sign;

    if (c != EOF) {
        ungetch(c);
        return c;
    }

    return 0;
}
