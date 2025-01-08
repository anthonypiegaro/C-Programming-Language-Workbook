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
int folded_strcmp(char *s, char *t);
int directory_order(char *s, char *t);
int folded_directory_order(char *s, char *t);
int isupper(char c);
int islower(char c);
int to_lower(char c);

int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0;
    int reverse = 0;
    int fold = 0;
    int dir_ord = 0;
    char *lines[MAX_LINES];

    while (--argc > 0) {
        ++argv;

        if (strcmp(*argv, "-n") == 0) {
            numeric = 1;
        } else if (strcmp(*argv, "-r") == 0) {
            reverse = 1;
        } else if (strcmp(*argv, "-f") == 0) {
            fold = 1;
        } else if (strcmp(*argv, "-d") == 0) {
            dir_ord = 1;
        }
    }
    
    nlines = read_lines(lines);

    printf("\n");

    qsort(lines, 0, nlines - 1, (numeric) ? numcmp : (dir_ord) ? ((fold) ? folded_directory_order : directory_order) : ((fold) ? folded_strcmp : strcmp), reverse);

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

int folded_strcmp(char *s, char*t) {
    char s_holder;
    char t_holder;
    while (*s != '\0' && *s == *t) {
        *++s;
        *++t;
    }

    if (65 <= *s && *s <= 90) {
        s_holder = *s + 32;
    } else {
        s_holder = *s;
    }

    if (65 <= *t && *t <= 90) {
        t_holder = *t + 32;
    } else {
        t_holder = *t;
    }

    if (s_holder < t_holder) {
        return -1;
    } else if (s_holder == t_holder) {
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

int directory_order(char *s, char *t) {
    while (1) {
        if (!islower(*s) && !isupper(*s) && !isdigit(*s) && *s != ' ' && *s != '\0')
            *++s;
        if (!islower(*t) && !isupper(*t) && !isdigit(*t) && *t != ' ' && *t != '\0')
            *++t;
        
        if (*s < *t) {
            return -1;
        } else if (*s > *t) {
            return 1;
        } else if (*s == '\0' && *t == '\0') {
            return 0;
        }

        *++s;
        *++t;
    }
}

int folded_directory_order(char *s, char *t) {
    while (1) {
        if (!islower(*s) && !isupper(*s) && !isdigit(*s) && *s != ' ' && *s != '\0')
            *++s;
        if (!islower(*t) && !isupper(*t) && !isdigit(*t) && *t != ' ' && *t != '\0')
            *++t;
        
        if (to_lower(*s) < to_lower(*t)) {
            return -1;
        } else if (to_lower(*s) > to_lower(*t)) {
            return 1;
        } else if (*s == '\0' && *t == '\0') {
            return 0;
        }

        *++s;
        *++t;
    }
}

int isupper(char c) {
    return 65 <= c && c <= 90;
}

int islower(char c) {
    return 97 <= c && c <= 122;
}

int to_lower(char c) {
    if (isupper(c)) {
        return c + 32;
    }
    return c;
}
