#include <stdio.h>

#define MAX_LINE_LENGTH 150
#define MAX_LINES 10000
#define STORAGE (MAX_LINE_LENGTH * MAX_LINES)

char *storage[STORAGE];

void tail(char *lines[], int num_of_lines, int lines_to_print);
int process_args(int argc, char *argv[], int *n);
int isdigit(char c);
int atoi(char *s);
int read_lines(char *lines[]);
int read_line(char *line_pointer);
void strcpy(char *s, char *t);

int main(int argc, char *argv[]) {
    char *lines[MAX_LINES];
    int num_of_lines;
    int lines_to_print = 10;

    if (!process_args(argc, argv, &lines_to_print)) {
        printf("Terminating program due to invalid args\n");
        return 1;
    }

    num_of_lines = read_lines(lines);
    printf("\n");

    tail(lines, num_of_lines, lines_to_print);

    return 0;
}

int process_args(int argc, char *argv[], int *n) {
    char *arg;

    while (--argc) {
        arg = *++argv;

        if (*arg == '-') {
            *n = atoi(++arg);
            if (*n == -1) {
                printf("Invalid \"-n\" argument %s\n", arg);
                return 0;
            }
        } else {
            printf("Invalid input %s\n", arg);
            return 0;
        }
    }

    return 1;
}

int atoi(char *s) {
    int n = 0;

    while (*s) {
        if (isdigit(*s)) {
            n = 10 * n + (*s - '0');
            ++s;
        } else {
            return -1;
        }
    }

    return n;
}

int isdigit(char c) {
    return 48 <= c && c <= 57;
}

int read_lines(char *lines[]) {
    int num_of_lines, line_length, storage_length;
    char line[MAX_LINE_LENGTH];

    num_of_lines = 0;
    storage_length = 0;

    while (line_length = read_line(line)) {
        if ((storage_length + line_length) > STORAGE) {
            return -1;
        } else {
            strcpy((storage + storage_length), line);
            *(lines + num_of_lines++) = (storage + storage_length);
            storage_length += line_length;
        }
    }

    return num_of_lines;
}

int read_line(char *line) {
    int c, length;

    for (length = 0; length < (MAX_LINE_LENGTH - 1) && (c = getchar()) != EOF && c != '\n'; ++length)
        *(line + length) = c;
    
    if (c == '\n')
        *(line + length++) = '\n';
    
    *(line + length) = '\0';

    return length;
}

void strcpy(char *s, char *t) {
    while (*s++ = *t++)
        ;
}

void tail(char *lines[], int num_of_lines, int lines_to_print) {
    int i = num_of_lines - lines_to_print;

    int line = (i > 0) ? i : 0;

    for (; line < num_of_lines; ++line)
        printf("%s", *(lines + line));
    
    printf("\n");
}
