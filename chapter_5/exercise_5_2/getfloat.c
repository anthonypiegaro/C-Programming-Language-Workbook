#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 100
#define SIZE 10

int buf[MAXSIZE];
int bufp = 0;

int getch(void);
void ungetch(int c);
float getfloat(float *);

int main() {
    int n;
    float array[SIZE];

    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; ++n)
        ;
    
    for (int i = 0; i < n; ++i) {
        printf("%f\n", array[i]);
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

float getfloat(float *pn) {
    int c, sign;
    double pow;

    while (isspace(c = getch()))
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
        c = getch();

    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
    }

    if (c == '.')
        c = getchar();
    
    for (pow = 1.0; isdigit(c); c = getch()) {
        *pn = 10.0 * *pn + (c - '0');
        pow *= 10.0;
    }

    *pn *= sign;

    if (c != EOF) {
        ungetch(c);
    }

    return c;
}
