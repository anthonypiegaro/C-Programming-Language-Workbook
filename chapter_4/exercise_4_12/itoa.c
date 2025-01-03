#include <stdio.h>

#define MAXSIZE 100

int i = 0;

void itoa(int n, char s[]);

int main() {
    char s[MAXSIZE];

    itoa(-2607551, s);

    printf("%s\n", s);

    return 0;
}

void itoa(int n, char s[]) {
    if (n < 0) {
        s[i++] = '-';
        n = -n;
    }

    if (n / 10) {
        itoa(n / 10, s);
    } else {
        s[i++] = (n % 10) + '0';
        return;
    }

    s[i++] = (n % 10) + '0';
    s[i] = '\0';
}
