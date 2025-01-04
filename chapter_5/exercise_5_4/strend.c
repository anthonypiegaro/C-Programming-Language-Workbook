#include <stdio.h>

int strend(char *s, char *t);

int main() {
    printf("expect 1: %d\n", strend("Hello", "Hello"));
    printf("expect 1: %d\n", strend("", ""));
    printf("expect 1: %d\n", strend("Hello", "lo"));
    printf("expect 0: %d\n", strend("Hello", "Hello World"));
    printf("expect 0: %d\n", strend("Hello", "H"));

    return 0;
}

int strend(char *s, char *t) {
    int s_len = 0;
    int t_len = 0;

    while (*s) {
        ++s;
        ++s_len;
    }
    
    while (*t) {
        ++t;
        ++t_len;
    }

    if (s_len < t_len)
        return 0;
    
    --s;
    --t;

    for (int i = 0; i < t_len; ++i) {
        if (*s-- != *t--) {
            return 0;
        }
    }

    return 1;
}
