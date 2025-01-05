#include <stdio.h>
#include <string.h>

#define SIZE 100

void strncpy_(char *s, char *t, int n);
void strncat_(char *s, char *t, int n);
int strncmp_(char *s, char *t, int n);

int main() {
    char r[SIZE] = "Hello";
    char s[SIZE] = "Right-handed";

    strncpy_(r, "one", 6);

    strncat_(s, " Left-handed", 15);

    printf("%s\n", r);
    printf("%s\n", s);

    return 0;
}

void strncpy_(char *s, char *t, int n) {
    for (int i = 0; i < n && *t != '\0'; ++i)
        *s++ = *t++;
    
    if (*t == '\0')
        *s = '\0';
}

void strncat_(char *s, char *t, int n) {
    while (*s != '\0')
        ++s;
    
    for (int i = 0; i < n && *t != '\0'; ++i)
        *s++ = *t++;
    
    *s = '\0';
}
