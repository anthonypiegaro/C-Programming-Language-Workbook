#include <stdio.h>

#define MAX_SIZE 1000
#define TRUE 1
#define FALSE 0

void expand(char s1[], char s2[]);
int is_digit(int c);
int is_upper_char(int c);
int is_lower_char(int c);

int main() {
    char s[MAX_SIZE];
    
    expand("a--e-jA-bW-Zsdf^!4-9", s);

    printf("%s\n", s);

    return 0;
}

void expand(char s1[], char s2[]) {
    int p, pp;
    int i, j;
    int is_prev_not = 0;

    if (s1[0] == '\0') {
        s2[0] = '\0';
        return;
    } else if (s1[1] == '\0') {
        s2[0] = s1[0];
        s2[1] = '\0';
        return;
    } else {
        s2[0] = s1[0];
        s2[1] = s1[1];
        p = s1[1];
        pp = s1[0];
    }

    for (i = j = 2; s1[i] != '\0'; ++i) {
        if (
            is_prev_not == FALSE 
            && is_digit(pp)
            && p == '-'
            && is_digit(s1[i])
            && pp < s1[i]
        ) {
            is_prev_not = TRUE;
            j -= 2;

            for (int k = pp; k <= s1[i]; ++k) {
                s2[j++] = k;
            }
        } else if (
            is_prev_not == FALSE 
            && is_lower_char(pp)
            && p == '-'
            && is_lower_char(s1[i])
            && pp < s1[i]
        ) {
            is_prev_not = TRUE;
            j -= 2;

            for (int k = pp; k <= s1[i]; ++k) {
                s2[j++] = k;
            }
        } else if (
            is_prev_not == FALSE 
            && is_upper_char(pp)
            && p == '-'
            && is_upper_char(s1[i])
            && pp < s1[i]
        ) {
            is_prev_not = TRUE;
            j -= 2;

            for (int k = pp; k <= s1[i]; ++k) {
                s2[j++] = k;
            }
        } else {
            s2[j++] = s1[i];
            is_prev_not = FALSE;
        }

        pp = s2[j - 2];
        p = s2[j - 1];
    }

    s2[j] = '\0';
}

int is_digit(int c) {
    return (48 <= c && c <= 57) ? 1 : 0;
}

int is_upper_char(int c) {
    return (65 <= c && c <= 90) ? 1 : 0;
}

int is_lower_char(int c) {
    return (97 <= c && c <= 122) ? 1 : 0;
}
