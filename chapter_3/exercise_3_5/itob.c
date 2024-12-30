#include <stdio.h>

#define MAX_SIZE 1000
#define POS 1
#define NEG 0

void itob(int n, char s[], int b);
void reverse(char s[]);

int main() {
    char s[MAX_SIZE];

    itob(72, s, 36);

    printf("%s\n", s);

    return 0;
}

void itob(int n, char s[], int b) {
    if (b < 2 || b > 36) {
        printf("Invalid base character (b). Must be between 2 and 36 inclusive.");
        return;
    }

    int i, sign, temp;
    i = 0;
    sign = (n < 0) ? NEG : POS;

    if (sign == NEG) {
        do {
            temp = -(n % b);
            s[i++] = (temp <= 9) ? temp + '0' : (temp - 9) + 'A';
        } while (-(n /= b) > 0);
    } else {
        do {
            temp = (n % b);
            s[i++] = (temp <= 9) ? temp + '0' : (temp - 9) + 'A';
        } while ((n /= b) > 0);
    }

    if (sign == NEG) {
        s[i++] = '-';
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
