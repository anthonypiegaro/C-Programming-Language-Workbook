#include <stdio.h>

#define BUFFSIZE 100

char buf[BUFFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
void ungets(char s[]);

int main() {
    int c, i;
    char s[BUFFSIZE];
    i = 0;

    ungets("This will be called for ungets");

    while ((c = getch()) != EOF) {
        if (c == '\n') {
            s[i] = '\0';
            printf("%s\n", s);
            i = 0;
        } else {
            s[i++] = c;
        }
    }

    return 0;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void ungets(char s[]) {
    int i;

    for (i = 0; s[i] != '\0'; ++i)
        ;
    
    --i;

    for (i; i >= 0; --i) {
        ungetch(s[i]);
    }
}
