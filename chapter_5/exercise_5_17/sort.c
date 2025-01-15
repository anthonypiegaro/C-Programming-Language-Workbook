#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 100
#define MAXLINE 1000
#define STORAGE (MAXLINES * MAXLINE)
#define FIELDS 3
#define MAXCONFIGS 100
#define DELIMITER ','

struct Config {
    int field;
    int numeric;
    int reverse;
    int folded;
    int dir;
};

char storage[STORAGE];
int storagep = 0;
struct Config config_storage[MAXCONFIGS];
int config_storage_p = 0;

void process_args(int argc, char *argv[], struct Config *configs[]);
int readline_(char *s);
int readlines(char *lineptr[]);
void writelines(char *lineptr[], int nlines);
int strcmp_(char *s, char *t, int reverse);
int strcmp_f(char *s, char *t, int reverse);
int strcmp_d(char *s, char *t, int reverse);
int strcmp_f_d(char *s, char *t, int reverse);
int numcmp_(char *s, char *t, int reverse);
void swap(void *v[], int i, int j);
void qsort_(void *v[], int left, int right, struct Config *configs[]);
char tolower(char c);
char *dir_check(char *s);
int isdigit(char c);
int isalpha(char c);
int cmp_(char *s, char *t, struct Config config);
int abstract_cmp(int (*comp) (void *, void *), char *s, char *t, int r);
int compare_(char *s, char *t, struct Config *configs[]);
void field_cpy(char *dest, char *src, char delimiter, int field_number);

int main(int argc, char *argv[]) {
    char *lineptr[MAXLINES];
    int nlines;
    struct Config *configs[MAXCONFIGS] = {NULL};

    process_args(argc, argv, configs);

    for (int i = 0; i < MAXCONFIGS && configs[i] != 0; ++i) {
        printf("The config for the sort with precedence %d\n", i);
        printf("Field: %d\n", (**(configs + i)).field);
        printf("folded: %d\tnumeric: %d\n", (**(configs + i)).folded, (**(configs + i)).numeric);
        printf("reverse: %d\tdirectory: %d\n", (**(configs + i)).reverse, (**(configs + i)).dir);
        printf("\n");
    }

    printf("\n");

    nlines = readlines(lineptr);

    qsort_((void **) lineptr, 0, nlines - 1, configs);

    writelines(lineptr, nlines);

    return 0;
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

int strcmp_(char *s, char *t, int reverse) {
    while (*s == *t) {
        if (*s == '\0')
            return 0;
        ++s;
        ++t;
    }

    return reverse ? *t - *s : *s - *t;
}

int strcmp_f(char *s, char *t, int reverse) {
    while (tolower(*s) == tolower(*t)) {
        if (*s == '\0')
            return 0;
        ++s;
        ++t;
    }

    return reverse ? tolower(*t) - tolower(*s) : tolower(*s) - tolower(*t);
}

int strcmp_d(char *s, char *t, int reverse) {
    while (*(s = dir_check(s)) == *(t = dir_check(t))) {
        if (*s == '\0')
            return 0;
        ++s;
        ++t;
    }

    return reverse ? *t - *s : *s - *t;
}

int strcmp_f_d(char *s, char *t, int reverse) {
    while (tolower(*(s = dir_check(s))) == tolower(*((t = dir_check(t))))) {
        if (*s == '\0')
            return 0;
        ++s;
        ++t;
    }

    return reverse ? tolower(*t) - tolower(*s) : tolower(*s) - tolower(*t);
}

char *dir_check(char *s) {
    while (!isdigit(*s) && !isalpha(*s) && *s != ' ' && *s != '\0')
        ++s;
    
    printf("Using %c for comparison\n", *s);
    return s;
}

int numcmp_(char*s, char *t, int reverse) {
    double snum = atof(s);
    double tnum = atof(t);

    if (snum < tnum) {
        return reverse ? 1 : -1;
    } else if (snum == tnum) {
        return 0;
    } else {
        return reverse ? -1 : 1;
    }
}

void swap(void *v[], int i, int j) {
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort_(void *v[], int left, int right, struct Config *configs[]) {
    int last;

    if (left >= right) {
        return;
    }

    swap(v, left, (right + left) / 2);

    last = left;

    for (int i = left + 1; i <= right; ++i) {
        if (compare_(v[i], v[left], configs) < 0) {
            swap(v, ++last, i);
        }
    }

    swap(v, left, last);
    qsort_(v, left, last - 1, configs);
    qsort_(v, last + 1, right, configs);
}

int compare_(char *s, char *t, struct Config *configs[]) {
    int res;

    while (*configs && (res = cmp_(s, t, **configs)) == 0)
        ++configs;
    
    return res;
}

int cmp_(char *s, char *t, struct Config config) {
    if (config.field == 0) {
        return abstract_cmp((int (*)(void*,void*)) (config.numeric ? numcmp_ : (config.dir ? (config.folded ? strcmp_f_d : strcmp_d) : (config.folded ? strcmp_f : strcmp_))), s, t, config.reverse);
    } else {
        char s_field[MAXLINE];
        char t_field[MAXLINE];

        field_cpy(s_field, s, DELIMITER, config.field);
        field_cpy(t_field, t, DELIMITER, config.field);

        return abstract_cmp((int (*)(void*,void*)) (config.numeric ? numcmp_ : (config.dir ? (config.folded ? strcmp_f_d : strcmp_d) : (config.folded ? strcmp_f : strcmp_))), s_field, t_field, config.reverse);
    }
}

int abstract_cmp(int (*comp) (void *, void *), char *s, char *t, int r) {
    return r ? (*comp)(s, t) : -(*comp)(s, t);
}

void field_cpy(char *dest, char *src, char delimiter, int field_number) {
    int field = 1;

    while (*src != '\0' && field < field_number) {
        while (*src != delimiter && *src != '\0')
            ++src;

        if (*src == delimiter)
            ++src;

        ++field;
    }

    while (*src != ',' && *src != '\0') {
        *dest++ = *src++;
    }

    *dest = '\0';
}

char tolower(char c) {
    return (65 <= c && c <= 90) ? c + 32 : c;
}

int isdigit(char c) {
    return 48 <= c && c <= 57;
}

int isalpha(char c) {
    return (65 <= c && c <= 90) || (97 <= c && c <= 122);
}

void process_args(int argc, char *argv[], struct Config *configs[]) {
    char *arg;
    int field, numeric, reverse, folded, dir;
    int valid;

    if (argc >= MAXCONFIGS) {
        printf("error: tooo many args\n");
        return;
    }

    if (argc == 1) {
        config_storage[config_storage_p].field = 0;
        config_storage[config_storage_p].numeric = 0;
        config_storage[config_storage_p].reverse = 0;
        config_storage[config_storage_p].folded = 0;
        config_storage[config_storage_p].dir = 0;

        *configs = config_storage + config_storage_p; 

        return;
    }

    while (--argc) {
        field = numeric = reverse = folded = dir = 0;
        arg = *++argv;
        valid = 1;

        if (*arg == '-') {
            while (*++arg) {
                if (isdigit(*arg)) {
                    field = atoi(arg);

                    if (field < 0) {
                        printf("error: invalid arg \"%s\" no negatve fields\n", *argv);
                        valid = 0;
                        break;
                    } else if (field > FIELDS) {
                        printf("error: invalid arg \"%s\" field too high\n", *argv);
                        valid = 0;
                        break;
                    }
                } else if (*arg == 'n') {
                    numeric = 1;
                } else if (*arg == 'r') {
                    reverse = 1;
                } else if (*arg == 'f') {
                    folded = 1;
                } else if (*arg == 'd') {
                    dir = 1;
                } else {
                    printf("error: invalid arg \"%s\"\n", *argv);
                    valid = 0;
                    break;
                }
            }

            if (valid) {
                config_storage[config_storage_p].field = field;
                config_storage[config_storage_p].numeric = numeric;
                config_storage[config_storage_p].reverse = reverse;
                config_storage[config_storage_p].folded = folded;
                config_storage[config_storage_p].dir = dir;

                *configs = config_storage + config_storage_p++;

                ++configs;
            }
        } else {
            printf("error: unrecognized arg \"%s\"\n", *arg);
        }
    }
}
