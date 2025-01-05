#include <stdio.h>

#define SIZE 100

int i = 0;

void itoa(char *s, int n);

int main() {
    char s[SIZE];
    char r[SIZE];
    char q[SIZE];

    itoa(s, -956);
    i = 0;
    itoa(r, 0);
    i = 0;
    itoa(q, 567634);

    printf("%s\n", s);
    printf("%s\n", r);
    printf("%s\n", q);

    return 0;
}

void itoa(char *s, int n) {
    if (n < 0) {
        *s = '-';
        ++i;
        n = -n;
    }

    if ((n / 10) > 0) {
        itoa(s, n / 10);
    }

    s += i++;

    *s = (n % 10)+ '0';
}
