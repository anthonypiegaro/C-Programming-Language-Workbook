#include <stdio.h>

#define SIZE 100

void strcat(char *s, char *t);

int main() {
    char name[SIZE] = "John";
    char last_name[SIZE] = "Doe";

    strcat(name, " ");
    strcat(name, last_name);

    printf("%s\n", name);

    return 0;
}


/* strcat: concatenate t to end of s; s must be big enough */
void strcat(char *s, char *t) {
    for (; *s != '\0'; ++s)
        ;
    
    while (*s++ = *t++)
        ;
}
