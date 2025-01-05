#include <stdio.h>

#define SIZE 100

int strindex(char *s, char *t);

int main() {
    printf("%d\n", strindex("Hello", "Hellos"));

    return 0;
}

int strindex(char *s, char *t) {
    char *i, *j, *k;

    for (i = s; *i != '\0'; ++i) {
        for (j = t, k = i; *j == *k; j++, k++) {
            if (*j == '\0' || *(j + 1) == '\0')
                return (i - s);
        }
    }

    return -1;
}
