#include <stdio.h>

#define MAX_LINE_LENGTH 100
#define MAX_LINES 100
#define STORAGE (MAX_LINE_LENGTH * MAX_LINES)

char storage[STORAGE];
int numeric = 0;
int reverse = 0;
int fold = 0;
int dir_ord = 0;
int *configs[] = { NULL, NULL, NULL, NULL, NULL };
int fields_used[] = { 0, 0, 0, 0 };
int configs_storage[20];
int configs_storage_p = 0;
char second_storage[STORAGE];
char *mid_p_storage[STORAGE];

int strcmp(char *s, char *t);
int read_lines(char *lines[]);
void strcpy(char *s, char *t);
int read_line(char *line, char *line_2, int pointer_starts[]);
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
int process_flags(int argc, char *argv[]);
int read_lines_new(char *lines[], char **field_lines[]);

int main(int argc, char *argv[]) {
    int nlines;
    char *lines[MAX_LINES];
    char **field_lines[MAX_LINES];

    if (!process_flags(argc, argv)) {
        printf("Invalid args. Terminating program\n");
        return 1;
    }

    printf("Config before we read some lines:\n\n");

    // for (int i = 0; i < 4; ++i) {
    //     printf("Configs position %d is: ", i);
    //     if (*(configs + i) == NULL) {
    //         printf("NULL\n");
    //     } else {
    //         printf("%d\n", **(configs + i));
    //     }
    // }

    for (int i = 0; i < 4; ++i) {
        if (*(configs + i) == NULL) {
            break;
        }
        printf("Sorting config with precedence of %d: ", i + 1);
        if (**(configs + i) == 0) {
            printf("A Sort on all lines\n");
        } else {
            printf("A sort on field %d\n", **(configs + i));
        }

        printf("numeric: %d\tfolded: %d\nreversed: %d\tdirectory: %d\n\n", 
            *(*(configs + i) + 1), *(*(configs + i) + 2), *(*(configs + i) + 3), *(*(configs + i) + 4));
    }

    nlines = read_lines_new(lines, field_lines);

    if (nlines == -1) {
        printf("read_lines error: terminating program\n");
        return 1;
    }
    printf("\nNumber of input lines: %d\n", nlines);

    if (*configs == NULL) {
        printf("No config given\n\n");

        qsort(lines, 0, nlines - 1, strcmp, reverse);
    } else {
        printf("Config given\n\n");
        printf("First config precedence: field-%d\n", **configs);
    }

    write_lines(lines, nlines);

    // while (--argc > 0) {
    //     ++argv;

    //     if (strcmp(*argv, "-n") == 0) {
    //         numeric = 1;
    //     } else if (strcmp(*argv, "-r") == 0) {
    //         reverse = 1;
    //     } else if (strcmp(*argv, "-f") == 0) {
    //         fold = 1;
    //     } else if (strcmp(*argv, "-d") == 0) {
    //         dir_ord = 1;
    //     }
    // }
    
    // nlines = read_lines(lines);

    // printf("\n");

    // qsort(lines, 0, nlines - 1, (numeric) ? numcmp : (dir_ord) ? ((fold) ? folded_directory_order : directory_order) : ((fold) ? folded_strcmp : strcmp), reverse);

    // printf("\n");

    // write_lines(lines, nlines);

    // printf("\n");

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

// int read_lines(char *lines[]) {
//     int length;
//     char line[MAX_LINE_LENGTH];
//     int num_of_lines = 0;
//     int storage_length = 0;

//     while (length = read_line(line)) {
//         if ((storage_length + length + 1) < STORAGE) {
//             strcpy((storage + storage_length), line);
//             *(lines + num_of_lines++) = (storage + storage_length);
//             storage_length += length + 1;
//         } else {
//             printf("Too much content. not enough storage. stopping at current line");
//             return num_of_lines;
//         }
//     }

//     return num_of_lines;
// }

int read_lines_new(char *lines[], char **field_lines[]) {
    int length;
    char line[MAX_LINE_LENGTH];
    char line_2[MAX_LINE_LENGTH];
    int pointer_starts[3];
    int num_of_lines = 0;
    int storage_length = 0;
    int mid_p_storage_length = 0;

    while (length = read_line(line, line_2, pointer_starts)) {
        if (length < 0) {
            printf("error: following line not in proper format -> %s\n", line);
            return -1;
        }
        if ((storage_length + length + 1) < STORAGE) {
            strcpy((storage + storage_length), line);
            *(lines + num_of_lines) = (storage + storage_length);

            strcpy((second_storage + storage_length), line_2);
            *(mid_p_storage + mid_p_storage_length) = (second_storage + storage_length + pointer_starts[0]);
            *(mid_p_storage + mid_p_storage_length + 1) = (second_storage + storage_length + pointer_starts[1]);
            *(mid_p_storage + mid_p_storage_length + 2) = (second_storage + storage_length + pointer_starts[2]);
            mid_p_storage_length += 3;

            *(field_lines + num_of_lines) = (mid_p_storage + mid_p_storage_length);

            storage_length += length + 1;
            ++num_of_lines;
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

int read_line(char *line, char *line_2, int pointer_starts[]) {
    int length;
    char c;
    int comma_count = 0;

    for (length = 0; length < (MAX_LINE_LENGTH - 1) && (c = getchar()) != EOF && c != '\n'; ++length) {
        *(line + length) = c;
        
        if (c == ',') {
            ++comma_count;
            *(line_2 + length) = '\0';
        }
    }
    
    if (c == '\n') {
        *(line_2 + length) = '\n';
        *(line + length++) = '\n';
    }

    *(line + length) = '\0';
    *(line_2 + length) = '\0';

    if (comma_count < 2 && !(length == 0 && c == EOF)) {
        return -1;
    }

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

int process_flags(int argc, char *argv[]) {
    // return 0 if invalid input
    // return 1 if valid input
    char *arg;
    int n, r, f, d, field;
    int **configp = &configs;

    while (--argc) {
        arg = *++argv;
        n = r = f = d = field = 0;

        if (*arg == '-') { // the beginning of a flag
            while (*++arg != '\0') {
                switch (*arg) {
                    case ('1'):
                        if (field) {
                            printf("Invalid flag: tried to use field %c for this flag. Field %d already chosen. At most 1 field per flag.\n", *arg, field);
                            return 0;
                        }
                        field = *arg - '0';
                        break;
                    case ('2'):
                        if (field) {
                            printf("Invalid flag: tried to use field %c for this flag. Field %d already chosen. At most 1 field per flag.\n", *arg, field);
                            return 0;
                        }
                        field = *arg - '0';
                        break;
                    case ('3'):
                        if (field) {
                            printf("Invalid flag: tried to use field %c for this flag. Field %d already chosen. At most 1 field per flag.\n", *arg, field);
                            return 0;
                        }
                        field = *arg - '0';
                        break;
                    case 'n':
                        n = 1;
                        break;
                    case 'r':
                        r = 1;
                        break;
                    case 'f':
                        f = 1;
                        break;
                    case 'd':
                        d = 1;
                        break;
                    default:
                        printf("Invalid flag: %c", *arg);
                        return 0;
                }
            }
        } else {
            printf("Invalid argument: %s\n", *argv);
        }


        // Here, we assign the config. For now, just testing:
        if (fields_used[field]) {
            printf("Duplicate field used: %d\n", field);
            return 0;
        } else {
            fields_used[field] = 1;
        }

        printf("The current start of configs points to :\n");
        if (*configs ==  NULL) {
            printf("Its Null\n");
        } else {
            printf("%d\n", **configs);
        }

        configs_storage[configs_storage_p + 0] = field;
        configs_storage[configs_storage_p + 1] = n;
        configs_storage[configs_storage_p + 2] = f;
        configs_storage[configs_storage_p + 3] = r;
        configs_storage[configs_storage_p + 4] = d;

        *configp++ = configs_storage + configs_storage_p;

        configs_storage_p += 5;

        printf("Given sorting config for the %s flag\n", *argv);

        if (field) {
            printf("Config for field %d\n", field);
        } else {
            printf("Config for all lines\n");
        }

        printf("numeric: %d\tfolded: %d\n", n, f);
        printf("directory: %d\treversed: %d\n", d, r);
        printf("\n");
    }
}
