#include <stdio.h>

#define MAX_LINE_LENGTH 100
#define MAX_LINES 100
#define STORAGE (MAX_LINE_LENGTH * MAX_LINES)

char storage[STORAGE];

int strcmp(char *s, char *t);
int read_lines(char *lines[]);
void strcpy(char *s, char *t);
int read_line(char *line);
void write_lines(char *lines[], int num_of_lines);
void qsort(void *v[], int left, int right, int (*comp) (void *, void *), int reverse);
void swap(void *v[], int i, int j);
int numcmp(char *s, char *t);
int atoi(char *s);
int isdigit(char c);

int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0;
    int reverse = 0;
    char *lines[MAX_LINES];

    // if (argc > 1 && strcmp(*++argv, "-n") == 0)
    //     numeric = 1;

    while (--argc > 0) {
        argv++;

        if (strcmp(*argv, "-n") == 0) {
            numeric = 1;
        } else if (strcmp(*argv, "-r") == 0) {
            reverse = 1;
        }
    }
    
    nlines = read_lines(lines);

    printf("\n");

    qsort(lines, 0, nlines - 1, (numeric) ? numcmp : strcmp, reverse);

    printf("\n");

    write_lines(lines, nlines);

    printf("\n");

    return 0;
}

int strcmp(char *s, char*t) {
    while (*s != '\0' && *s == *t) {
        *++s;
        *++t;
    }

    if (*s < *t) {
        return -1;
    } else if (*s == *t) {
        return 0;
    } else {
        return 1;
    }
}

int read_lines(char *lines[]) {
    int length;
    char line[MAX_LINE_LENGTH];
    int num_of_lines = 0;
    int storage_length = 0;

    while (length = read_line(line)) {
        if ((storage_length + length + 1) < STORAGE) {
            strcpy((storage + storage_length), line);
            *(lines + num_of_lines++) = (storage + storage_length);
            storage_length += length + 1;
        } else {
            printf("Too much content. not enough storage. stopping at current line");
            return num_of_lines;
        }
    }

    return num_of_lines;
}

void strcpy(char *s, char *t) {
    while (*s++ = *t++)
        ;
}

int read_line(char *line) {
    int length;
    char c;

    for (length = 0; length < (MAX_LINE_LENGTH - 1) && (c = getchar()) != EOF && c != '\n'; ++length)
        *(line + length) = c;
    
    if (c == '\n') {
        *(line + length++) = '\n';
    }

    *(line + length) = '\0';

    return length;
}

void write_lines(char *lines[], int num_of_lines) {
    for (int i = 0; i < num_of_lines; ++i)
        printf("%s", *(lines + i));
}

void qsort(void *v[], int left, int right, int (*comp) (void *, void *), int reverse) {
    int i, last;

    if (left >= right) {
        return;
    }

    swap(v, left, (left + right) / 2);

    last = left;

    for (int i = left + 1; i <= right; ++i) {
        if ((reverse) ? (*comp) (v[i], v[left]) > 0 : (*comp) (v[i], v[left]) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort(v, left, last - 1, comp, reverse);
    qsort(v, last + 1, right, comp, reverse);
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int numcmp(char *s, char *t) {
    double v1, v2;

    v1 = atoi(s);
    v2 = atoi(t);

    if (v1 < v2) {
        return -1;
    } else if (v1 == v2) {
        return 0;
    } else {
        return 1;
    }
}

int atoi(char *s) {
    int sign = 1;
    int n = 0;

    if (*s == '-') {
        sign = -1;
    }

    if (*s == '+' || *s == '-')
        s++;

    while (isdigit(*s)) {
        n = 10 * n + (*s++ - '0');
    }

    return n * sign;
}

int isdigit(char c) {
    return 48 <= c && c <= 57;
}
