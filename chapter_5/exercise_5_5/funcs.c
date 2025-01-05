#include <stdio.h>

#define SIZE 100

void strncpy(char *s, char *t, int n);
void strncat(char *s, char *t, int n);
int strncmp(char *s, char *t, int n);

int main() {
    char r[SIZE] = "Hello";
    char s[SIZE] = "Right-handed";
    char t[SIZE] = "The Remote";

    strncpy(r, "one", 6);

    strncat(s, " Left-handed", 15);

    printf("%s\n", r);
    printf("%s\n", s);
    printf("%d\n", strncmp(t, "The Remote", 45));

    return 0;
}

void strncpy(char *s, char *t, int n) {
    for (int i = 0; i < n && *t != '\0'; ++i)
        *s++ = *t++;
    
    if (*t == '\0')
        *s = '\0';
}

void strncat(char *s, char *t, int n) {
    while (*s != '\0')
        ++s;
    
    for (int i = 0; i < n && *t != '\0'; ++i)
        *s++ = *t++;
    
    *s = '\0';
}

int strncmp(char *s, char *t, int n) {
    int i;

    for (i = 0; i < n && *s != '\0' && *t != '\0'; ++i) {
        if (*s < *t) {
            return -1;
        } else if (*s > *t) {
            return 1;
        }

        ++s;
        ++t;
    }

    if (i == n)
        return 0;

    if (*s < *t) {
        return -1;
    } else if (*s == *t) {
        return 0;
    } else {
        return 1;
    }
}
