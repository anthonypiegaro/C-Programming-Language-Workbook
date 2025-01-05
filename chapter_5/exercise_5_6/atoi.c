#include <stdio.h>

#define SIZE 100

int atoi(char *s);

int main() {
    char s[SIZE] = "-7511";

    printf("%d\n", atoi(s));

    return 0;
}

int atoi(char *s) {
    int n, sign;
    n = 0;

    sign = (*s == '-') ? -1 : 1;

    if (*s == '-' || *s == '+')
        *s++;
    
    while (isdigit(*s)) {
        n = 10 * n + (*s - '0');
        *s++;
    }

    n *= sign;

    return n;
}
