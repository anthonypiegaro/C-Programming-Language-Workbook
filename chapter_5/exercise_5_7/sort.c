#include <stdio.h>
#include <string.h>

#define MAXLINES 5000
#define MAXLINELENGTH 100
#define STORAGE (MAXLINELENGTH * MAXLINELENGTH)

char storage[STORAGE];
int storagep = 0;
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

int main() {
    int nlines;

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort.");
        return 1;
    }
}

int getline_(char *, int);

int readlines(char *lineptr[], int maxlines) {
    int len, nlines;
    char *p, line[MAXLINELENGTH];

    nlines = 0;
    while ((len = getline_(line, MAXLINELENGTH)) > 0)
        if (nlines >= maxlines || (storagep + len) >= STORAGE)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy((storage + storagep), line);
            lineptr[nlines++] = storage + storagep;
            storagep += len;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

void qsort(char *v[], int left, int right) {
    int i, last;

    void swap(char *v[], int l, int r);

    if (left >= right)
        return;
    
    swap(v, left, (left + right) / 2);

    last = left;

    for (i = left + 1; i <= right; ++i) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);

    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int getline_(char *s, int lim) {
    int c;
    char *start = s;

    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    
    if (c == '\n')
        *s++ = '\n';
    
    *s = '\0';

    return s - start;
}
