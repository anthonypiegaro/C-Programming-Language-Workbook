#include <stdio.h>
#include <ctype.h>

#define SIZE 10
#define BUF_SIZE 100

char buf[BUF_SIZE];
int bufp = 0;

char getch(void);
void ungetch(char c);
float getfloat(float *pn);

int main() {
    int n, len;
    float array[SIZE];

    for (len = 0; len < SIZE && getfloat(&array[len]) != 0.0; ++len)
        ;
    
    for (n = 0; n < len; ++n) {
        printf("i = %d\t%f\n", n, array[n]);
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

float getfloat(float *pn) {
    char c;
    short sign, expo_sign;
    float pow = 1.0;
    int expo = 0;

    while (isspace(c = getch()))
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        ungetch(c);
        return 0.0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-') {
        c = getch();
        if (!isdigit(c) && c != '.') {
            ungetch(c);
            ungetch((sign == -1) ? -1 : 1);
            return 0;
        } else if (c == '.') {
            c = getch();
            if (!isdigit(c)) {
                ungetch(c);
                ungetch('.');
                ungetch((sign == -1) ? -1 : 1);
                return 0;
            }

            ungetch(c);
            c = '.';
        }
    }
    
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    
    if (c == '.') {
        c = getch();
        for (*pn; isdigit(c); c = getch()) {
            *pn = 10 * *pn + (c - '0');
            pow *= 10;
        }
    }

    *pn *= sign;
    *pn /= pow;

    if (c == 'e') {
        c = getch();

        if (isdigit(c) || c == '+' || c == '-') {
            expo_sign = (c == '-') ? -1 : 1;

            if (c == '+' || c == '-') {
                c = getch();
                if (!isdigit(c)) {
                    ungetch(c);
                    ungetch((expo_sign == -1) ? '-' : '+');
                    ungetch('e');
                    return 'e';
                }
            }

            for (expo = 0; isdigit(c); c = getch())
                expo = 10 * expo + (c - '0');
            
            for (int i = 0; i < expo; ++i) {
                *pn = (expo_sign > 0) ? *pn * 10 : *pn / 10;
            }
        } else {
            ungetch(c);
            c = 'e';
        }
    }

    if (c != EOF) {
        ungetch(c);
        return c;
    }

    return 0.0;
}
