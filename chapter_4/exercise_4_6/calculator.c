#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
#define BUFFSIZE 100
#define SIN 2000
#define POW 2001
#define VAR 2002
#define VAR_ASSIGN 2003
#define VARSIZE 26

int sp = 0;
double val[MAXVAL];
char buf[BUFFSIZE];
int bufp = 0;
double var[VARSIZE];
char var_init[VARSIZE];
double curr_var_val;

int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
void peek(void);
void swap(void);
void duplicate(void);
void clear(void);
int isupperchar(char c);

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
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
            case 'p':
                peek();
                break;
            case 'd':
                duplicate();
                break;
            case 's':
                swap();
                break;
            case 'c':
                clear();
                break;
            case SIN:
                push(sin(pop()));
                break;
            case 'e':
                push(exp(pop()));
                break;
            case POW:
                push(pow(pop(), pop()));
                break;
            case VAR:
                push(curr_var_val);
                break;
            case VAR_ASSIGN:
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break; 
            default:
                printf("error: unknown command %s\n", s);
                break; 
        }
    }
    return 0;
}

void push(double f) {
    if (sp < MAXVAL) {
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
    int i, c, isvar, var_name;
    isvar = 0;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-' && c != 's' && c != 'p' && !isupperchar(c)) {
        return c;
    }
    i = 0;
    if (c == '-') {
        if (!isdigit((c = getch())) && c != '.') {
            ungetch(c);
            return '-';
        } else {
            s[++i] = c;
        }
    } else if (c == 's') {
        if ((c = getch()) != 'i') {
            ungetch(c);
            return 's';
        } else {
            if ((c = getch()) != 'n') {
                ungetch(c);
                ungetch(c);
                return 's';
            } else {
                return SIN;
            }
        }
    } else if (c == 'p') {
        if ((c = getch()) != 'o') {
            ungetch(c);
            return 'p';
        } else {
            if ((c = getch()) != 'w') {
                ungetch(c);
                ungetch(c);
                return 'p';
            } else {
                return POW;
            }
        }
    } else if (isupperchar(c)) {
        var_name = c;
        if ((c = getch()) == '=') {
            printf("Here 4\n");
            c = getch();
            if (isdigit(c)) {
                printf("Here 5 and c is %d", c);
                var_init[var_name - 'A'] = 1;
                isvar = 1;
                s[0] = c;
            } else {
                return c;
            }
        } else if (c == ' ' || c == '\n') {
            if (c == '\n') {
                ungetch(c);
            }
            if (var_init[var_name - 'A']) {
                curr_var_val = var[var_name - 'A'];
            } else {
                curr_var_val = 0;
            }
            return VAR;
        } else {
            ungetch(c);
        }
    }

    printf("Here 7 and c is %d", c);

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';

    if (c != EOF)
        ungetch(c);

    if (isvar) {
        printf("here\n");
        printf("And the value that should be assigned: %s\n", s);
        var[var_name - 'A'] = atof(s);
        
        return VAR_ASSIGN;
    }
    return NUMBER;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

void peek(void) {
    if (sp > 0) {
        printf("\t%.8g\n", val[sp - 1]);
    } else {
        printf("error: stack empty");
    }
}

void swap(void) {
    double temp;

    if (sp > 1) {
        temp = val[sp - 2];
        val[sp - 2] = val[sp - 1];
        val[sp - 1] = temp;
    } else {
        printf("error: less than two elements in the stack");
    }
}

void duplicate(void) {
    if (sp > 0) {
        val[sp] = val[sp - 1];
        ++sp;
    } else {
        printf("error: stack empty");
    }
}

void clear(void) {
    sp = 0;
}

int isupperchar(char c) {
    return (65 <= c && c <= 90);
}
