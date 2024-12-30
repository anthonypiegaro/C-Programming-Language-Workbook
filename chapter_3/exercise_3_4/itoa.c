#include <stdio.h>

#define MAX_SIZE 100
#define POS 1
#define NEG 0

void itoa(int n, char s[]);
void reverse(char s[]);

int main() {
    char s[MAX_SIZE];

    itoa(1500, s);

    printf("%s\n", s);

    return 0;
}

void itoa(int n, char s[]) {
    int i, sign;
    
    sign = (n < 0) ? NEG : POS;
    i = 0;

    if (sign == POS) {
        do {
            s[i++] = n % 10 + '0';
        } while ((n /= 10) > 0);
    } else {
        do {
            s[i++] = -(n % 10) + '0';
        } while (-(n /= 10) > 0);
    }

    if (sign == NEG) {
        s[i++] = '-';
    }

    s[i] = '\0';

    reverse(s);
}

void reverse(char s[]) {
    int length;
    int temp;

    for (length = 0; (s[length]) != '\0'; ++length) {
        ;
    }

    for (int i = 0; i < (length / 2); ++i) {
        temp = s[i];
        s[i] = s[length - i - 1];
        s[length - i - 1] = temp;
    }
}
