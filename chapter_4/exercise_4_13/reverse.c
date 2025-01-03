#include <stdio.h>

#define MAXSIZE 100

int END = 0;

void reverse(char s[], int l, int r);
int get_line(char s[]);

int main() {
    char s[MAXSIZE];
    int s_len;

    while (!END) {
        s_len = get_line(s);

        reverse(s, 0, s_len - 1);

        printf("%s\n", s);
    }
    return 0;
}

void reverse(char s[], int l, int r) {
    if (l >= r)
        return;

    char temp;

    temp = s[l];
    s[l] = s[r];
    s[r] = temp;

    reverse(s, l + 1, r - 1);
}

int get_line(char s[]) {
    int c;
    int i = 0;

    while ((c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    
    if (c == EOF) {
        END = 1;
    }

    s[i] = '\0';

    return i;
}
