#include <stdio.h>
#define MAXLINE 1000
#define CUTOFF 80

int getinputline(char line[], int maxline);

int main() {
    int len;
    char line[MAXLINE];

    while ((len = getinputline(line, MAXLINE)) > 0) {
        if (len > CUTOFF) {
            printf("%s", line);
        }
    }

    return 0;
}

int getinputline(char line[], int maxsize) {
    int c, i;

    for (i = 0; i < maxsize - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }

    if (c == '\n') {
        line[i] = '\n';
        ++i;
    }

    line[i] = '\0';

    return i;    
}
