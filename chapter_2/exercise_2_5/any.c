#include <stdio.h>

#define MAX_SIZE 100

int any(char s1[], char s2[]);
void get_line(char s[]);

int main() {
    char s1[MAX_SIZE];
    char s2[MAX_SIZE];
    int first_idx;

    get_line(s1);
    get_line(s2);

    first_idx = any(s1, s2);

    printf("%d\n", first_idx);

    return 0;
}

int any(char s1[], char s2[]) {
    int res;

    res = -1;

    for (int i = 0; s2[i] != '\0'; ++i) {
        for (int j = 0; s1[j] != '\0'; ++j) {
            if (s2[i] == s1[j]) {
                if (res == -1 || j < res) {
                    res = j;
                }
                break;
            }
        }
    }

    return res;
}

void get_line(char s[]) {
    int c;
    int i;

    for (i = 0; (c = getchar()) != '\n'; ++i) {
        s[i] = c;
    }

    s[i] = '\0';
}
