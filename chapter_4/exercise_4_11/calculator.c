#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

int getop(char []);
void push(double);
double pop(void);

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
    int i, c;
    static int buff[100];
    static int buffp = 0;

    while ((s[0] = c = ((buffp > 0) ? buff[--buffp]: getchar())) == ' ' || c == '\t')
        ;

    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if (c == '-') {
        if (!isdigit((c = ((buffp > 0) ? buff[--buffp]: getchar()))) && c != '.') {
            buff[buffp++] = c;
            return '-';
        } else {
            s[++i] = c;
        }
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = ((buffp > 0) ? buff[--buffp]: getchar())))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = ((buffp > 0) ? buff[--buffp]: getchar())))
            ;
    s[i] = '\0';
    if (c != EOF)
        buff[buffp++] = c;
    return NUMBER;
}
