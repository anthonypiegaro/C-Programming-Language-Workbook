#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXLINES 50000
#define MAXLEN 1000
#define MAXSTORAGE 1000000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines, char *storage);
void writelines(char *lineptr[], int nlines);
int get_line(char *s, int lim);
void q_sort(char *lineptr[], int left, int right);
void swap(char *v[], int i, int j);

int main() {
    int nlines;
    clock_t start, end;
    double cpu_time_used;
    char storage[MAXSTORAGE];

    start = clock();
    if ((nlines = readlines(lineptr, MAXLINES, storage)) >= 0) {
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("Time using own storage:\t%.10f\n", cpu_time_used);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int readlines(char *lineptr[], int maxlines, char *storage) {
    int len, nlines, storage_len;
    char *p, line[MAXLEN];

    nlines = 0;
    storage_len = 0;
    while ((len = get_line(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || storage_len + len >= MAXSTORAGE) {
            return -1;
        } else {
            line[len - 1] = '\0';
            strcpy((storage + storage_len), line);
            lineptr[nlines++] = (storage + storage_len);
            storage_len += len;
        }
    }

    return nlines;
}

void writelines(char *lineptr[], int nlines) {
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}

int get_line(char *s, int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        *(s + i) = c;
    }

    if (c == '\n')
        *(s + i++) = '\n';
    
    *(s + i) = '\0';

    return i;
}

void q_sort(char *v[], int left, int right) {
    int i, last;
    
    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);
    last = left;

    for (i = left + 1; i <= right; ++i) {
        if (strcmp(v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }
    swap(v, left, last);

    q_sort(v, left, last - 1);
    q_sort(v, last + 1, right);
}

void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
