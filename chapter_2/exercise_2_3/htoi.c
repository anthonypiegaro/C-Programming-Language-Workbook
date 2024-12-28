#include <stdio.h>

#define MAX_SIZE 100

int htoi(char s[]);

int main() {
    char line[MAX_SIZE];
    int line_length;
    int c;

    line_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            line[line_length] = '\0';
            line_length = 0;
        
            printf("Converted int:\t%4d\n", htoi(line));
        } else {
            line[line_length] = c;
            ++line_length;
        }
    }

    return 0;
}

int htoi(char s[]) {
    int n;
    int value;
    int i;

    value = 0;
    i = 0;

    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        i = 2;
    }

    for (i; s[i] != '\0'; ++i) {
        if (s[i] >= '0' && s[i] <= '9') {
            n = s[i] - '0';
        } else if (s[i] >= 'a' && s[i] <= 'f') {
            n = 10 + s[i] - 'a';
        } else if (s[i] >= 'A' && s[i] <= 'F') {
            n = 10 + s[i] - 'A';
        } else {
            printf("error: string not in hex format");
            return -1;
        }

        value = 16 * value + n;
    }

    return value;
}
