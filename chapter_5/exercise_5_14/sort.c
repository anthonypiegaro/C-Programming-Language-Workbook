#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 100
#define MAXLINE 1000
#define STORAGE (MAXLINES * MAXLINE)

char storage[STORAGE];
int storagep = 0;

int readline_(char *s);
int readlines(char *lineptr[]);
void writelines(char *lineptr[], int nlines);
int strcmp_(char *s, char *t);
int numcmp_(char *s, char *t);
void swap(void *v[], int i, int j);
void qsort_(void *v[], int left, int right, int (*comp) (void *, void *), int reverse);

int main(int argc, char *argv[]) {
    char *lineptr[MAXLINES];
    int nlines;
    char *arg;
    int numeric = 0;
    int reverse = 0;

    while (--argc) {
        arg = *++argv;

        if (*arg == '-') {
            if (*(arg + 1) == '\0') {
                printf("error: invalidarh %s\n", *arg);
                return 1;
            }

            while (*++arg) {
                if (*arg == 'n') {
                    numeric = 1;
                } else if (*arg == 'r') {
                    reverse = 1;
                } else {
                    printf("error: invalid arg %s\n", *argv);
                    return 1;
                }
            }
        } else {
            printf("error: invalid arg %s\n", *arg);
            return 1;
        }
    }
    printf("numeric sort: %d\treverse sort: %d\n", numeric, reverse);

    if ((nlines = readlines(lineptr)) >= 0) {
        qsort_((void **) lineptr, 0, nlines - 1, (int (*)(void*,void*)) (numeric ? numcmp_ : strcmp_), reverse);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: invalid input\n");
        return 1;
    }
}

int readline_(char *s) {
    char c;
    int i = 0;

    while (i < MAXLINE && (c = getchar()) != EOF && c != '\n')
        *(s + i++) = c;

    if (c == EOF) {
        *(s + i) = '\0';
        return i;
    }

    *(s + i++) = '\0';
    return i;
}

int readlines(char *lineptr[]) {
    char line[MAXLINE];
    int lines = 0;
    int len;

    while (lines < MAXLINES && (len = readline_(line)) > 0) {
        if (storagep + len < STORAGE) {
            strcpy((storage + storagep), line);
            *lineptr++ = (storage + storagep);
            storagep += len;
            ++lines;
        } else {
            printf("error: current line cannot fit into storage, not reading line\n");
        }
    }

    return lines;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines--) {
        printf("%s\n", *lineptr++);
    }
}

int strcmp_(char *s, char *t) {
    while (*s == *t) {
        if (*s == '\0')
            return 0;
        ++s;
        ++t;
    }

    return *s - *t;
}

int numcmp_(char*s, char *t) {
    double snum = atof(s);
    double tnum = atof(t);

    if (snum < tnum) {
        return -1;
    } else if (snum == tnum) {
        return 0;
    } else {
        return 1;
    }
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort_(void *v[], int left, int right, int (*comp) (void *, void *), int reverse) {
    int last;

    if (left >= right) {
        return;
    }

    swap(v, left, (right + left) / 2);

    last = left;

    for (int i = left + 1; i <= right; ++i) {
        if ((reverse) ? (*comp) (v[i], v[left]) > 0 : (*comp) (v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort_(v, left, last - 1, comp, reverse);
    qsort_(v, last + 1, right, comp, reverse);
}
