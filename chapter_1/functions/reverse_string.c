#include <stdio.h>

#define MAXSIZE 1000

void reverse(char s[], int length);

int main() {
    int c;
    char line[MAXSIZE];
    int length;

    c = 0;
    while (c != EOF) {
        for (length = 0; (c = getchar()) != EOF && c != '\n'; ++length) {
            line[length] = c;
        }

        line[length] = '\0';

        reverse(line, length);

        printf("%s\n", line);
    }

    return 0;
}

void reverse(char s[], int length) {
    int temp;

    for (int i = 0; i < length / 2; ++i) {
        temp = s[i];

        s[i] = s[length - 1 - i];
        s[length - 1 - i] = temp;
    }
}
