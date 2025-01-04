#include <stdio.h>

#define MAX_SIZE 100

void strcat(char *s, char *t);

int main() {
    char s[MAX_SIZE] = "Hello";

    strcat(s, " World!");

    printf("%s\n", s);
    return 0;
}

void strcat(char *s, char *t) {
    while (*s)
        ++s;
    
    while (*s++ = *t++)
        ;
}
