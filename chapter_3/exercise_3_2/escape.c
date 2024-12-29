#include <stdio.h>

#define MAX_SIZE 1000

void escape(char to[], char from[]);
void get_line(char s[]);

int main() {
    int c;
    char fro[MAX_SIZE];
    char to[MAX_SIZE];

    get_line(fro);
    printf("%s\n", fro);

    escape(to, fro);

    printf("%s\n", to);

    return 0;
}

void escape(char to[], char from[]) {
    int i;
    int j;

    for (i = j = 0; from[i] != '\0'; ++i) {
        switch (from[i]) {
            case '\t':
                to[j++] = '\\';
                to[j++] = 't';
                break;
            case '\n':
                to[j++] = '\\';
                to[j++] = 'n';
                break;
            default:
                to[j++] = from[i];
                break;
        }
    }

    to[j] = '\0'; 
}

void get_line(char s[]) {
    int c;
    int i = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            s[i] = c;
            ++i;
            break;
        }
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
}
