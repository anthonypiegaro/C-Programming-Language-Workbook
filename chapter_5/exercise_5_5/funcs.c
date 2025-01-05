#include <stdio.h>
#include <string.h>

#define SIZE 100

void strncpy_(char *s, char *t, int n);
void strncat_(char *s, char *t, int n);
int strncmp_(char *s, char *t, int n);

int main() {
    char r[SIZE] = "Hello";

    strncpy_(r, "one", 6);

    printf("%s\n", r);

    return 0;
}

void strncpy_(char *s, char *t, int n) {
    for (int i = 0; i < n && *t != '\0'; ++i)
        *s++ = *t++;
    
    if (*t == '\0')
        *s = '\0';
}
