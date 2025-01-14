#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 20000
#define MAXLINE 1000
#define STORAGE (MAXLINES * MAXLINE)

char *lineptr[MAXLINES];
char storage[STORAGE];
int storagep = 0;

int readlines(char *lineptr[]);
int readline_(char *s);
void tail(char *lineptr[], int nlines, int n);
void writelines(char *lineptr[], int nlines);

int main(int argc, char *argv[]) {
    int lines = 10;
    int nlines;

    if (argc == 2) {
        if (*argv[1] == '-') {
            lines = atoi(argv[1] + 1);
        } else {
            printf("error: invalid args\n");
            return 0;
        }
    } else if (argc > 2) {
        printf("error: invalid args\n");
        return 1;
    }

    if ((nlines = readlines(lineptr)) >= 0) {
        tail(lineptr, nlines, lines);
        return 0;
    } else {
        printf("error: coudn't process lines\n");
        return 1;
    }
}

int readlines(char *lineptr[]) {
    int len;
    char line[MAXLINE];
    int lines = 0;

    while ((len = readline_(line)) > 0 && lines <= MAXLINES) {
        if (storagep + len <= STORAGE) {
            strcpy((storage + storagep), line);
            *lineptr++ = (storage + storagep);
            storagep += len;
            ++lines;
        } else {
            printf("error: storage limit hit. Cannot add line\n");
        }
    }

    return lines;
}

int readline_(char *s) {
    char c;
    int i = 0;

    while (i <= MAXLINE && (c = getchar()) != EOF && c != '\n')
        *(s + i++) = c;

    if (c == EOF) {
        *(s + i) = '\0';
        return i;
    }
    
    *(s + i++) = '\0';

    return i;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines--) {
        printf("%s\n", *lineptr++);
    }
}

void tail(char *lineptr[], int nlines, int n) {
    int start = nlines - n;
    writelines(lineptr + (start > 0 ? start : 0), (start > 0) ? n : nlines);
}
