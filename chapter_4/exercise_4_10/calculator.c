#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXSIZE 100

int sp = 0;
double val[MAXSIZE];
int linep = 0;
int line[MAXSIZE];
int EOF_HIT = 0;

int getop(char []);
void push(double);
double pop(void);
void get_line(void);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while (!EOF_HIT) {
        get_line();
        linep = 0;

        while ((type = getop(s)) != '\0') {
            switch (type) {
                case NUMBER:
                    push(atof(s));
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0) {
                        push(pop() / op2);
                    } else {
                        printf("error: zero divisor\n");
                    }
                    break;
                case '%':
                    op2 = pop();
                    if (op2 != 0.0) {
                        push((int)pop() % (int)op2);
                    } else {
                        printf("error: zero divisor\n");
                    }
                    break;
                case '\n':
                    printf("\t%.8g\n", pop());
                    break; 
                default:
                    printf("error: unknown command %s\n", s);
                    break; 
            }
        }
    }
    return 0;
}

void push(double f) {
    if (sp < MAXSIZE) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

double pop(void) {
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int getop(char s[]) {
    int i, c;

    while ((s[0] = c = line[linep++]) == ' ' || c == '\t')
        ;

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-') {
        if (!isdigit((c = line[linep])) && c != '.') {
            return '-';
        } else {
            s[++i] = c;
        }
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = line[linep++]))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = line[linep++]))
            ;
    s[i] = '\0';

    return NUMBER;
}

void get_line(void) {
    int c, i;
    i = 0;

    while ((c = getchar()) != EOF && c != '\n') {
        line[i++] = c;
    }

    if (c == '\n') {
        line[i++] = '\n';
        line[i] = '\0';
    } else if (c == EOF) {
        line[i] = '\0';
        EOF_HIT = 1;
    }
}
