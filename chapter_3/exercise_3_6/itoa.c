#include <stdio.h>

#define MAX_SIZE 100
#define POS 1
#define NEG 0

void itoa(int n, char s[], int w);
void reverse(char s[]);

int main() {
    char s[MAX_SIZE];

    itoa(15395, s, 10);

    printf("%s\n", s);

    return 0;
}

void itoa(int n, char s[], int w) {
    int i, sign;
    i = 0;
    sign = (n < 0) ? NEG : POS;

    if (sign == NEG) {
        do {
            s[i++] = -(n % 10) + '0';
        } while (-(n /= 10) > 0);
    } else {
        do {
            s[i++] = (n % 10) + '0';
        } while ((n /= 10) > 0);
    }

    if (sign == NEG) {
        s[i++] = '-';
    }

    for (; i < w; ++i) {
        s[i] = ' ';
    }

    s[i] = '\0';

    reverse(s);
}

void reverse(char s[]) {
    int length, temp;

    for (length = 0; s[length] != '\0'; ++length) {
        ;
    }

    for (int i = 0; i < (length / 2); ++i) {
        temp = s[i];
        s[i] = s[length - 1 - i];
        s[length - 1 - i] = temp;
    }
}
