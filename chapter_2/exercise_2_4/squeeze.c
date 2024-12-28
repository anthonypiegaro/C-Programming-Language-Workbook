#include <stdio.h>

#define MAX_SIZE 100

void squeeze(char s1[], char s2[]);
void get_line(char s[]);

int main() {
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];

    get_line(s1);
    get_line(s2);

    squeeze(s1, s2);

    printf("%s\n", s1);

    return 0;
}

void squeeze(char s1[], char s2[]) {
    int i, j, k;

    for (k = 0; s2[k] != '\0'; ++k) {
        for (i = j = 0; s1[i] != '\0'; ++i) {
            if (s1[i] != s2[k]) {
                s1[j++] = s1[i];
            }
        }
        s1[j] = '\0';
    }
}

void get_line(char s[]) {
    int c;
    int s_length;

    s_length = 0;
    while ((c = getchar()) != '\n') {
        s[s_length++] = c;
    }

    s[s_length] = '\0';
}
