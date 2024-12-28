#include <stdio.h>

#define MAX_SIZE 1000

int main() {
    int c;
    int line_length;
    char s[MAX_SIZE];

    line_length = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            s[line_length] = '\0';

            printf("%s\n", s);
            line_length = 0;
        } else {
            s[line_length] = c;
            ++line_length;
        }
    }

    s[line_length] = '\0';
    printf("%s\n", s);

    return 0;
}
