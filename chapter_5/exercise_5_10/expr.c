#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSIZE 100
#define NUMBER 1

double stack[MAXSIZE];
int stackp = 0;

char getop(char *arg, double *i);
void push(double i);
double pop(void);

int main(int argc, char *argv[]) {
    char *arg;
    char type;
    double i, op2;

    while (--argc > 0) {
        arg = *++argv;

        type = getop(arg, &i);

        switch (type) {
            case NUMBER:
                push(i);
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
                if (op2 == 0.0) {
                    printf("invalid divide by zero. terminating program");
                    return -1;
                }
                push(pop() / op2);
                break;
            case '%':
                op2 = pop();
                if (op2 == 0.0) {
                    printf("invalid mod by zero. terminating program");
                    return -1;
                }
                push((int)pop() % (int)op2);
                break;
            default:
                printf("invalid input %c. Terminating program\n", type);
                return -1;
        }
    }

    if (stackp != 1) {
        printf("Incomplete expression\n");
    } else {
        printf("%f\n", pop());
    }

    return 0;
}

void push(double i) {
    if (stackp < MAXSIZE) {
        stack[stackp++] = i;
    } else {
        printf("error: stack full. cannot push number to stack");
    }
}

double pop(void) {
    if (stackp > 0) {
        return stack[--stackp];
    } else {
        printf("stack empty: returning 0");
        return 0;
    }
}

char getop(char *arg, double *i) {
    if (isdigit(*arg) || ((*arg == '+' || *arg == '-') && isdigit(*(arg + 1))) || *arg == '.') {
        *i = atof(arg);
        return NUMBER;
    }

    return *arg;
}
