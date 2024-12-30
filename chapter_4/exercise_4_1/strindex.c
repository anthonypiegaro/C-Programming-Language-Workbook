#include <stdio.h>

#define MAX_SIZE 1000

int strindex(char s[], char t[]);

int main() {
    printf("%d\n", strindex("Hello World", "zorld"));
    return 0;
}

int strindex(char s[], char t[]) {
    int i, j, k, res;

    res = -1;

    for (i = 0; s[i] != '\0'; ++i) {
        for (j = i, k = 0; s[j] == t[k] && t[k] != '\0'; ++j, ++k) {
            ;
        }

        if (t[k] == '\0') {
            res = i;
        }
    }

    return res;
}
