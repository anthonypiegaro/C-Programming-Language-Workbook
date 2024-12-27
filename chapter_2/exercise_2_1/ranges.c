#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    // char
    printf("signed char range: %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char range: 0 to %u\n\n", UCHAR_MAX);

    // short
    printf("signed short range: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short range: 0 to %u\n\n", USHRT_MAX);

    // int
    printf("signed int range: %d to %d\n", INT_MIN, INT_MAX);
    printf("unsigned int range: 0 to %u\n\n", UINT_MAX);

    // long
    printf("signed long range: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long range: 0 to %lu\n", ULONG_MAX);

    return 0;
}
