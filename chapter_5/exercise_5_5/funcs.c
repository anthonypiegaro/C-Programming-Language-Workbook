/* 
    Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which
    operate on at most the first n characters of their argument strings. For example,
    strncpy(s,t,n) copies at most n characters of t to `s.
*/

#include <stdio.h>

#define SIZE 100

void strcpy(char *s, char *t);
int strcmp(char *s, char *t);
char *strncpy(char *dest, char *src, int n);
void strncat(char *s, char *t, int n);
int strncmp(char *s, char *t, int n);

int main() {
    printf("%d\n", strncmp("Hi", "Hi there", 2));

    return 0;
}

void strcpy(char *s, char *t) {
    while (*s++ = *t++)
        ;
}

/* strncpy copies the first n chars from string pointed by source to the destination. */
char *strncpy(char *dest, char *src, int n) {
    char *start_of_dest = dest;

    for (int i = 0; i < n && *src != '\0'; ++i)
        *dest++ = *src++;
    
    *dest = '\0';

    return start_of_dest;
}

int strcmp(char *s, char *t) {
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

void strncat(char *s, char *t, int n) {
    int i;

    while (*s)
        s++;

    for (i = 0; i < n && *t; ++i)
        *s++ = *t++;
    
    *s = '\0';
}

int strncmp(char *s, char *t, int n) {
    int i;

    for (i = 0; i < n && *s == *t; i++) {
        if (*s == '\0')
            return 0;
        ++s;
        ++t;
    }

    if (i == n)
        return 0;

    return *s - *t;
}
