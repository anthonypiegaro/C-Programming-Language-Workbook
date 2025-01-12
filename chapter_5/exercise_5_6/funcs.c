#include <stdio.h>
#include <string.h>

#define SIZE 100

int getline_(char *s, int lim);
int atoi_(char *s);
void itoa_(int n, char *s);
void itoa_helper(int n, char *s, int *i);
void reverse_(char *s);
int strindex_(char *s, char *t);
int isdigit_(char c);


int main() {
    char s[SIZE];
    
    printf("%d\n", strindex_("Hello World!", "Wor"));
    
    return 0;
}

int getline_(char *s, int lim) {
    int i;

    for (i = 0; i < lim - 1 && (*s = getchar()) != EOF && *s != '\n'; ++i, s++)
        ;
    
    if (*s == EOF) {
        *s = '\0';
        return i;
    }

    *++s = '\0';
    return i + 1;
}

int atoi_(char *s) {
    int num, sign;

    while (*s == ' ')
        ++s;
    
    sign = (*s == '-') ? -1 : 1;

    if (*s == '-' || *s == '+')
        ++s;
    
    num = 0;
    while (isdigit_(*s))
        num = 10 * num + (*s++ - '0');

    num *= sign;

    return num;
}

void itoa_(int n, char *s) {
    int i = 0;
    int first_cut;

    if (n < 0) {
        n *= -1;
        first_cut = n % 10;
        *s = '-';
        i++;

        itoa_helper(n / 10, s, &i);

        *(s + i++) = first_cut + '0';
    } else {
        itoa_helper(n, s, &i);
    }

    *(s + i) = '\0';
}

void itoa_helper(int n, char *s, int *i) {
    if ((n / 10) > 0) {
        itoa_helper(n / 10, s, i);
    }

    *(s + (*i)++) = (n % 10) + '0'; 
}

void reverse_(char *s) {
    char temp;
    char *t = s + strlen(s) - 1;

    for (; (t - s) > 0; s++, --t) {
        temp = *s;
        *s = *t;
        *t = temp;
    }
}

int strindex_(char *s, char *t) {
    char *start = s;
    char *si;
    char *ti;

    while (*s) {
        ti = t;
        si = s;
        while (*ti && *ti == *si) {
            ++ti;
            ++si;
        }

        if (*ti == '\0')
            return s - start;
        
        ++s;
    }

    return -1;
}

int isdigit_(char c) {
    return 49 <= c && c <= 57;
}
