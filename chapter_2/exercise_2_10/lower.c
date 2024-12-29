#include <stdio.h>

#define MAX_SIZE 100

void lower(char s[]);
void get_line(char s[]);

int main() {
    char s[MAX_SIZE];
    int c;

    while (1) {
        get_line(s);
        lower(s);

        printf("%s\n", s);
    }

    return 0;
}

void lower(char s[]) {
    for (int i = 0; s[i] != '\0'; ++i) {
        s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] + 32 : s[i];
    }
}

void get_line(char s[]) {
    int c;
    int i;

    for (i = 0; (c = getchar()) != '\n'; ++i) {
        s[i] = c;
    }

    s[i] = '\0';
}
