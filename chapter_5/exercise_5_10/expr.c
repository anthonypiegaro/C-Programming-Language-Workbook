#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER 1
#define MAXSIZE 10

int stack[MAXSIZE];
int stackp = 0;

char gettype(char *s);
void push(int number);
int pop(void);

int main(int argc, char *argv[]) {
    int op2;

    while (--argc) {
        switch (gettype(*++argv)) {
            case NUMBER:
                push(atoi(*argv));
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
                if (op2 == 0) {
                    printf("error: cannot divide by zero.\n");
                    return 1;
                }
                push(pop() / op2);
                break;
            case '%':
                op2 = pop();
                if (op2 == 0) {
                    printf("error: cannot mod by zero.\n");
                    return 1;
                }
                push(pop() % op2);
                break;
            default:
                printf("error: invalid arg \"%s\"\n", *argv);
                break;
        }
    }

    printf("Result: %d\n", pop());
    
    return 0;
}

char gettype(char *s) {
    while (isspace(*s))
        ++s;

    if (*s == '*' || *s == '/' || *s == '%') {
        if (*(s + 1) != '\0')
            return -1;
        return *s;
    }

    if (*s == '+' || *s == '-') {
        if (*(s + 1) == '\0')
            return *s;
        ++s;
    }

    while (isdigit(*s))
        ++s;
    
    return (*s == '\0') ? NUMBER : -1;
}

void push(int number) {
    if (stackp < MAXSIZE) {
        stack[stackp++] = number;
    } else {
        printf("error: stack full, cannot push %d to stack\n", number);
    }
}

int pop(void) {
    if (stackp > 0) {
        return stack[--stackp];
    }
    printf("error: stack is empty, returning 0\n");
    return 0;
}
