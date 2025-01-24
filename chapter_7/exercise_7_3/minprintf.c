#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main() {
    minprintf("Testing a char: %c\nTesting a string: %s\nTesting an integer with d: %d\nTesting an integer with i: %i\nTesting a double: %f\n", 'c', "Hello World", 10, 12, 23.6);

    return 0;
}

void minprintf(char *fmt, ...) {
    va_list ap;
    char *p;
    char cval;
    char *sval;
    int ival;
    double fval;

    va_start(ap, fmt);

    for (p = fmt; *p; ++p) {
        if (*p != '%') {
            putchar(*p);
        } else {
            switch(*++p) {
                case 'c':
                    cval = va_arg(ap, int);
                    printf("%c", cval);
                    break;
                case 's':
                    sval = va_arg(ap, char *);
                    printf("%s", sval);
                    break;
                case 'd':
                case 'i':
                    ival = va_arg(ap, int);
                    printf("%d", ival);
                    break;
                case 'f':
                    fval = va_arg(ap, double);
                    printf("%f", fval);
                    break;
                default:
                    printf("error: not a valid converion type: \"%c\"\n", *p);
                    break;
            }
        }
    }

    va_end(ap);
}
